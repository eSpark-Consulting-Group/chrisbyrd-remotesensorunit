int buzzerPin = 21;

void setup() {
  pinMode(buzzerPin, OUTPUT);


}

void loop() {
digitalWrite(buzzerPin, HIGH);
  delay(5000); // Approximately 10% duty cycle @ 1KHz
  digitalWrite(buzzerPin, LOW);
  delay(5000);
}
