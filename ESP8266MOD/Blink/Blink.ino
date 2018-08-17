int led = LED_BUILTIN;
void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);//LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(led, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                    // but actually the LED is on; this is because 
                                    // it is acive low on the ESP-01)
  Serial.println(led);                            
  delay(200);                      
  digitalWrite(led, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(100);                      
}
