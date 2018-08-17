int input_M = A0;

void setup() {
  Serial.begin(9600);
  pinMode(input_M, INPUT);
}

void loop() {
  int reading = map(analogRead(input_M),0,63,0,10);
  //Moisture
  //map(analogRead(input_M),-5,53,0,10);
  //pH
  //map(analogRead(input_M),-11,53,10,3);
  Serial.print(analogRead(input_M));
  Serial.print("r1 = ");
  Serial.print(reading);
  reading = log(analogRead(input_M))/log(2);//map(analogRead(input_M),-11,53,10,3);
  Serial.print(" r2 = ");
  Serial.println(reading);
  delay(500);
}
