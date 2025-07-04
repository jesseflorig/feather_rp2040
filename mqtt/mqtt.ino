// Author: Jesse Florig
// License: MIT
// Board: Adafruit Feather RP2040, Silicognition PoE HAT
// Description: Use the W5500 to set a static IP, connect to an MQTT broker, 
//              publish a connect and heartbeat message, and subscribe to a topic

#define DEBUG 1  // Set to 0 for production

// Debug macros
#if DEBUG
  #define DEBUG_BEGIN(baud)    Serial.begin(baud); while (!Serial && millis() < 2000)
  #define DEBUG_PRINT(x)       Serial.print(x)
  #define DEBUG_PRINTLN(x)     Serial.println(x)
  #define DEBUG_PRINTF(...)    Serial.printf(__VA_ARGS__)
#else
  #define DEBUG_BEGIN(baud)
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINTF(...)
#endif

// Unset to supress redefined warnings
#ifdef htons
  #undef htons
#endif

#include <SPI.h>
#include <Ethernet.h>
#include <MQTT.h>

// Network settings
byte mac[] = { 0x02, 0xFE, 0xD3, 0xAD, 0xBE, 0xEF };
IPAddress ip(10, 1, 1, 20);
IPAddress subnet(255, 255, 255, 0);

// MQTT broker config
IPAddress broker(10, 1, 1, 10);
const int mqttPort = 1883;
const char* mqttUser = "pico";
const char* mqttPass = "password";
const char* mqttClientID = "feather-pico";

// MQTT Topics
const char* publishTopic = "fleet1/pico/status";
const char* subscribeTopic = "fleet1/pico/test";

// Ethernet and MQTT clients
EthernetClient net;
MQTTClient client(128);  // 128-byte message buffer

// Initialize ethernet connection
void connectToEthernet(){
  DEBUG_BEGIN(115200);
  Ethernet.begin(mac, ip, subnet);
  DEBUG_PRINT("IP Address: ");
  DEBUG_PRINTLN(Ethernet.localIP());
}

// Connect to broker and publish online message
void connectToMQTT() {
  // Client settings
  client.begin(broker, mqttPort, net);
  client.onMessage(onTestMessage);
  client.setWill(publishTopic, "offline", true, 1);
  
  DEBUG_PRINT("Connecting to MQTT...");
  while (!client.connect(mqttClientID, mqttUser, mqttPass)) {
    DEBUG_PRINT(".");
    delay(1000);
  }
  DEBUG_PRINTLN("connected!");
  client.publish(publishTopic, "online", true, 1);

  // Subscriptions
  DEBUG_PRINT("Subscribing to ");
  DEBUG_PRINTLN(subscribeTopic);
  client.subscribe(subscribeTopic);
}

// Publish a heartbeat status every 10 seconds
void publishHeartbeat(){
  static unsigned long lastPublish = 0;
  if (millis() - lastPublish > 10000) {
    lastPublish = millis();
    client.publish(publishTopic, "heartbeat", true, 1);
    DEBUG_PRINTLN("Published heartbeat");
  }
}

// Subscription handler
void onTestMessage(String &topic, String &payload) {
  DEBUG_PRINT("Received on ");
  DEBUG_PRINT(topic);
  DEBUG_PRINT(": ");
  DEBUG_PRINTLN(payload);
}

void setup() {
  connectToEthernet();
  connectToMQTT();
}

void loop() {
  client.loop();
  publishHeartbeat();

  // Reconnect if dropped
  if (!client.connected()) {
    connectToMQTT();
  }
}
