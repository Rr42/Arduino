int s1=7;
int s2=8;
int power=36;

void op(int t)
{
  digitalWrite(power,HIGH);
  digitalWrite(s1,HIGH);
  digitalWrite(s2,HIGH); 
  delay(t);
  digitalWrite(power,LOW);
}

void cl(int t)
{
  digitalWrite(power,HIGH);
  digitalWrite(s1,LOW);
  digitalWrite(s2,LOW); 
  delay(t);
  digitalWrite(power,LOW);
}


void setup() {
  pinMode(s1,OUTPUT);
  pinMode(s2,OUTPUT);
  pinMode(power,OUTPUT);
  
  digitalWrite(power,LOW);
}

void loop() 
{
  
}

