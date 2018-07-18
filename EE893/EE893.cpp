
#include <Wire.h>
#include <EE893.h>

EE893::EE893(){
  Wire.begin();
  TWBR = 200;  // set the TWBR register (bypass wire library) reduce the speed about 3 times
  TWSR |= bit (TWPS0);
  TWSR |= bit (TWPS1);
}


void EE893::printValue(String measure, uint16_t value, String units){
  Serial.print(measure); Serial.print(":\t"); 
  if (value == 0x55){ 
    Serial.println("Not Supported"); 
  } else { 
    Serial.print(value); Serial.println(units);
  };
}

byte EE893::readCo2Fast(byte *hi, byte *lo)
{
  byte result;

  result = EE893::readByte(0xC1, lo);
  if (result != 0) {
    return result;
  }
  result = EE893::readByte(0xD1, hi);
  if (result != 0) {
    return result;
  }
  return 0;
}

uint16_t EE893::readCo2Fast()
{
  uint16_t val;
  byte result;
  
  result = EE893::readValue(CO2_VALUE, &val);
  if (result != 0) {
    return 0xFFFF;
  }
  else {
    return val;
  }
}

byte EE893::readCo2Accurate(byte *hi, byte *lo)
{
  byte result, result_byte;

  result = EE893::readByte(0xE1, lo);
  if (result != 0) {
    return result;
  }
  result = EE893::readByte(0xF1, hi);
  if (result != 0) {
    return result;
  }

  return 0;
}

uint16_t EE893::readCo2Accurate()
{
  uint16_t val;
  byte result;
  
  result = EE893::readValue(CO2_AVG_VALUE, &val);
  if (result != 0) {
    return 0xFFFF;
  }
  else {
    return val;
  }
}

byte EE893::readByteFromAddress(byte address, byte *result){

  EE893::setCustomAddressPointer(0x00,address);
  return EE893::readByte(READ_CUSTOM_ADDRESS, result);

}

byte EE893::readByteFromAddress(byte address){
  byte ret, result;
  ret = EE893::setCustomAddressPointer(0x00,address);
  if (ret != 0) return 0xFF;

  ret = EE893::readByte(READ_CUSTOM_ADDRESS, &result);
  if (ret != 0) return 0xFF;
  
  return result;
}

byte EE893::readBytesFromAddress(byte address, byte result[], byte length){

  byte ret;

  ret = EE893::setCustomAddressPointer(0x00,address);
  if (ret != 0) return 0xFF;
  
  for (byte i = 0; i < length; i++){
    ret = EE893::readByte(READ_CUSTOM_ADDRESS, &result[i]);
    if (ret != 0) return 0xFF;
  }
  return 0;
}

byte EE893::readByte(byte control_byte, byte *result)
{
  byte control, dev_addr, i2c_addr, checksum;

  control = control_byte;
  dev_addr = 0x00;

  i2c_addr = ((control) | (dev_addr << 1)) >> 1;

  Wire.requestFrom(i2c_addr, 2);
  if (Wire.available()) {
    *result = Wire.read();
    checksum = Wire.read();

    if (checksum != ((*result + control) % 0x100)) {
       return 1;
     }
  }
  else {
    return 2;
  }
  return 0;
}

byte EE893::readValue(byte get_value, byte *hi, byte *lo)
{
  byte result, result_byte, lo_reg, hi_reg;

  switch(get_value){
    case TEMPERATURE_VALUE:
      lo_reg = TEMPERATURE_L;
      hi_reg = TEMPERATURE_H;
      break;
    case HUMIDITY_VALUE:
      lo_reg = HUMIDITY_L;
      hi_reg = HUMIDITY_H;
      break;
    case CO2_AVG_VALUE:
      lo_reg = CO2_AVG_L;
      hi_reg = CO2_AVG_H;
      break;
    case CO2_VALUE:
      lo_reg = CO2_L;
      hi_reg = CO2_H;
      break;
    case SENSOR_TYPE_GROUP:
      lo_reg = SENSOR_TYPE_GROUP_L;
      hi_reg = SENSOR_TYPE_GROUP_H;
      break;
  }
  
  result = EE893::readByte(lo_reg, lo);
  if (result != 0) {
    return result;
  }
  result = EE893::readByte(hi_reg, hi);
  if (result != 0) {
    return result;
  }
  return 0;
}

byte EE893::readValue(byte get_value, uint16_t *value)
{
  byte result, lo_reg, hi_reg, lo, hi;

  switch(get_value){
    case TEMPERATURE_VALUE:
      lo_reg = TEMPERATURE_L;
      hi_reg = TEMPERATURE_H;
      break;
    case HUMIDITY_VALUE:
      lo_reg = HUMIDITY_L;
      hi_reg = HUMIDITY_H;
      break;
    case CO2_AVG_VALUE:
      lo_reg = CO2_AVG_L;
      hi_reg = CO2_AVG_H;
      break;
    case CO2_VALUE:
      lo_reg = CO2_L;
      hi_reg = CO2_H;
      break;
    case SENSOR_TYPE_GROUP:
      lo_reg = SENSOR_TYPE_GROUP_L;
      hi_reg = SENSOR_TYPE_GROUP_H;
      break;
  }
  
  result = EE893::readByte(lo_reg, &lo);
  if (result != 0) {
    return result;
  }
  result = EE893::readByte(hi_reg, &hi);
  if (result != 0) {
    return result;
  }
  
  *value = (hi << 8) + lo;

  return 0;
}

byte EE893::dumpMemory(byte data[]){
  
  byte ret;
    
  EE893::setCustomAddressPointer(0x00,0x00);
  
  for (int i = 0; i <= 0xFF; i++){
    ret = EE893::readByte(READ_CUSTOM_ADDRESS, &data[i]);
    if (ret != 0){
      return ret;
    }
  }
}

void EE893::printMemoryDump(){
  
  byte b, ret;
  
  EE893::setCustomAddressPointer(0x00,0x00);

  Serial.println("\n\nMemory Dump:");
  
  for (byte j = 0; j <= 0xF; j++){
     Serial.print("\t"); Serial.print(j, HEX);
  }
  for (byte i = 0; i <= 0xF; i++){
    Serial.print("\n");Serial.print(i, HEX);
    for (byte j = 0; j <= 0xF; j++){
      ret = EE893::readByte(READ_CUSTOM_ADDRESS, &b);
      Serial.print("\t0x"); Serial.print(b, HEX);
    }
  }
}

void EE893::printSensorInfo(){
  byte b, buf[0xF], ret;
  uint16_t val, sensor_type;
  
  ret = EE893::readValue(SENSOR_TYPE_GROUP, &val);
  sensor_type = val;
  Serial.println("\n\nSensor Type:");
  Serial.print("\tEE"); Serial.println(val);
  if (ret != 0) EE893::printError(ret);

  ret = EE893::readByte(SENSOR_TYPE_SUBGROUP, &b);
  Serial.println("Sensor Sub-Type:");
  Serial.print("\tEE"); Serial.print(sensor_type); Serial.print("-"); Serial.print(b >> 4); Serial.print(" FT"); Serial.println((b & 0x0F));
  if (ret != 0) EE893::printError(ret);
  
  ret = EE893::readBytesFromAddress(PART_NAME, buf, (byte) 0xF);
  Serial.println("Custom Part Name:\t");
  Serial.print("\t");
  for (byte i = 0; i < 0xF; i++){
    Serial.print((char)buf[i]);
  }
  Serial.print("\n");
  if (ret != 0) EE893::printError(ret);

  ret = EE893::readBytesFromAddress(SERIAL_NUMBER, buf, (byte) 0xF);
  Serial.println("Serial Number:\t");
  Serial.print("\t");
  for (byte i = 0; i < 0xF; i++){
    Serial.print((char)buf[i]);
  }
  Serial.print("\n");  
  if (ret != 0) EE893::printError(ret);

  ret = EE893::readByteFromAddress(BUS_ADDRESS, &b);
  Serial.println("Bus Address:");
  Serial.print("\t"); Serial.println(b);
  if (ret != 0) EE893::printError(ret);

  ret = EE893::readByte(AVAILABLE_PHYSICAL_MEASUREMENTS, &b);
  Serial.println("Available Physical Measurements:"); 
  Serial.print("\tHumidity:\t"); Serial.println( bitRead(b,0) ? "Available" : "Not Supported");
  Serial.print("\tTemperature:\t"); Serial.println(bitRead(b,1) ? "Available" : "Not Supported");
  Serial.print("\tAir Velocity:\t"); Serial.println(bitRead(b,2) ? "Available" : "Not Supported");
  Serial.print("\tCO2:\t\t"); Serial.println(bitRead(b,3) ? "Available" : "Not Supported");
  if (ret != 0) EE893::printError(ret);  
  
  ret = EE893::readByte(STATUS_BYTE, &b);
  Serial.println("Status Byte:");
  Serial.print("\tHumidity:\t"); Serial.println(bitRead(b,0) ? "OK" : "Error");
  Serial.print("\tTemperature:\t"); Serial.println(bitRead(b,1) ? "OK" : "Error");
  Serial.print("\tAir Velocity:\t"); Serial.println(bitRead(b,2) ? "OK" : "Error");
  Serial.print("\tCO2:\t\t"); Serial.println(bitRead(b,3) ? "OK" : "Error");
  if (ret != 0) EE893::printError(ret);
  
}

void EE893::printAllValues() {

  byte b, ret, available, status;
  uint16_t val, sensor_type;
   
  ret = EE893::readByte(AVAILABLE_PHYSICAL_MEASUREMENTS, &available);
  if (ret != 0) EE893::printError(ret);
  
  ret = EE893::readByte(STATUS_BYTE, &status);
  if (ret != 0) EE893::printError(ret);
  
  if (bitRead(available, 0) && bitRead(status, 0)){
    ret = EE893::readValue(HUMIDITY_VALUE, &val);
    EE893::printValue("Humidity", val, "%RH");
    if (ret != 0) EE893::printError(ret);
  }

  if (bitRead(available, 1) && bitRead(status, 1)){
    ret = EE893::readValue(TEMPERATURE_VALUE, &val);
    EE893::printValue("Temperature", val, "degC");
    if (ret != 0) EE893::printError(ret);
  }

  if (bitRead(available, 2) && bitRead(status, 2)){
    ret = EE893::readValue(AIR_VELOCITY_VALUE, &val);
    EE893::printValue("Air Velocity", val, "M/s");
    if (ret != 0) EE893::printError(ret);
  }

  if (bitRead(available, 3) && bitRead(status, 3)){
    ret = EE893::readValue(CO2_VALUE, &val);
    EE893::printValue("CO2 (Fast)", val, "ppm");
    if (ret != 0) EE893::printError(ret);

    ret = EE893::readValue(CO2_AVG_VALUE, &val);
    EE893::printValue("CO2 (Accurate)", val, "ppm");
    if (ret != 0) EE893::printError(ret);
  }
}

byte EE893::setCustomAddressPointer(byte hi, byte lo)
{
  byte control, address, data, dev_addr, i2c_addr, checksum;

  control = SET_CUSTOM_ADDRESS_POINTER;
  address = hi;
  data = lo;
  dev_addr = 0x00;

  // Send Control Byte
  i2c_addr = ((control) | (dev_addr << 1)) >> 1;

  checksum = ((control + address + data) % 0x100);
  
  //Wert lesen:
  Wire.beginTransmission(i2c_addr);
  Wire.write(address);
  Wire.write(data);
  Wire.write(checksum);
  Wire.endTransmission();
  
  return 0;
}

void EE893::errorMessage(byte err_number, String &buffer){
  switch(err_number){
    case 0:
      buffer = "OK";
      break;
    case 1:
      buffer = "Checksum Failure";
      break;
    case 2:
      buffer = "Communication Failure";
      break;
  }
}

void EE893::printError(byte err_number){
  String msg;
  EE893::errorMessage(err_number, msg);
  Serial.println(msg);
}