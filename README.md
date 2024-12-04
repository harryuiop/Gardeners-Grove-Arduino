## Installation and Run
- Open CLion Jetbrains IDE
- Download Platform IO (for example, using curl)
```
curl -fsSL -o get-platformio.py https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py
python3 get-platformio.py
```
- Download 'Platform IO for CLion' plugin in IDE (File > settings > Plugins: search Platform IO for CLion)
- Build project with command below
```
pio run
```
- Upload project to arduino with command below
```
pio run -t upload
```
- Read serial with command below
```
pio device monitor
```

## Connecting Sensors to the Arduino
The arduinos used for this project are the Arduino Uno R4 WiFi. When connecting the mulittude of sensors to the arduino, it is advised that a breadboard is used in which the 5V header of the board is connected to the positive rail on the breadboard, and a ground pin is connected to the minus rail. The sensors may then have their respective Vin and Gnd pins connected to these rails.
The data pins should be connected to the board as follows:

| Sensor | Pin |
| ------ | ------ |
|    Light sensor    |  A0      |
|     DHT11 (Temp and humidity)   | 2       |
| Soil moisture sensor | A1 |
|Barometric Sensor| A4, A5|

## Using the Soil Moisture Sensor with a Plant
The sensor should be placed in the soil such that the top of the soil meets the top of the capacitive plating. DO NOT place the sensor any deeper, as water on the electronics above may interfere with or damage the sensor and board.

## Sending JSON Data
Data sent through HTTP in the following json form:
- All number types will be floats.
- Dates in ISO_8601 format: https://en.wikipedia.org/wiki/ISO_8601
- Id relates to the specific arduino used
- Time will be in the format "dd-MM-yyyy HH:mm"
```typescript
type SensorData = {
    id: string,
    temperatureCelcius: number,
    humidityPercentage: number,
    atomsphereAtm: number,
    lightLevelPercentage: number,
    mositurePercentage: number,
    time: string,
}
```