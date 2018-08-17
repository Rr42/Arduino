#define MAX 500
int ANALOG_IN=A0;
int val;
int i=0;
int cap=5;
int t=0;
int re;
void setup() {
  Serial.begin(9600); 
  pinMode(cap,OUTPUT);
}
void loop() {
  analogWrite(cap,i);
  if (t==0 && i==MAX)
     t=1;
  else
     t=0;
  if(i!=MAX)
     i++;
  else
     i=0;
  val = analogRead(ANALOG_IN);                                              
  Serial.write( 0xff );                                                         
  Serial.write( (val >> 8) & 0xff );                                            
  Serial.write( val );
}

