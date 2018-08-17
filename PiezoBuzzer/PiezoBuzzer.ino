int pins=A12;
void setup() {
   pinMode(pins,OUTPUT);
}

void loop() {
  digitalWrite(pins,HIGH);
  delay(10);
  digitalWrite(pins,LOW);
  delay(1000);  
}


