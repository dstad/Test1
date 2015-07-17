int FsrPin = 0;
int ledPin1 = 15;
int ledPin2 = 16;
int ledPin3 = 17;
int ledPin4 = 18;
int LEDbrightness;
int FsrReading;
int incomingByte = 0;
int bytesAvailable = 0;
int i = 0;
int readSuccess = 0;
int writeCount = 0;
void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(13, LOW);
  
}

void loop() 
{
  FsrReading = analogRead(FsrPin);

  //Serial.print("Analog reading = ");
  if (writeCount == 5000)
  {
    Serial.print(FsrReading);
    writeCount = 0;
  }
  else
  {
    writeCount++;
  }
  //delay(1000);

  bytesAvailable = Serial.available();

  if (bytesAvailable)
  {
     for (i=0;i<bytesAvailable; i++)
        {
          
            incomingByte = Serial.read();
            readSuccess = 1;
            //digitalWrite(15, HIGH);
            //delay(200);
            //digitalWrite(15, HIGH);
        }

        bytesAvailable=0;
        
        //digitalWrite(13, HIGH);
        //delay(1000);
        //digitalWrite(13, LOW);
        
    
    if (readSuccess == 1)
    {
      /*digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);*/
        switch ((int)incomingByte)
        {
          case 1:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin4, HIGH);
            break;  
          case 2:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin4, HIGH);
            break;   
          case 3:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
            digitalWrite(ledPin4, HIGH);
            break;         
          case 4:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
            digitalWrite(ledPin4, LOW);                    
            break;                                  

          default:
            digitalWrite(ledPin1, HIGH);
            digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin4, HIGH);
            break;
        }
        readSuccess = 0;
    }
  }

}
