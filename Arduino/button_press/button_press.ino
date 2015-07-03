#define SWITCH 0
#define Pi 1
//#define Pi  2


// the setup routine runs once when you press reset:

void setup() {
  //initalize the LED pin as an output
  pinMode(Pi, OUTPUT);
  // initialize the SWITCH pin as an input

  pinMode(SWITCH, INPUT);
  //... with a pull up)

  //pinMode(Pi, OUTPUT);  //output connection to pi

  digitalWrite(SWITCH, HIGH);

  //digitalWrite(Pi, HIGH);
}

// the loopm routine runs over and over again forever:

void loop() {
  if (! digitalRead(SWITCH)){ // if the button is pressed
    digitalWrite(Pi, HIGH);  // light up LED
    //digitalWrite(Pi, LOW);
  } else {
    digitalWrite(Pi, LOW);   // otherwise, turn it off
    //digitalWrite(Pi, HIGH);
  }
}

