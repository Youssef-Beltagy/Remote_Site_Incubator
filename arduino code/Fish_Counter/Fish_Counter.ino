
const byte interruptPin = 3;
volatile unsigned short int count = 0;

volatile unsigned long ltime = millis();
const long LowerTimeThr = 6; // set arbitrarily for now (and ever). A HACK
const long UpperTimeThr = 1000;

void setup() {

  Serial.begin(9600);
  Serial.print("S");
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), increment, CHANGE);
}

void loop() {
  
  Serial.print("C:");
  Serial.println((int)count);

}


void increment() {
  if(digitalRead(interruptPin) == HIGH){// What about if LOW and time is not
    ltime = millis();
  }else if(digitalRead(interruptPin) == LOW && (millis() - ltime > LowerTimeThr) && (millis() - ltime < UpperTimeThr)){// Consider ltime - millis in large values like 100000
    count++;
  }
}
