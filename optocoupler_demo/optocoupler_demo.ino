#define LED 10
#define LDR A0
void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(LED, HIGH);
  Serial.println(analogRead(LDR));
  delay(1000);
  
  digitalWrite(LED, LOW);
  Serial.println(analogRead(LDR));
  delay(1000);
}
