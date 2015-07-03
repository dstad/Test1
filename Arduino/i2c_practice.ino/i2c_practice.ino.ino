#include <TinyWireS.h>

#define I2C_SLAVE_ADDRESS  0x04
int button = 3;
int i = 0;
//#define data [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10];

void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(requestEvent);
  pinMode(button, INPUT);                     // initialize I2C lib
  digitalWrite(button, HIGH);
}

void loop() {
  TinyWireS_stop_check();
}

void requestEvent()
{
  if(digitalRead(button == LOW))
  {
    TinyWireS.send(i);
  }
}

