/*
 * For a 3x3x3 LED Matrix
*/

int LED_off[3][3][3] = {0,0,0,  0,0,0,  0,0,0,
                        0,0,0,  0,0,0,  0,0,0,
                        0,0,0,  0,0,0,  0,0,0};


int LED_ptt1[3][3][3] = {0,0,1,  
                         0,1,0,  
                         1,0,0,

                         1,0,0,
                         0,1,0,
                         0,0,1,

                         0,1,0,
                         1,1,1,
                         0,1,0};
                       

                      

int pow_pin[9] = {52,50,48,46,44,42,40,38,36}; // Power pins (+ pins)
int gnd_pin[9] = {53,51,49,47,45,43,41,39,37}; // Gorund pins (- pins)

int LED_print(int x, int y, int z, int Pow) // Pow =1 => HIGH; Pow =0 => LOW
{
    /* 
     *         O  O  O _- P0
     *         O  O  O _- P1
     *         O  O  O _- P2
     *         |  |  | 
     *         G0 G1 G2
     *         
     *         O  O  O _- P3
     *         O  O  O _- P4
     *         O  O  O _- P5
     *         |  |  |
     *         G3 G4 G5
     *         
     *         O  O  O _- P6
     *         O  O  O _- P7
     *         O  O  O _- P8 
     *         |  |  |
     *         G6 G7 G8   
     *         
     *  Y (P)       
     *  ^
     *  |   
     *  O _-> X (G)       
     *  |
     *  |
     *  Z
    */ 

    if(x<0 or y<0 or z<0)
      return -1;

    int P[3],G[3];

    if(z==1)
    {
      P[0] = pow_pin[0]; P[1] = pow_pin[1]; P[2] = pow_pin[2];
      G[0] = gnd_pin[0]; G[1] = gnd_pin[1]; G[2] = gnd_pin[2];
    }
    else if(z==2)
    {
      P[0] = pow_pin[3]; P[1] = pow_pin[4]; P[2] = pow_pin[5];
      G[0] = gnd_pin[3]; G[1] = gnd_pin[4]; G[2] = gnd_pin[5];
    }
    else
    {
      P[0] = pow_pin[6]; P[1] = pow_pin[7]; P[2] = pow_pin[8];
      G[0] = gnd_pin[6]; G[1] = gnd_pin[7]; G[2] = gnd_pin[8];
    }

    if (Pow == 1)
    {
      digitalWrite(P[x-1],HIGH);
      digitalWrite(G[y-1],LOW);
    }
    else
    {
      digitalWrite(P[x-1],LOW);
      digitalWrite(G[y-1],HIGH);
    }
}

void print_Mx(int led[3][3][3]) // Print with respect to the given matrix
{
  for(int i=0;i<3;++i)
    for(int j=0;j<3;++j)
      for(int k=0;k<3;++k)
      {
        LED_print(i+1,j+1,k+1,led[k][i][j]);
        delay(0.5);
        LED_print(j+1,i+1,k+1,0);
      }
}

void setup() {
  for(int i=0;i<9;++i)
  {
    pinMode(pow_pin[i],OUTPUT);
    pinMode(gnd_pin[i],OUTPUT);  
  }

  print_Mx(LED_off);
}

void loop() {

  print_Mx(LED_ptt1);
}
