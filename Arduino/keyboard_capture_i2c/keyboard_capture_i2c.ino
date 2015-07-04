#include <TinyWireS.h>

#define I2C_SLAVE_ADDRESS 0x04
int count;
int i = 0;
int someByte;

void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(requestEvent);
  TinyWireS.onReceive(receiveEvent);

  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
}

void loop(){
  TinyWireS_stop_check();
}

void requestEvent ()
{
  TinyWireS.send(someByte);
}

void receiveEvent(uint8_t)
{
  count = TinyWireS.available();
  if(count > 0)
  {
    for (i = 0; i < count; i++)
    {
      if (someByte = TinyWireS.receive())
      {
        digitalWrite(1, HIGH);
        delay(1000);
        digitalWrite(1, LOW);
      }
    }
  }
}

