/*
 * Program for controlling the CD4017BD decade counter.
 */
int Reset = 22;
int Clock = 7;
int button = 30;

boolean button_input()
{
  /*
   * Debounsing button input
   */
   if(digitalRead(button)==HIGH)
   {
    delay(500);
    return true;
   }
   
   return false;
}
void clk()
{
  digitalWrite(Clock,HIGH);
  delay(1);
  digitalWrite(Clock,LOW);
}

void rst()
{
  digitalWrite(Reset,HIGH);
  delay(1);
  digitalWrite(Reset,LOW);
}

void setup() 
{
  pinMode(Reset,OUTPUT);
  pinMode(Clock,OUTPUT);  
}

void loop() 
{
  if(button_input())
    clk();
 delay(100);
}
