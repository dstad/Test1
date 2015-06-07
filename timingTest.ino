// **********************************************************
//   Need Header information here:
//   IV Arm Pump Test Program
// 
// *********************************************************
 
#include <Bounce2.h>

//#define DEBUG
#define DEBUGERROR

#ifdef DEBUG
#define debug(x)     Serial.print(x)
#define debugln(x)   Serial.println(x)
#else
#define debug(x)     // define empty, so macro does nothing
#define debugln(x)
#endif

#ifdef DEBUGERROR
#define debugerr(x)     Serial.print(x)
#define debugerrln(x)   Serial.println(x)
#else
#define debugerr(x)     // define empty, so macro does nothing
#define debuglnerr(x)
#endif


const int ledPin = 13;
const int pumpPin = 3;
const float sensorScale = 0.250;  // This is a max Heart Rate of 255 when scaled to the max 5 volt analog input from the pot
const int millisPerMin = 60000; // The number of milliseconds per minute for HR calculations
const int pulseOnWidth = 25;  // 100 miliseconds on time for the pump when in pulse mode
int upperlimitPin = 4;      // switch for the upper level limit
int lowerlimitPin = 6;      // switch for the lower level limit
int llpinVal = 1;
int ulpinVal = 1;
int delaySize = 2000;       //used to increment the amount of delay on the LED
int count = 0;              //used for the for loop count
int pumpSpeed = 0;         // used for the output speed of the pump
int pumpRunning = 0;       // keep track of the pump running or not
int sensorPin = A0;         // select the input pin for the potentiometer
int sensorValue = 0;        // variable to store the value coming from the sensor
int lastSensorValue = 0;    // used to track changes in the analog input we read for pump speed
int sensorCheck = 0;        // used to hold the delta between the last two sensor (pot) readings
int hrValue = 1;            // Start out with 1 so we don't divide by zero
int hrInMS = 0;             // Number of milliseconds between pump pulses to match the heart rate
long lastTimeCheck = 0;     // Using to keep track of # of milliseconds that have passed
long currentTimeCheck = 0;  // This will hold the current time on each pass so we can trigger certain things with lastTimeCheck
int timeDiff = 0;           // keeping track of the time differences
boolean pumpPulseOn = false; // keep track of on or off pulsing the pump while pump running is true
long nextTimeCheck = 0;      // Set to the next time interval of significance (rise of fall of the pulse wave)
int nextTransition = LOW;    // Set to the next transition of the pump motor is it turning off-LOW, or turning on-HIGH
int pulseOffWidth = 0;       // The length of the pulse off phase of the pump, based on Heart Rate calculations
boolean checkSensor = false; // used to indicate if we need to check the sensor or not.  Start with false



// Instantiate a Bounce object
Bounce debouncer = Bounce(); 

// the setup() method runs once, when the sketch starts

void setup() {
  // initialize the digital pin as input or output as required
  pinMode(ledPin, OUTPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(upperlimitPin, INPUT_PULLUP);
  pinMode(lowerlimitPin, INPUT_PULLUP);

  // read the value from the Potentiometer
  // sensorCheck was initialized false because we do read the value at the setup phase
  sensorValue = analogRead(sensorPin);    

  // After setting up the button, setup the Bounce instance :
  //debouncer.attach(upperlimitPin);
  debouncer.attach(lowerlimitPin);
  
  debouncer.interval(5); // interval in ms - how long do you wait for a bounce to stabilize 
  
  Serial.begin(9600); // USB is always 12 Mbit/sec, NEED TO PUT THIS IN A DEFINE SO WE DON"T DO IF NOT NEEDED 
  
  digitalWrite(upperlimitPin, HIGH);  // force the switches high to activate the pull up resistor
  digitalWrite(lowerlimitPin, HIGH);  // force the switches high to activate the pull up resistor
}


void loop() {
  // Update the Bounce instance
  debouncer.update();
  
  // Get the updated value from the debounced switch
  // We need to add in the upper limit switch also (future effort)
  llpinVal = debouncer.read();
  
  // Get a timecheck for the heart rate pulsing
  currentTimeCheck = millis();
  timeDiff = currentTimeCheck - lastTimeCheck;

  
    if(checkSensor == true)
    {
      // read the value from the Potentiometer
      sensorValue = analogRead(sensorPin);    

      // Check for a change in the value from the Pot that is significant enough to use
      sensorCheck = sensorValue - lastSensorValue;
      if (abs(sensorCheck) >= 16)
      {
         debug("Sensor check is: ");
         debug(sensorValue);
         debug("    ");
         debug(lastSensorValue);
         debug("    ");
         debugln(sensorCheck);
              
         // Set the last read to the new value
         lastSensorValue = sensorValue;
              
         // Determine the new rate that should be applied
         hrValue = sensorScale * sensorValue;
         hrInMS = millisPerMin / hrValue;
         pulseOffWidth = hrInMS - pulseOnWidth;
         debug("Heart Rate set to ");
         debug(hrValue);
         debug(" BPM And ");
         debug(pulseOffWidth);
         debugln(" For millisecond pulse");
         nextTimeCheck = pulseOnWidth;
        }
    }    
	// if the llpinVal is HIGH it means the switch has not be activated
    // so the pump should be running or turned on for the first time
    if(llpinVal == HIGH)
    {
      // don't check the sensor value while we are in the beating loop
	  // we need to fix so that we can check the sensor while in the beating loop
      checkSensor = false;
      if (timeDiff >= nextTimeCheck)
      {
        // The next "if" only occurs if the pump is off and needs to be started
        if (nextTransition == HIGH)
        {
          debugln("Motor on");
          pumpSpeed = 255;  // Get the pump spinning 
          pumpRunning = 1;  // pump is on
          // The pump just turned on so set the last time check to now
          currentTimeCheck = millis();
          lastTimeCheck = currentTimeCheck;
          analogWrite(pumpPin, pumpSpeed);
          digitalWrite(ledPin, HIGH);
          nextTransition = LOW;  // Pump is in the on mode so next is to go off-LOW
          nextTimeCheck = pulseOnWidth;  // pulseOnWidth determined in the sensor check with HR
        }
        else if (nextTransition == LOW)
        {
          debugln("Motor Shut Off");
          pumpSpeed = 0;
          pumpRunning = 0;
          pumpPulseOn = false;
          currentTimeCheck = millis();
          lastTimeCheck = currentTimeCheck;
          analogWrite(pumpPin, pumpSpeed);
          digitalWrite(ledPin, LOW);
          nextTransition = HIGH;
          nextTimeCheck = pulseOffWidth;
        }
        else
        {
          debugerrln("Error Occured");
        }
      }

    }
    else
    {
      pumpSpeed = 0;
      analogWrite(pumpPin, pumpSpeed);
      digitalWrite(ledPin, LOW);
      // Look at the Pots value and normalize for a heart rate
      // 0 is the min and 1023 is the max
      hrValue = int(sensorScale * sensorValue);
      hrInMS = millisPerMin / hrValue;
      // ok to check the sensor now
      checkSensor = true;
    }
      
}





























/******************************************************************************
      // The next "if" only occurs if the pump is off and needs to be started
      if (!pumpRunning)
      {
        debugln("Motor Was Not Running So Spin it up");
        spinup(pumpPin, ledPin, 3000);
        pumpSpeed = 255;  // Get the pump spinning 
	debugln("Set the pump running to 1");
        pumpRunning = 1;  // pump is on
        pumpPulseOn = true; // we are in the on state of the heart rate pulse
        // The pump just turned on so set the last time check to now
        currentTimeCheck = millis();
        lastTimeCheck = currentTimeCheck;
       
        // Look at the Pots value and normalize for a heart rate
        // 0 is the min and 1023 is the max
        hrValue = int(sensorScale * sensorValue);
        hrInMS = millisPerMin / hrValue;
        // Since this is the startup of the motor and we just used the sensor value for the first time set it to the last time
        lastSensorValue = sensorValue;
	debug("Heart Rate set to ");
        debug(hrValue);
        debug(" BPM And ");
        debug(hrInMS);
        debug(" For millisecond And ");
        debug(sensorValue);
        debugln(" For sensorVaule Read   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
      }
      //else
      //{
        // Check for a change in the value from the Pot that is significant enough to use
        sensorCheck = sensorValue - lastSensorValue;
        if (abs(sensorCheck) >= 25)
        {

          debug("Sensor check is: ");
          debug(sensorValue);
          debug("    ");
          debug(lastSensorValue);
          debug("    ");
          debugln(sensorCheck);
          
          // Set the last read to the new value
          lastSensorValue = sensorValue;
          
          // Determine the new rate that should be applied
          hrValue = sensorScale * sensorValue;
          hrInMS = millisPerMin / hrValue;
  	  debug("Heart Rate set to ");
          debug(hrValue);
          debug(" BPM And ");
          debug(hrInMS);
          debugln(" For millisecond pulse");
        }
        // The system is within limits and the pump should be running so pulse at HR
        // check the time elapsed since last go around;
        timeDiff = currentTimeCheck - lastTimeCheck;  
        //debug(timeDiff);
        //debug(" ----- ");
        //debug(hrInMS);
        //debugln(" is the current time difference and Heart Rate in MS  --  TOP");
        if (timeDiff >= (hrInMS - pumpPulseWidth)) 
        {
           // Turn the pump on, delay, and then shut it off
          //debugln("Pulse Time");
          if(pumpPulseOn)
          {
            debugln("ERROR::PUMP RUNNING WHEN PULSE TIME HIT!");
          }
          //debug(pumpSpeed);
          //debugln(" is the current pump speed");
          debug(timeDiff);
          debugln(" is the current time difference INSIDE");
          analogWrite(pumpPin, pumpSpeed);
          digitalWrite(ledPin, HIGH);  // light on to indicate pump runningpumpRunning
          pumpPulseOn = true;  // set the pump pulse flag to running
          // Set the last Time checked to the current
          lastTimeCheck = currentTimeCheck;
        }   
        if(pumpPulseOn)
        {
          // The pump is running in pulse mode so check if it is time to shut the pulse off
          if (timeDiff >= pumpPulseWidth)  //what if we don't read excatly at the pulse width?  what if we miss this by 1 millisecond or 2?
          {
             // Pump has been on for long enough so shut it off until the next pulse
             analogWrite(pumpPin, 0);
             digitalWrite(ledPin, LOW);  // light on to indicate pump runningpumpRunning
             debugln("Pulse Off");
             if (!pumpPulseOn)
             {
               debugln("ERROR::PUMP OFF WHEN PULSE WIDTH OFF HIT!");
             }
             pumpPulseOn = false;  // set the pump flag to NOT running
          }
        }
                
        // print debug every so often
        if (count == 500000)
        {
          debugln("Motor is running and we are otherwise: Doing Nothing");
          count = 0;
        }
        count++;
      //}
      //debugln("at the bottom of running");
    }
    else if (llpinVal == LOW)
    {
      // Shut off the pump if it is running
      if (pumpRunning)
      {
        debug(llpinVal);
        debugln(" - Was the input, Limit Hit, shut pump off");
        pumpSpeed = 0;
        analogWrite(pumpPin, pumpSpeed);  // shut the pump off
        pumpRunning = 0;  // pump is off
        digitalWrite(ledPin, LOW);  // shut off the LED
        digitalWrite(lowerlimitPin, HIGH);  // ensure the pullup resistor is high        
        //debugln("Delay for a bit to ensure the input bounce has stableized");
        //delay(100);
      }
      else
      {
        //pump is not running and it should not be
        if (count == 500000)
        {
          debugln("Pump is NOT running we are Doing Nothing");
          count = 0;
        }
        count++;
      }
    }
}

int spinup(int outputPin, int lightPin, int delayTime)
{
  debugln("Beginning spinup routine");
  analogWrite(outputPin, 255);
  digitalWrite(lightPin, HIGH);
  delay(delayTime);
  digitalWrite(lightPin, LOW);
  debugln("End spinup routine");
  return 0;
}
*******************************************************************************/  
