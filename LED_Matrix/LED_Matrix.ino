

void setup() 
{
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
}

void loop() 
{
 
  
//Row by row
  for(int i=0;i<2;++i)
    pattern_RbR();

//Border
  for(int i=0;i<500;++i)
    pattern_Border();

//X
  pattern_X();
}

void pattern_RbR()
{
  for(int i=1;i<=3;++i)
    for(int j=1;j<=3;++j)
    {
      Clear();
      
      led(i,j,1);

      delay(200);
    }
  Clear();
}

void pattern_Border()// Border
{
  for(int i=1;i<=3;++i)
   for(int j=1;j<=3;++j)
    {
      if(i == 2 && j==2)
        continue;
      Clear();
      
      led(i,j,1);

      delay(1);
    }
  Clear();
}

void pattern_X()//X
{ 
  Clear();
  led(1,1,1);
  led(3,1,1);
  delay(1000);
  Clear();
  led(2,2,1);
  delay(1000);
  Clear();
  led(3,3,1);
  led(1,3,1); 
  delay(1000);
   
  for(int i=0;i<2;++i)
  {
    for(int i=0;i<100;++i)
    {
      Clear();
      led(1,1,1);
      led(3,1,1);
      delay(5);
      Clear();
      led(2,2,1);
      delay(5);
      Clear();
      led(3,3,1);
      led(1,3,1); 
     delay(5);
    }

    Clear();
    delay(1000);
  }
  
  Clear();
  delay(1000);
}

void Clear()
{
  r(1,0);
  r(2,0);
  r(3,0);
  c(1,0);
  c(2,0);
  c(3,0);
}

void led(int rno,int cno,int P)//High: P == 1,Low: P == 0
{
  r(rno,P);
  c(cno,P);
}

void r(int no,int P)//High: P == 1,Low: P == 0; no={1,2,3}
{
  if(P == 1)
  {
    if(no == 1)
      analogWrite(7,16);
    else if(no == 2)
      analogWrite(6,16);
    else if(no == 3)
      analogWrite(5,16);
  }
  else //P == 0
  {
    if(no == 1)
      digitalWrite(7,LOW);
    else if(no == 2)
      digitalWrite(6,LOW);
    else if(no == 3)
      digitalWrite(5,LOW);
  }
}


void c(int no,int P)//High: P == 1,Low: P == 0; no={1,2,3}
{
  if(P == 1)
  {
    if(no == 1)
      digitalWrite(4,LOW);
    else if(no == 2)
      digitalWrite(3,LOW);
    else if(no == 3)
      digitalWrite(2,LOW);
  }
  else //P == 0
  {
    if(no == 1)
      digitalWrite(4,HIGH);
    else if(no == 2)
      digitalWrite(3,HIGH);
    else if(no == 3)
      digitalWrite(2,HIGH);
  }
}

/*  
   *   (0,0) -> (4,7)
   *   (3,3) -> (5,2)
*/

