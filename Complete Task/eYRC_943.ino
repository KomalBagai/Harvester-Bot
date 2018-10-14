/*
  Team Id             : eYRC-HB#934
  Author List         : Nikunj Kumar Agarwal, Komal Bagai, Dheeraj Khanna
  Filename            : eYRC_#934
  Theme               : Harvester Bot
  Functions           :
  Global Variables    :
*/

int tempx = 0, tempy = 0, temp2 = 0;                                      //dynamic(changeable) values of adjacent coordinates of trees.
int bkl = 0, i = 0;
char papa;                                                                
int Nodecheck = 0;                                                        
int ShaftCountRight = 0, ShaftCountLeft = 0;                              // ISR increaments
int Threshold = 48;                                                       // White Line Sensor Threshhold Value
int ls = 0, ms = 0, rs = 0;                                               // White Line Sensor Values
int x = 0, y = 0;                                                         // Position Coordinates of the bot
int ex = 0, why = 0, j = 0;                                               //Dynamic position coordinates of the bot
char Facing = 'N';                                                        // Current Compass value
int bhuwan = 1;                                                             
int var = 0;
int count = 0;
int hmm;  
int color;
int up;
int distance=11;                                                          //distance of fruit from the picking arm
int sensor=A11;                                                           //sharp sensor pin initialisation



int maze[7][7] = {
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1}
};


//Dynamic path matrix which changes its vaalues with different function calls while traversal.
int path2[7][7] = {
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1}
};

// Path matrix for the configuration given(0 for empty nodes, 1 for nodes having trees)
int path[7][7] =  {
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1},
  {1, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 0, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1}
};

/*    FUNCTIONS FOR MOTOR MOVEMENTS    */
 
//void Stop();
//void Forward();
//void Backward();
//void Left();
//void Right();
//void Left_Degree(unsigned int Degrees);
//void Right_Degree(unsigned int Degrees);
//int Line_Follow_Forward();
//void Shaft_Right();
//void Shaft_Left();
//void Forward_Cm(int Distance);
//void Backard_Cm(int Distance);
//void Direction(char f);

/*    FUNCTIONS FOR TRAVERSAL    */  
//void Move(int x1, int y1);
//void Buzzer(int msec);
//void Go(int nod);
//void Go1(int b);
//void check();
//int count_adjacent();
//int Traversal();
//void check_adjacent();
//void deposition();
//void weightage(int x, int y, char f);
//void search();

/*    FUNCTION FOR SERIAL COMMUNICATION    */
//void fruitdetect();


/*    FUNCTIONS FOR MECHANISMS    */ 
//void pick();
//void drop_r();
//void drop_b();
//void drop_l();
//int sharpservo();



#include<math.h>
#include<Servo.h>

//arm servos
Servo upservo;
Servo downservo;
Servo pickservo;

//deposition servos
Servo db;
Servo dr;
Servo dl;

//SETUP
/*
   Function Name      : Setup
   Input              : None
   Output             : None
   Logic              : Initializes all the required pins and ports.
   Example Call       : N/A
*/
void setup() 
{
  // put your setup code here, to run once:
  // PORTS Initiallization
  
  UCSR2B = 0x00; //disable while setting baud rate
  UCSR2A = 0x00;
  UCSR2C = 0x06;
  UBRR2L = 0x5F; //set baud rate lo
  UBRR2H = 0x00; //set baud rate hi
  UCSR2B = 0x98;

  DDRA = 0x0F;
  DDRL = DDRL | 0x18;
  PORTL = PORTL | 0x18;
  DDRE  = DDRE & 0xEF;
  PORTE = PORTE | 0x10;
  DDRE  = DDRE & 0xDF;
  PORTE = PORTE | 0x20;
  pinMode(A11, INPUT);                                    //Sharp sensor pin                                  
  pinMode(3, INPUT);                                      //1,2,3 arethe White line sensors
  pinMode(2, INPUT);
  pinMode(1, INPUT);
  pinMode(34, OUTPUT);                                    //Buzzer Pin   
  
  upservo.attach(13);
  downservo.attach(12);
  pickservo.attach(11);
  //ss.attach(48); //27

  db.attach(9);                                           //pin 6 in Atmega 2560 
  dr.attach(8);                                           //pin 5 in Atmega 2560  
  dl.attach(47);                                          //pin 30 in Atmega 2560 

  upservo.write(90);
  downservo.write(90);
  pickservo.write(0);

  db.write(0);
  dr.write(0);
  dl.write(0);
  //Serial2.begin(9600);

  attachInterrupt(digitalPinToInterrupt(2), Shaft_Left, FALLING);
  attachInterrupt(digitalPinToInterrupt(3), Shaft_Right, FALLING);
  delay(1000);
  
  upservo.detach();
  downservo.detach();
  pickservo.detach();
  dr.detach();
  db.detach();
  dl.detach();
  traversal();
  deposition();
  Buzzer(5000);
}


/*
  Function Name      :  loop
  Input              :  None
  Output             :  None
  Logic              :  No code is used here
  Example Call       :  NOT USED
*/
void loop()
{
}

