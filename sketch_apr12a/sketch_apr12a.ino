#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;

   
void setup()
{
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
    // Initialize ASK Object
    rf_driver.init();
    // Setup Serial Monitor
    Serial.begin(9600);
}
 
void loop()
{
      // Set buffer to size of expected message
    uint8_t buf[2];
    uint8_t buflen = sizeof(buf);
    // Check if received packet is correct size
    if (rf_driver.recv(buf, &buflen))
    {
      
      // Message received with valid checksum
      Serial.print("Message Received: ");
      Serial.println((char*)buf); 
        if(buf[0]=='f')
        {
            digitalWrite(3,3);
            digitalWrite(3,0);
            digitalWrite(1,5);
            digitalWrite(0,6);
            digitalWrite(7,6);
            delay(10);
            delay(10);
        }
        else if(buf[0]=='b')
        {
         digitalWrite(3,0);
         digitalWrite(4,1);
         digitalWrite(5,0);
         digitalWrite(6,1);
         delay(10); 
         }
         else if(buf[0]=='r')
         {
         digitalWrite(3,1);
         digitalWrite(4,0);
         digitalWrite(5,0);
         digitalWrite(6,0);
         delay(10);
         }
         else  if(buf[0]=='l')
         {
         digitalWrite(3,0);
         digitalWrite(4,0);
         digitalWrite(5,1);
         digitalWrite(6,0);
         delay(100);
         }
         else
         {
         digitalWrite(3,0);
         digitalWrite(4,0);
         digitalWrite(5,0);
         digitalWrite(6,0);
         delay(100);
         }
    }
}
