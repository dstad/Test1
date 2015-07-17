int A = 4;
int B = 5;
int C = 6;
int D = 8;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(A, INPUT);
  pinMode(B, INPUT);
  pinMode(C, INPUT);
  pinMode(D, INPUT);
  digitalWrite(A, HIGH);
  digitalWrite(B, HIGH);
  digitalWrite(C, HIGH);
  digitalWrite(D, HIGH);
  Serial.println("Hello World");
}

void loop() {
  if (! digitalRead(A)) {
    Serial.println("I recieved: A");
  }
  if(! digitalRead(B)) {
    Serial.println("I recieved: B");
  }
  if(! digitalRead(C)) {
    Serial.println("I recieved: C");
  }
  if(! digitalRead(D)) {
    Serial.println("I recieved: D");
  }
}

