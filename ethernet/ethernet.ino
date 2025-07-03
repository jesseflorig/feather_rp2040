// Author: Jesse Florig
// License: MIT
// Board: Adafruit Feather RP2040, Silicognition PoE HAT
// Description: Use the W5500 to set a static IP

#include <SPI.h>
#include <Ethernet.h>

// Use a unique locally administered MAC
byte mac[] = { 0x02, 0xFE, 0xD3, 0xAD, 0xBE, 0xEF };

// Static network config
IPAddress ip(10,1,1,20);
IPAddress gateway(0,0,0,0);
IPAddress subnet(255, 255, 255, 0);

// Helper function to return ethernet hardware detected
const char* getHardwareStatusString() {
  switch (Ethernet.hardwareStatus()) {
    case EthernetNoHardware: return "No hardware";
    case EthernetW5100:      return "W5100";
    case EthernetW5200:      return "W5200";
    case EthernetW5500:      return "W5500";
    default:                 return "Unknown";
  }
}

const char* getLocalIP() {
  static char ipStr[16];  // Enough for "255.255.255.255"
  IPAddress ip = Ethernet.localIP();
  snprintf(ipStr, sizeof(ipStr), "%u.%u.%u.%u", ip[0], ip[1], ip[2], ip[3]);
  return ipStr;
}

const char* getLinkStatus() {
  return Ethernet.linkStatus() == LinkON ? "alive" : "dead";
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("Initializing Ethernet with Static IP...");
  Ethernet.begin(mac, ip, subnet);
  
  delay(1000); // Allow hardware to settle
  Serial.printf("Ethernet %s initialized @ %s\n",
              getHardwareStatusString(),
              getLocalIP());
}

void loop() {
  Serial.printf("Ethernet is %s @ %s\n",
              getLinkStatus(),
              getLocalIP());
  delay(5000);
}
