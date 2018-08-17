float val=0;

void setup() {
  pinMode(A0,INPUT);

  Serial.begin(9600);

}

void loop() {
  val=((analogRead(A0)-515)/3.76);

  Serial.println(val);

  delay(100);


}
