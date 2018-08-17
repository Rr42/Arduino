int pin= 13;

void setup() {
  pinMode(pin,OUTPUT);
  digitalWrite(pin,HIGH);
}

void loop() {
  digitalWrite(pin,LOW);
  delay(100);
  digitalWrite(pin,HIGH);
  delay(100);
}
