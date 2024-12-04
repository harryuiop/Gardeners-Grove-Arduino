#ifndef SENSORS_H
#define SENSORS_H

#include <DHT.h>
#include <SPL06-001.h>

extern DHT digitalHumidityTemperature;
extern SPL06 pressureSensor;

void sensorSetup();

float getLightPercentage();
float getMoisturePercentage();

void printSensorReading(const char *name, float reading, const char *units);
void printSensorReadings(float temp, int humidity, float pressure,
                         int light_percentage, int moisture);

#endif // !SENSORS_H
