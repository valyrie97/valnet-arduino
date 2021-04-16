#include "WiFi.h"
#include "EEPROM.h"
#include "mdns.h"

#include "RGBLED.h"
#include "Settings.h"

void setup() {
  
  Serial.begin(115200);
  Serial.println("");
  Serial.println(" ===== [ VALNET ] =====");
  Serial.println("");
  Serial.println("");

  Settings.begin();

  initRGBLED(STATUS_LED);
  setRGBLEDColor(STATUS_LED, RED);
  
  if(Settings.readWifi() == NULL_WIFI_SETTINGS) {
    enterSetupMode();
  } else {
    startValnet();
  }


}

void loop() {
  setRGBLEDColor(STATUS_LED, RED);
  delay(500);
  setRGBLEDColor(STATUS_LED, BLACK);
  delay(500);

  setRGBLEDColor(STATUS_LED, GREEN);
  delay(500);
  setRGBLEDColor(STATUS_LED, BLACK);
  delay(500);

  setRGBLEDColor(STATUS_LED, BLUE);
  delay(500);
  setRGBLEDColor(STATUS_LED, BLACK);
  delay(500);
  
  // setRGBLEDColor(STATUS_LED, CYAN);
  // delay(500);
  // setRGBLEDColor(STATUS_LED, BLACK);
  // delay(500);
  
  // setRGBLEDColor(STATUS_LED, MAGENTA);
  // delay(500);
  // setRGBLEDColor(STATUS_LED, BLACK);
  // delay(500);
  
  // setRGBLEDColor(STATUS_LED, YELLOW);
  // delay(500);
  // setRGBLEDColor(STATUS_LED, BLACK);
  // delay(500);
}

void enterSetupMode() {
  // AHHHHHHHHHHH SHIT
}

void startValnet() {
  WiFiNetworkSettings network = Settings.readWifi();

  Serial.println("SSID: " + String(network.ssid));
  Serial.println("PASS: " + String(network.passwd));

  WiFi.begin(network.ssid, network.passwd);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting to WiFi..");
    delay(500);
  }
  Serial.println("wifi connected!");
}