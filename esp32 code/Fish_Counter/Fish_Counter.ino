
const byte interruptPin = 2;
volatile unsigned short int count = 0;

volatile unsigned long ltime = millis();
const long LowerTimeThr = 6; // set arbitrarily for now (and ever). A HACK
const long UpperTimeThr = 1000;

void setup() {

  Serial.begin(115200);
  //Serial.print("S");
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), increment, CHANGE);
  esp_sleep_enable_timer_wakeup(10000000);

}

void loop() {
  //delay(1000);
  Serial.print("C:");
  Serial.println((int)count);


  //If you were to use ext1, you would use it like
  //esp_sleep_enable_ext1_wakeup(BUTTON_PIN_BITMASK,ESP_EXT1_WAKEUP_ANY_HIGH);

  //Go to sleep now
  //Serial.println("Going to sleep now");
  esp_light_sleep_start();

}


void increment() {
  if(digitalRead(interruptPin) == HIGH){// What about if LOW and time is not
    ltime = millis();
  }else if(digitalRead(interruptPin) == LOW && (millis() - ltime > LowerTimeThr) && (millis() - ltime < UpperTimeThr)){// Consider ltime - millis in large values like 100000
    count++;
  }
}
