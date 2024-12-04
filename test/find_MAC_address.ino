#include <SPI.h>
#include <WiFi.h>

char ssid[] = "random"; // Needed to start the wifi stuff so we can check the MAC address.
int status = WL_IDLE_STATUS;

byte mac[6];


void setup()
{
 Serial.begin(9600);

 status = WiFi.begin(ssid);


  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);

}

void loop () {}