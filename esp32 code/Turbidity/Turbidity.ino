void setup() {
  Serial.begin(115200); //Baud rate: 9600
}
void loop() {
  int sensorValue = analogRead(13);// read the input on analog pin 0:
  float voltage = sensorValue * (3.3 / 4095.0)*2; // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  Serial.print("Voltage: ");
  Serial.print(voltage); // print out the value you read:
  Serial.print(" | Turbidity: ");
  Serial.println(-1120.4 * voltage * voltage + 5742.3 * voltage - 4352.9);
  delay(500);
}
