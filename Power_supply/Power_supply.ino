#define INP A0
#define OUT 2
double ipVal, opVal;

void setup() {
  pinMode(INP, INPUT);
  pinMode(OUT, OUTPUT);
  Serial.begin(9600);
  ipVal = 0;
  opVal = 0;
}

void loop() {
  ipVal = analogRead(INP);

//  Serial.println(ipVal);
  opVal = map(ipVal, 0, 676, 0, 255);
  Serial.println((opVal/255)*(4.926));
  analogWrite(OUT, opVal);
}
