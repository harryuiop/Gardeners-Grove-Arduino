#include <ArduinoHttpClient.h>
#include <WiFiS3.h>

#include "certificate.h"
#include "wifi_credentials.h"

#define LOGGING

static constexpr char *HOST_NAME = "csse-seng302-team400.canterbury.ac.nz";
static constexpr int PORT_NUMBER = 443;
static constexpr char *REQUEST_PATH = "/prod/sensor-data";

static WiFiSSLClient wiFiClient;
static HttpClient httpClient(wiFiClient, HOST_NAME, PORT_NUMBER);

static int status = WL_IDLE_STATUS;

void connectWifi() {
  // Wi-Fi connection code modified from Arduino's WiFiS3 example
  // https://github.com/arduino/ArduinoCore-renesas/tree/main/libraries/WiFiS3/examples/WiFiWebClientSSL/WiFiWebClientSSL.ino

  // Attempt to connect to Wi-Fi network:
  while (status != WL_CONNECTED) {
#ifdef LOGGING
    Serial.print("Attempting to connect to ");
    Serial.println(WIFI_SSID);
#endif

    // Connect to WPA/WPA2 network:
    status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // wait 1 second for connection:
    delay(1000);
  }
#ifdef LOGGING
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
#endif

  wiFiClient.setCACert(certificate);
}

int postData(const char *data) {
  int errorCode = httpClient.post(REQUEST_PATH, "application/json", data);

#ifdef LOGGING
  if (errorCode >= 0) {
    int statusCode = httpClient.responseStatusCode();
    Serial.print("Status code: ");
    Serial.println(statusCode);

    String response = httpClient.responseBody();
    Serial.print("Response: ");
    Serial.println(response);
  } else {
    Serial.print("Was error: ");
    Serial.println(errorCode);
  }
#endif

  httpClient.stop();
  return errorCode;
}
