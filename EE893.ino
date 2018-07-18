#include <Wire.h>
#include <EE893.h>

EE893 Sensor;

void setup() {

  Serial.begin(9600);
  
  Serial.print("CO2 Reading (Instantaneous):\t");
  Serial.print(Sensor.readCo2Fast());
  Serial.println("ppm");
  Serial.print("CO2 Reading (Recent Avg):\t");
  Serial.print(Sensor.readCo2Accurate());
  Serial.println("ppm");
  Sensor.printSensorInfo();
  Sensor.printMemoryDump();
  
}

void loop() {
}

