#define lc 5
int avg[12];

void setup() 
{
   pinMode(A0,OUTPUT);
   pinMode(A1,INPUT);
   pinMode(A2,INPUT);
   pinMode(A3,INPUT);
   pinMode(A3,INPUT);
   pinMode(A4,INPUT);
   pinMode(A5,INPUT);
   pinMode(A6,INPUT);
   pinMode(A7,INPUT);
   pinMode(A8,INPUT);
   pinMode(A9,INPUT);
   pinMode(A10,INPUT);
   pinMode(A11,INPUT);
   pinMode(13,OUTPUT);
   Serial.begin(9600);
   
   digitalWrite(13,LOW);
   digitalWrite(A0,HIGH);
   
}

void loop() 
{
   for(int i=0;i<12;i++)
   {
     avg[i]=0;
   }
   for(int i=0;i<lc;i++)
   {
      avg[1]+=analogRead(A1);
      avg[2]+=analogRead(A2);
      avg[3]+=analogRead(A3);
      avg[4]+=analogRead(A4);
      avg[5]+=analogRead(A5);
      avg[6]+=analogRead(A6);
      avg[7]+=analogRead(A7);
      avg[8]+=analogRead(A8);
      avg[9]+=analogRead(A9);
      avg[10]+=analogRead(A10);
      avg[11]+=analogRead(A11);
   }
   for(int i=0;i<12;i++)
   {
      avg[i]/=lc;
   }
   
      
   Serial.print("A1 ");Serial.print(Read(avg[1]));
   
   Serial.print("; A2 ");Serial.print(Read(avg[2]));
   
   Serial.print("; A3 ");Serial.print(Read(avg[3]));
   
   Serial.print("; A4 ");Serial.print(Read(avg[4]));
   
   Serial.print("; A5 ");Serial.print(Read(avg[5]));
   
   Serial.print("; A6 ");Serial.print(Read(avg[6]));
   
   Serial.print("; A7 ");Serial.print(Read(avg[7]));
   
   Serial.print("; A8 ");Serial.print(Read(avg[8]));
   
   Serial.print("; A9 ");Serial.print(Read(avg[9]));
   
   Serial.print("; A10 ");Serial.print(Read(avg[10]));
   
   Serial.print("; A11 ");Serial.println(Read(avg[11]));
   
   delay(100);

   int flag=1;

  for(int i=1;i<=11;i++)
  {
    if(Read(avg[i])==0)
       flag=0;
  }

  if (flag==1)
     digitalWrite(13,HIGH);
  else 
     digitalWrite(13,LOW);
}

int Read(int i)
{
   if(i<0)
      return -2;
   else if(i<400)
      return -1;
   else if(i<450)
      return 0;
   else if(i<500)
      return 1;
   else
      return 2;
  
}
