/* RGB LED strip driver
* This code for an Arduino Uno to be used as a driver for RGB LED strips.
* The program contains 5 different animations namely, flow, shift, blue_up, green_up, and red_up.
* The pin connection between the RGB LED strip and the Uno is given in the below table:
* |-------------------------------------|
* | Arduino Uno  |    RGB LED strip     |
* |-------------------------------------|
* |      2       |       Red pin        |
* |      3       |      Green pin       |
* |      4       |      Blue pin        |
* |      5       |  White (Enable) pin  |
* |     GND      |      Black pin       |
* |-------------------------------------|
* 
*/

/// Macros for pin definitions
#define CTRL_R 2
#define CTRL_G 3
#define CTRL_B 4
#define CTRL_MAIN 5

/// cycle time in ms
float PERIOD=5;
/// brightness step per cycle
float STEP=3; 

/// Initial Red, Green, and Blue values
float R_val = 100;
float G_val = 0;
float B_val = 0;

/// Function to set PWM output to required pin
void pwmWrite(int pin, float duty);

/// Functions for RGB animations
void flow();
void shift();
void blue_up();
void green_up();
void red_up();

/// Main/init function to setup pins and initial values
void setup() 
{
  pinMode(CTRL_R, OUTPUT);
  pinMode(CTRL_G, OUTPUT);
  pinMode(CTRL_B, OUTPUT);
  pinMode(CTRL_MAIN, OUTPUT);

  digitalWrite(CTRL_MAIN, HIGH);
  digitalWrite(CTRL_R, HIGH);
  digitalWrite(CTRL_G, HIGH);
  digitalWrite(CTRL_B, HIGH);
}

/// Loop function to call different animations in a fixed order
void loop() 
{
  flow();
  red_up();
  shift();
  blue_up();
  red_up();
  flow();
  green_up();
  blue_up();
  shift();
  shift();
  shift();
  shift();
  red_up();
  flow();
  green_up();
  blue_up();
  red_up();
  shift();
  flow();
  flow();
  red_up();
  flow();
}

void pwmWrite(int pin, float duty)
{
  duty = duty/100.0;
  digitalWrite(pin, LOW);
  delay(PERIOD*duty);
  digitalWrite(pin, HIGH);
  delay(PERIOD*(1-duty));
}

void flow()
{
  for (; B_val <= 100; B_val+=STEP)
  {
    pwmWrite(CTRL_R, R_val);
    pwmWrite(CTRL_G, G_val);
    pwmWrite(CTRL_B, B_val);
  }

  for (; R_val >= 0; R_val-=STEP)
  {
    pwmWrite(CTRL_R, R_val);
    pwmWrite(CTRL_G, G_val);
    pwmWrite(CTRL_B, B_val);
  }

  for (; G_val <= 100; G_val+=STEP)
  {
    pwmWrite(CTRL_R, R_val);
    pwmWrite(CTRL_G, G_val);
    pwmWrite(CTRL_B, B_val);
  }

  for (; B_val >= 0; B_val-=STEP)
  {
    pwmWrite(CTRL_R, R_val);
    pwmWrite(CTRL_G, G_val);
    pwmWrite(CTRL_B, B_val);
  }

  for (; R_val <= 100; R_val+=STEP)
  {
    pwmWrite(CTRL_R, R_val);
    pwmWrite(CTRL_G, G_val);
    pwmWrite(CTRL_B, B_val);
  }

  for (; G_val >= 0; G_val-=STEP)
  {
    pwmWrite(CTRL_R, R_val);
    pwmWrite(CTRL_G, G_val);
    pwmWrite(CTRL_B, B_val);
  }
}

void shift()
{
  digitalWrite(CTRL_R, LOW);
  delay(100);
  digitalWrite(CTRL_R, HIGH);
  digitalWrite(CTRL_G, LOW);
  delay(100);
  digitalWrite(CTRL_G, HIGH);
  digitalWrite(CTRL_B, LOW);
  delay(100);
  digitalWrite(CTRL_B, HIGH);
}

void blue_up()
{
  digitalWrite(CTRL_R, HIGH);
  digitalWrite(CTRL_G, HIGH);
  
  for (B_val = 0; B_val <= 100; B_val+=1)
    pwmWrite(CTRL_B, B_val);
}

void red_up()
{
  digitalWrite(CTRL_B, HIGH);
  digitalWrite(CTRL_G, HIGH);
  
  for (R_val = 0; R_val <= 100; R_val+=1)
    pwmWrite(CTRL_R, R_val);
}

void green_up()
{
  digitalWrite(CTRL_R, HIGH);
  digitalWrite(CTRL_B, HIGH);
  
  for (G_val = 0; G_val <= 100; G_val+=1)
    pwmWrite(CTRL_G, G_val);
}


