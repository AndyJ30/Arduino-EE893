# Arduino-EE893
Arduino library for interfacing with EE893 CO2 sensor and other E2 interface devices

# Usage
To use the EE893 library:

1. Copy the EE893 directory into your Arduino libraries directory (%USERPROFILE%\Documents\Arduino\libraries\)
2. Include the library at the top of your sketch, and create a variable to refer to it:
```c++
   #include <EE893.h>
   EE893 Sensor;
```
3. Call the library functions to read values from the sensor:
```c++
   Serial.print("CO2 Reading (Instantaneous):\t");
   Serial.print(Sensor.readCo2Fast());
   Serial.println("ppm");
   
   //"CO2 Reading (Instantaneous):	1444ppm"
```   
# Functions

## ```readCo2Fast()```
Reads the current instantaneous CO2 measurement.

This function has 2 variants:

```c++
uint16_t readCo2Fast()
```
Returns an integer containing the current instantaneous CO2 reading in ppm (parts per million).

If an error occurred, returns 0xFFFF.

---
```c++
byte readCo2Fast(byte *hi, byte *lo)
```
On success, writes the high byte of the value into `hi`, and the low byte into `lo`.

Return values:
* 0: Success
* 1: Checksum failure while reading value
* 2: No response from device


## ```readCo2Accurate()```
Reads the recent average CO2 measurement.

This function has 2 variants:

```c++
uint16_t readCo2Accurate()
```
Returns an integer containing the recent average CO2 reading in ppm (parts per million).

If an error occurred, returns 0xFFFF.

---
```c++
byte readCo2Accurate(byte *hi, byte *lo)
```
On success, writes the high byte of the value into `hi`, and the low byte into `lo`.

Return values:
* 0: Success
* 1: Checksum failure while reading value
* 2: No response from device


## ```readByte()```
Reads a single byte value from the device.

The value to returned is specified by passing one of the [Control Byte](#control-bytes) names.

```c++
byte readByte(byte control_byte, byte *result)
```
On success, writes the high byte of the value into `hi`, and the low byte into `lo`.

Return values:
* 0: Success
* 1: Checksum failure while reading value
* 2: No response from device


## ```readValue()```
Reads a 16-bit value from the device.

The value to returned is specified by passing one of the [Readable Value](#readable-values) names.

```c++
byte readValue(byte get_value, uint16_t *result)
```
On success, writes the value into `result`.

Return values:
* 0: Success
* 1: Checksum failure while reading value
* 2: No response from device

## ```readByteFromAddress()```
Reads a single byte from the Custom Memory area of the device.

Use this function to read configuration values from the device.

This function has 2 variants:

```c++
byte readByteFromAddress(byte address)
```
Returns the byte from the custom memory address passed.

If an error occurred, returns 0xFF.

If the device does not support the value requested, returns 0xFF or 0x55.

---
```c++
byte readByteFromAddress(byte address, byte *result)
```
On success, writes the byte from the custom memory address passed into `result`.

If the device does not support the value requested, result will be 0xFF or 0x55.

Return values:
* 0: Success
* 1: Checksum failure while reading value
* 2: No response from device

## ```readBytesFromAddress()```
Reads a series of consecutive bytes from the Custom Memory area of the device.

Use this function to read information such as the device name or serial number.

```c++
byte readByteFromAddress(byte address, byte result[], byte length)
```
On success, writes `length` consecutive bytes starting from the custom memory address passed into `result`.

If the device does not support one or more values requested, result will contain 0xFF or 0x55.

Return values:
* 0: Success
* 1: Checksum failure while reading values
* 2: No response from device

## ```dumpMemory()```
Reads the entire Custom Memory area of the device into a buffer.
```c++
byte dumpMemory(byte data[])
```
On success, writes all 256 bytes of custom memory into `data`.

If the device does not support one or more values requested, result will contain 0xFF or 0x55.

Return values:
* 0: Success
* 1: Checksum failure while reading values
* 2: No response from device

## ```printSensorInfo()```
Prints information about the device to the serial console (if connected).
```c++
void printSensorInfo()
```
Example:
```
Sensor Type:
	EE893
Sensor Sub-Type:
	EE893-0 FT9
Custom Part Name:	
	EE893
Serial Number:	
	123456789123456
Bus Address:
	0
Available Physical Measurements:
	Humidity:     Not Supported
	Temperature:  Not Supported
	Air Velocity: Not Supported
	CO2:          Available
Status Byte:
	Humidity:     Error
	Temperature:  Error
	Air Velocity: Error
	CO2:          OK
```

## ```printAllValues()```
Checks the `Available Physical Measurements` flags, then prints all available measurements to the serial console (if connected).
```c++
void printAllValues()
```
Example:
```
CO2 (Fast):	    1030ppm
CO2 (Accurate):	688ppm
```

## ```printMemoryDump()```
Reads the entire Custom Memory area of the device and prints it to the serial console (if connected).
```c++
void printAllValues()
```
Example
```
Memory Dump:
	0	1	2	3	4	5	6	7	8	9	A	B	C	D	E	F
0	0x1	0x0	0x4	0x8	0x8	0x1	0x8	0x93	0x0	0x0	0x55	0x55	0x55	0x55	0x55	0x55
1	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
2	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
3	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
4	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
5	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x0	0x0	0x0	0x80	0x0	0x0	0x88	0x13
6	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
7	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
8	0xFF	0xFF	0xFF	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0xFF	0xFF	0xFF	0x55
9	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
A	0x31	0x34	0x31	0x31	0x39	0x33	0x35	0x38	0x31	0x32	0x32	0x37	0x38	0x36	0x0	0x0
B	0x45	0x45	0x38	0x39	0x33	0x0	0x0	0x0	0x0	0x0	0x0	0x0	0x0	0x0	0x0	0x0
C	0x0	0xCA	0x55	0x55	0x55	0x55	0xA0	0x8C	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
D	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
E	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55
F	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x55	0x9	0xB1
```

# Readable Values
These readable value names are used to specify which value to return from the ```readValue()``` function:
```c++
#define HUMIDITY_VALUE 0x00
#define TEMPERATURE_VALUE 0x01
#define AIR_VELOCITY_VALUE 0x02
#define CO2_AVG_VALUE 0x02
#define CO2_VALUE 0x03
```

# Control Bytes
These control byte names are used to specify which value to return from the ```readByte()``` function:
```c++
#define SENSOR_TYPE_GROUP_L 0x11              //Sensor Type Group (Low Byte)
#define SENSOR_TYPE_SUBGROUP   0x21           //Sensor Type Sub-Group
#define AVAILABLE_PHYSICAL_MEASUREMENTS 0x31  //Available Physical Measurement flags
#define SENSOR_TYPE_GROUP_H 0x41              //Sensor Type Group (High Byte)
#define READ_CUSTOM_ADDRESS 0x51              //Read the byte specified by the custom address pointer
#define STATUS_BYTE 0x71                      //Measurement status flags
#define HUMIDITY_L 0x81                       //Measure1/Humidity Value (Low Byte) 
#define HUMIDITY_H 0x91                       //Measure1/Humidity Value (High Byte) 
#define TEMPERATURE_L 0xA1                    //Measure2/Temperature Value (Low Byte) 
#define TEMPERATURE_H 0xB1                    //Measure2/Temperature Value (High Byte) 
#define AIR_VELOCITY_L 0xC1                   //Measure3/Air Velocity Value (Low Byte) 
#define AIR_VELOCITY_H 0xD1                   //Measure3/Air Velocity Value (High Byte) 
#define CO2_AVG_L 0xC1                        //Measure3/CO2 Avg Value (Low Byte) 
#define CO2_AVG_H 0xD1                        //Measure3/CO2 Avg Value (High Byte) 
#define CO2_L 0xE1                            //Measure4/CO2 Value (Low Byte) 
#define CO2_H 0xF1                            //Measure4/CO2 Value (High Byte) 
```
# References
* Original comms code from: https://github.com/blueberrye-io/BB-EE893
* EE893 Datasheet: http://downloads.epluse.com/fileadmin/data/product/ee893/datasheet_EE893.pdf
* E2 Protocol specification: http://downloads.epluse.com/fileadmin/data/sw/Specification_E2_Interface.pdf
