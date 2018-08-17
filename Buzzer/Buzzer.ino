int var=0;
void setup() {
  pinMode(13,OUTPUT);
}

void loop() {
  var++;
  digitalWrite(13,var);
  delay(10);
  digitalWrite(13,LOW);
  delay(1000);
}
