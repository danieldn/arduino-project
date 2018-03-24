int ledPin = 13;

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  digitalWrite(ledPin, HIGH);   // LED on
  delay(2000);
  digitalWrite(ledPin, LOW);
  delay(2000);
}

