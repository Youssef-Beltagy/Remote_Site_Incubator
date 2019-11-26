
byte sensorPin =  2;
byte rstPin = 1;

volatile unsigned long count = 0;  

void pulseCounter()
{
  count++;
}

void rstCounter()
{
  count = 0;
}

void setup()
{
  
  Serial.begin(9600);

  pinMode(sensorPin, INPUT);
  pinMode(rstPin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);
  attachInterrupt(digitalPinToInterrupt(rstPin), rstCounter, FALLING);

}


void loop()
{
  
  delay(200);
  unsigned long temp = count;
  Serial.println(temp);
  
}
