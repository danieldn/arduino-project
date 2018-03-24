void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(1000);                       // pause, 1000 = 1 sec
  digitalWrite(LED_BUILTIN, LOW);    // off
  delay(1000);                      
}
