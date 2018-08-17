

int p1=A0;
int p2=A1;
//int p3=pow
int p4=A2;
int p5=A3;
int p6=A4;
int p7=A5;
int p8=A6;
int p9=A7;
int p10=A8;
int p11=A9;

void setup() {
  pinMode(p1,INPUT);
  pinMode(p2,INPUT);
  pinMode(p4,INPUT);
  pinMode(p5,INPUT);
  pinMode(p6,INPUT);
  pinMode(p7,INPUT);
  pinMode(p8,INPUT);
  pinMode(p9,INPUT);
  pinMode(p10,INPUT);
  pinMode(p11,INPUT);
  //digitalWrite(p3,HIGH);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Pin=");
  if (analogRead(p1)==HIGH)
     Serial.print("1,");
  if (analogRead(p2)==HIGH)
     Serial.print("2,");
  if (analogRead(p4)==HIGH)
     Serial.print("4,");
  if (analogRead(p5)==HIGH)
     Serial.print("5,");
  if (analogRead(p6)==HIGH)
     Serial.print("6,");
  if (analogRead(p7)==HIGH)
     Serial.print("7,");
  if (analogRead(p8)==HIGH)
     Serial.print("8,");
  if (analogRead(p9)==HIGH)
     Serial.print("9,");
  if (analogRead(p10)==HIGH)
     Serial.print("10,");
  if (analogRead(p11)==HIGH)
     Serial.print("11");
  Serial.println(" "); 
 delay(100);  
}
