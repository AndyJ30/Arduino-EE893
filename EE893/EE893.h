#ifndef EE893_h
#define EE893_h

#include <Arduino.h>

//Control Bytes
#define WRITE_CUSTOM_ADDRESS 0x10
#define SENSOR_TYPE_GROUP_L 0x11
#define SENSOR_TYPE_SUBGROUP   0x21
#define AVAILABLE_PHYSICAL_MEASUREMENTS 0x31
#define SENSOR_TYPE_GROUP_H 0x41
#define SET_CUSTOM_ADDRESS_POINTER 0x50
#define READ_CUSTOM_ADDRESS 0x51
#define STATUS_BYTE 0x71
#define HUMIDITY_L 0x81
#define HUMIDITY_H 0x91
#define TEMPERATURE_L 0xA1
#define TEMPERATURE_H 0xB1
#define AIR_VELOCITY_L 0xC1
#define AIR_VELOCITY_H 0xD1
#define CO2_AVG_L 0xC1
#define CO2_AVG_H 0xD1
#define CO2_L 0xE1
#define CO2_H 0xF1

//Readable value types
#define HUMIDITY_VALUE 0
#define TEMPERATURE_VALUE 1
#define AIR_VELOCITY_VALUE 2
#define CO2_AVG_VALUE 2
#define CO2_VALUE 3
#define SENSOR_TYPE_GROUP 4

//Custom Memory addresses
#define FIRMWARE_VERSION_MAJOR         (byte) 0x00
#define FIRMWARE_VERSION_MINOR          (byte) 0x01
#define E2_VERSION                      (byte) 0x02
#define SUPPORT_OFFSET_GAIN_ADJUSTMENT  (byte) 0x03
#define SUPPORT_SAVE_ADJUSTMENT_POINT   (byte) 0x04
#define SUPPORT_TIMESTAMP_ADJUSTMENT_GENERAL      (byte) 0x05
#define SUPPORT_TIMESTAMP_ADJUSTMENT_PER_MEASURE  (byte) 0x06
#define SUPPORT_OPERATING_FUNCTIONS     (byte) 0x07
#define SUPPORT_OPERATING_MODE          (byte) 0x08
#define SUPPORT_SPECIAL_FEATURES        (byte) 0x09
//0x0A-0x3F Reserved
#define HUMIDITY_OFFSET_L               (byte) 0x40
#define HUMIDITY_OFFSET_H               (byte) 0x41
#define HUMIDITY_GAIN_L                 (byte) 0x42
#define HUMIDITY_GAIN_H                 (byte) 0x43
#define HUMIDITY_RANGE_LOWER_L          (byte) 0x44
#define HUMIDITY_RANGE_LOWER_H          (byte) 0x45
#define HUMIDITY_RANGE_UPPER_L          (byte) 0x46
#define HUMIDITY_RANGE_UPPER_H          (byte) 0x47
#define TEMPERATURE_OFFSET_L            (byte) 0x48
#define TEMPERATURE_OFFSET_H            (byte) 0x49
#define TEMPERATURE_GAIN_L              (byte) 0x4A
#define TEMPERATURE_GAIN_H              (byte) 0x4B
#define TEMPERATURE_RANGE_LOWER_L       (byte) 0x4C
#define TEMPERATURE_RANGE_LOWER_H       (byte) 0x4D
#define TEMPERATURE_RANGE_UPPER_L       (byte) 0x4E
#define TEMPERATURE_RANGE_UPPER_H       (byte) 0x4F
#define AIR_VELOCITY_OFFSET_L           (byte) 0x50
#define AIR_VELOCITY_OFFSET_H           (byte) 0x51
#define AIR_VELOCITY_GAIN_L             (byte) 0x52
#define AIR_VELOCITY_GAIN_H             (byte) 0x53
#define AIR_VELOCITY_RANGE_LOWER_L      (byte) 0x54
#define AIR_VELOCITY_RANGE_LOWER_H      (byte) 0x55
#define AIR_VELOCITY_RANGE_UPPER_L      (byte) 0x56
#define AIR_VELOCITY_RANGE_UPPER_H      (byte) 0x57
#define CO2_OFFSET_L                    (byte) 0x58
#define CO2_OFFSET_H                    (byte) 0x59
#define CO2_GAIN_L                      (byte) 0x5A
#define CO2_GAIN_H                      (byte) 0x5B
#define CO2_RANGE_LOWER_L               (byte) 0x5C
#define CO2_RANGE_LOWER_H               (byte) 0x5D
#define CO2_RANGE_UPPER_L               (byte) 0x5E
#define CO2_RANGE_UPPER_H               (byte) 0x5F
//0x60-0x7F Reserved
#define GLOBAL_TIMESTAMP_YEAR           (byte)0x80
#define GLOBAL_TIMESTAMP_MONTH         (byte)0x81
#define GLOBAL_TIMESTAMP_DAY           (byte)0x82
#define HUMIDITY_TIMESTAMP_YEAR        (byte)0x83
#define HUMIDITY_TIMESTAMP_MONTH       (byte)0x84
#define HUMIDITY_TIMESTAMP_DAY         (byte)0x85
#define TEMPERATURE_TIMESTAMP_YEAR     (byte)0x86
#define TEMPERATURE_TIMESTAMP_MONTH    (byte)0x87
#define TEMPERATURE_TIMESTAMP_DAY      (byte)0x88
#define VELOCITY_TIMESTAMP_YEAR        (byte)0x89
#define VELOCITY_TIMESTAMP_MONTH       (byte)0x8A
#define VELOCITY_TIMESTAMP_DAY         (byte)0x8B
#define CO2_TIMESTAMP_YEAR             (byte)0x8C
#define CO2_TIMESTAMP_MONTH            (byte)0x8D
#define CO2_TIMESTAMP_DAY               (byte)0x8E
//0x8F-0x9F Reserved
#define SERIAL_NUMBER                  (byte)0xA0 //16 Bytes 0xA0-0xAF
#define PART_NAME                      (byte)0xB0 //16 Bytes 0xB0-0xBF
#define BUS_ADDRESS                    (byte)0xC0
#define ERROR_CODE                     (byte)0xC1
//0xC2-0xC5 Reserved
#define GLOBAL_MEASUREMENT_INTERVAL_L    (byte)0xC6
#define GLOBAL_MEASUREMENT_INTERVAL_H    (byte)0xC7
#define HUMIDITY_INTERVAL_MULTIPLIER     (byte)0xC8
#define TEMPERATURE_INTERVAL_MULTIPLIER  (byte)0xC9
#define VELOCITY_INTERVAL_MULTIPLIER     (byte)0xCA
#define CO2_INTERVAL_MULTIPLIER          (byte)0xCB
//0xCC-0xCF Reserved
#define FILTER_HUMIDITY                 (byte)0xD0
#define FILTER_TEMPERATURE              (byte)0xD1
#define FILTER_VELOCITY                 (byte)0xD2
#define FILTER_CO2                      (byte)0xD3
//0xD4-0xD7 Reserved        
#define OPERATING_MODE                  (byte) 0xD8
#define SPECIAL_FEATURES                (byte) 0xD9
//0xDA-0xFD Reserved        
#define ADDRESS_POINTER_L               (byte) 0xFE
#define ADDRESS_POINTER_H               (byte) 0xFF

class EE893
{
  public:
    EE893();
    uint16_t readCo2Fast();
    uint16_t readCo2Accurate();
    byte readCo2Fast(byte *hi, byte *lo);
    byte readCo2Accurate(byte *hi, byte *lo);
    byte readByte(byte control_byte, byte *result);
    byte readByteFromAddress(byte address, byte *result);
    byte readByteFromAddress(byte address);
    byte readBytesFromAddress(byte address, byte result[], byte length);
    byte readValue(byte get_value, byte *hi, byte *lo);
    byte readValue(byte get_value, uint16_t *result);
    void printSensorInfo();
    void printAllValues();
    byte dumpMemory(byte data[]);
    void printMemoryDump();
  private:
    byte setCustomAddressPointer(byte hi, byte lo);
    void errorMessage(byte err_number, String &buffer);
    void printError(byte err_number);
    void printValue(String measure, uint16_t value, String units);

};

#endif
