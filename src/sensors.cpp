#include "sensors.h"

// Change these depending on what are connected to the physical arduino
#define USING_WIFI 1
#define USING_LIGHT_SENSOR 1
#define USING_DHT_SENSOR 1
#define USING_SPL06_SENSOR 1
#define USING_MOISTURE_SENSOR 1

#define LIGHT_SENSOR_PIN 0    // Analog pin number
#define DHT_SENSOR_PIN 2      // Digital
#define MOISTURE_SENSOR_PIN 1 // Analog

#define MAX_ANALOG_VALUE 1023

#define PRESSURE_SENSOR_I2C_ADDRESS 0x76

DHT digitalHumidityTemperature(DHT_SENSOR_PIN, DHT11);
SPL06 pressureSensor;

/**
 * Sets up the DHT (humidity and temperature) and barometer
 */
void sensorSetup() {
#if USING_DHT_SENSOR
  digitalHumidityTemperature.begin();
#endif
#if USING_SPL06_SENSOR
  pressureSensor.begin(PRESSURE_SENSOR_I2C_ADDRESS);
#endif
}

/**
 * Print sensor readings
 * @param name Name of sensor
 * @param reading Current reading
 * @param units Units related to sensor reading
 */
void printSensorReading(const char *name, float reading, const char *units) {
  Serial.print(name);
  Serial.print(" ");
  Serial.print(reading);
  Serial.println(units);
}

/**
 * Reads light level from analog input and converts it to percentage
 * @return the light level percentage
 */
float getLightPercentage() {
  int lightLevel = analogRead(LIGHT_SENSOR_PIN);
  return (float)lightLevel / MAX_ANALOG_VALUE *
         100; // Analog reads from 0 - 1023
}

/**
 * Reads moisture level from analog input and converts it to percentage
 * @return the moisture level percentage
 */
float getMoisturePercentage() {
  int moistureLevel = analogRead(MOISTURE_SENSOR_PIN);
  return (float)moistureLevel / 1023.0 * 100; // Analog reads from 0 - 1023
}

/**
 * Print all five sensor values to the serial port
 *
 * @param temp The temperature reading from the DHT.
 * @param humidity The humidity reading from the DHT.
 * @param pressure The air pressure reading from the barometer.
 * @param light_percentage The light level reading from the LDR.
 * @param moisture The moisture reading from the moisture sensor.
 */
void printSensorReadings(float temp, int humidity, float pressure,
                         int light_percentage, int moisture) {
  printSensorReading("Temperature", temp, "C");
  printSensorReading("Humidity", humidity, "%");
  printSensorReading("Pressure", pressure, "atmospheres");
  printSensorReading("Light Level", light_percentage, "%");
  printSensorReading("Moisture Level", moisture, "%");
}
