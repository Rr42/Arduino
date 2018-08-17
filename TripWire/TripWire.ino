int apin = A15;
int pino=9,alarm=0;
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
  
   if (aval>25)
   {
      if(alarm==100)
         alarm=0;
      else
         alarm=100;      
      digitalWrite(pino,alarm);
      delay(1000);
   } 
   
   //analogWrite(pino,aval);
   Serial.println(aval);
}
