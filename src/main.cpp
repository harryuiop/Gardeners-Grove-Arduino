#include <Arduino.h>
#include <cstdio>

#include "clock.h"
#include "dataTemplateString.h"
#include "internet.h"
#include "sensors.h"

// #define LOGGING

#define ARDUINO_ID "one"
#define DELAY_VALUE_MS 1000 * 60 * 5 // Five minutes in milliseconds

static char data[200] = {0};

void setup() {
#ifdef LOGGING
  Serial.begin(9600);
  while (!Serial)
    continue; // wait for serial port to connect.
  Serial.println("Serial communication started!");
#endif

  connectWifi();
  initialiseTime();
  sensorSetup();
}

void loop() {
  float temp = digitalHumidityTemperature.readTemperature();
  float humidity = digitalHumidityTemperature.readHumidity();
  float pressure = pressureSensor.readPressureATM();
  float light_percentage = getLightPercentage();
  float moisture = getMoisturePercentage();

  timeStampString time;
  formatCurrentTime(time);

#ifdef LOGGING
  printSensorReadings(temp, humidity, pressure, light_percentage, moisture);
#endif

  sprintf(data, dataTemplate, ARDUINO_ID, temp, humidity, pressure,
          light_percentage, moisture, time);

  postData(data);
  delay(DELAY_VALUE_MS);
}
