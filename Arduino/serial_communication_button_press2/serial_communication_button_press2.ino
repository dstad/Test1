#define SINGLE 0
#define CONT   1

int A = 4;
int currentBtnStateA = 0;
int lastBtnStateA = 0;
int B = 5;
int currentBtnStateB = 0;
int lastBtnStateB = 0;
int C = 6;
int currentBtnStateC = 0;
int lastBtnStateC = 0;
int D = 8;
int currentBtnStateD = 0;
int lastBtnStateD = 0;
int modePin = 14;
int mode = 1;
int incomingByte = 0;
int bytesAvailable = 0;
int i = 0;
int readSuccess = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  digitalWrite(15, HIGH);
  digitalWrite(13, LOW);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);
  pinMode(modePin, INPUT_PULLUP);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  digitalWrite(modePin, HIGH);
  //Serial.print("Hello World");
}

void loop() 
{
  if (! digitalRead(modePin))
  {
    mode = SINGLE;
  }
  else 
  {
    mode = CONT;
  }
  if (! digitalRead(A)) 
  {
/******************************************    
    
    bytesAvailable = Serial.available();
    for (i=0;i++;i<bytesAvailable)
    {
      incomingByte = Serial.read();
      if (incomingByte > 0)
      {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
      }
    }
******************************************/    
    if (mode == SINGLE)
    {
      currentBtnStateA = 1;
      if (lastBtnStateA == currentBtnStateA)
      {
      //fail through
      }
      else
      {
        lastBtnStateA = currentBtnStateA;
        Serial.print("sent A");
        
      }
    }
    else if (mode == CONT)
    {
      Serial.print("sent A");
    }
  }
  else
  {
    lastBtnStateA = 0;
    currentBtnStateA = 0;
  }
      
  if (! digitalRead(B)) 
  {
/******************************************    
    bytesAvailable = Serial.available();
    
    for (i=0;i++;i<bytesAvailable)
    {
      incomingByte = Serial.read();
      if (incomingByte > 0)
      {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
      }
    }
******************************************/    
    if (mode == SINGLE)
    {
       currentBtnStateB = 1;
      if (lastBtnStateB == currentBtnStateB)
      {
        //fall through 
      }
      else
      {
        lastBtnStateB = currentBtnStateB;
        Serial.print("sent B");
      }
    }
    else if (mode == CONT)
    {
      Serial.print("sent B");
    }
  }
  else
  {
    lastBtnStateB = 0;
    currentBtnStateB = 0;
  }
  
    
  if (! digitalRead(C))
  {

/******************************************    
    bytesAvailable = Serial.available();
    
    for (i=0;i++;i<bytesAvailable)
    {
      incomingByte = Serial.read();
      if(incomingByte > 0)
      {
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
        delay(1000);
        digitalWrite(13, HIGH);
        delay(1000);
        digitalWrite(13, LOW);
      }
    }
****************************************/    
    if (mode == SINGLE)
    {
      currentBtnStateC = 1;
      if (lastBtnStateC == currentBtnStateC)
      {
        //fall through
      }
      else
      {
        lastBtnStateC = currentBtnStateC;
        Serial.print("sent C");
      }
    }
    else if (mode == CONT)
    {
      Serial.print("sent C");
    }
  }
  else
  {
    lastBtnStateC = 0;
    currentBtnStateC = 0;
  }
  
  if (! digitalRead(D)) 
  {

    if (mode == SINGLE)
    {
      currentBtnStateD = 1;
      if (lastBtnStateD  == currentBtnStateD)
      {
        //fall through
      }
      else
      {
        lastBtnStateD = currentBtnStateD;
        Serial.print("sent D");
      }
    }
    else if (mode == CONT)
    {
      Serial.print("sent D");
    }
    

    
  }
  else
  {
    currentBtnStateD = 0;
    lastBtnStateD = 0;
  }


//void serialEvent()
//{
  bytesAvailable = Serial.available();
    if (bytesAvailable)
    {
      //Serial.flush();

        
        
        for (i=0;i<bytesAvailable; i++)
        {
          
            incomingByte = Serial.read();
            readSuccess = 1;
            digitalWrite(15, LOW);
            delay(200);
            digitalWrite(15, HIGH);
        }

        bytesAvailable=0;
        
        //digitalWrite(13, HIGH);
        //delay(1000);
        //digitalWrite(13, LOW);
        
    
    if (readSuccess == 1)
    {
        switch (incomingByte)
        {
          case 'A':
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);
            break;  
          case 66:LO
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);          
            break;   
          case 'C':
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);          
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);
            break;         
          case 'D':
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);          
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);
            digitalWrite(13, HIGH);
            delay(500);
            digitalWrite(13, LOW);
            delay(500);                    
            break;                                  

          default:
            digitalWrite(13, HIGH);
            delay(5000);
            digitalWrite(13, LOW);
            break;
/******************************          
          delay(50);
          digitalWrite(13, HIGH);
          delay(50);
          digitalWrite(13, LOW);
          delay(50);          
          digitalWrite(13, HIGH);
          delay(50);
          digitalWrite(13, LOW);
          delay(50);
          digitalWrite(13, HIGH);
          delay(50);
          digitalWrite(13, LOW);
          delay(50);          
           digitalWrite(13, HIGH);
          delay(50);
          digitalWrite(13, LOW);
          delay(50);
          digitalWrite(13, HIGH);
          delay(50);
          digitalWrite(13, LOW);
          delay(50);
          break;                                 
******************************/             
      }
      readSuccess = 0;
   }
    }
}
      


