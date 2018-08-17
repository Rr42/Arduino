#include<LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);
int pinLDR=A0;
void setup()
{
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("Hellow");
  lcd.setCursor(0,1);
  lcd.print("How are you?");
}
void loop()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(analogRead(pinLDR));
  delay(100);
}

