int apin = A0;
int pino=13;
int aval;
void setup() {
   pinMode(pino,OUTPUT);
   Serial.begin(9600);
}

void loop() {
   aval= analogRead(apin);
   //aval=1000-aval;
   //aval+=50;
   //aval-=70;
   aval=100%aval;
   aval=100-aval;
   analogWrite(pino,aval);
   Serial.println(aval);
   delay(100);
  
}
