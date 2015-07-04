#include <TinyWireS.h>

#define I2C_SLAVE_ADDRESS  0x04
int i = 0;
int count;
int someByte;
//#define data [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(requestEvent);
  TinyWireS.onReceive(receiveEvent);
  
  pinMode(1, OUTPUT);                     // initialize I2C lib
  digitalWrite(1, LOW);
}

void loop() {
  TinyWireS_stop_check();
}

void requestEvent()
{
  TinyWireS.send(i);
  i++;
}

void receiveEvent(uint8_t)
{
  count = TinyWireS.available();
  if(count > 0)
  {
    for (i = 0; i < count; i++)
    {
      someByte = TinyWireS.receive();
      if (someByte == 10)
      {
         digitalWrite(1, HIGH);
        delay(1000);
        digitalWrite(1, LOW);
      }
    }
  }
 
}

