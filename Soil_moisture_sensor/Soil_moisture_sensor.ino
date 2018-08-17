int ip = A0;
double moisture = 0;
int data[5] = {100,20,50,3,75};

int send(int num)
{
  do 
  {
    switch((int)num%10)
    {
      case 0: Serial.print('0');break;
      case 1: Serial.print('1');break;
      case 2: Serial.print('2');break;
      case 3: Serial.print('3');break;
      case 4: Serial.print('4');break;
      case 5: Serial.print('5');break;
      case 6: Serial.print('6');break;
      case 7: Serial.print('7');break;
      case 8: Serial.print('8');break;
      case 9: Serial.print('9');break;
    }
    num /= 10;
  }while(num != 0);
  Serial.println(';');
   return 0;
}

void setup() {
  Serial.begin(1200);
  pinMode(ip,INPUT);
}

void loop() {
  for(int i=0;i<5;++i)
  {
    send(data[i]);
    delay(1000);
  }
  /*
  moisture = analogRead(ip);
  moisture = map(moisture,1017,0,0,100);
  send(moisture);
  //Serial.print("input= ");
  //Serial.println(moisture);
  delay(1000);
  */
}
