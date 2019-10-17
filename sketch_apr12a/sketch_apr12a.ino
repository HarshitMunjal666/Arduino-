#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
#include "Wire.h" // This library allows you to communicate with I2C devices.

const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.

int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
char tmp_str[7]; // temporary variable used in convert function

char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
} 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
 
void setup()
{
    Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true); // Initialize ASK Object
    rf_driver.init();
}
 
void loop()
{
   Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 8*2, true); // request a total of 8*2=16 registers
  
  gyro_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  Serial.println();
  Serial.print(" | gX = "); Serial.print(gyro_x);
  Serial.print(" | gY = "); Serial.print(gyro_y);
  Serial.print(" | gZ = "); Serial.print(gyro_z);
  Serial.println();
  
   if(gyro_x>2050 && gyro_y<0 && gyro_y> -9050 && gyro_z>7050)
    {
    const char *msg1 ="f";
    rf_driver.send((uint8_t *)msg1, strlen(msg1));
    rf_driver.waitPacketSent();
    Serial.print("f");
    delay(1050);
    }
    else if(gyro_x<-8050 && gyro_y>-5050 && gyro_y<550 && gyro_z> 7050)
    {
    const char *msg1 ="b";
    rf_driver.send((uint8_t *)msg1, strlen(msg1));
    rf_driver.waitPacketSent();
    Serial.print("b");
    delay(1050);
    }
    else if(gyro_x<1050 && gyro_x>-5050 && gyro_y<-10050 && gyro_z<7050 && gyro_z>-6050)
    {
    const char *msg1 ="l";
    rf_driver.send((uint8_t *)msg1, strlen(msg1));
     rf_driver.waitPacketSent();
    Serial.print("l");
    delay(1050);
    }
    else if(gyro_x>-550 && gyro_y>10050 && gyro_z>2550)
    {
    const char *msg1 ="r";
    rf_driver.send((uint8_t *)msg1, strlen(msg1));
    rf_driver.waitPacketSent();
    Serial.print("r");
    delay(1050);
    }
 }
