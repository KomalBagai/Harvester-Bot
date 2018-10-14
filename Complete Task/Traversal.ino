/*
   Function Name      : Stop
   Input              : None
   Output             : None
   Logic              : Stops both the motors
   Example Call       : Stop()
*/
void Stop()
{
  PORTA = 0B00000000;
}

/*
   Function Name      : Forward
   Input              : None
   Output             : None
   Logic              : Starts both the motors in Forward direction
   Example Call       : Forward()
*/

void Forward()
{
  PORTA = 0B00000110;
}

/*
   Function Name      : Backward
   Input              : None
   Output             : None
   Logic              : Starts both the motors in backward direction
   Example Call       : Backward()
*/

void Backward()
{
  PORTA = 0B00001001;
}

/*
   Function Name      : Left
   Input              : None
   Output             : None
   Logic              : Starts right motor in forward and left motor in backward direction
   Example Call       : Left()
*/

void Left()
{
  PORTA = 0B00000101;
}

/*
   Function Name      : Right
   Input              : None
   Output             : None
   Logic              : Starts left motor in forward and right motor in backward direction
   Example Call       : Right()
*/

void Right()
{
  PORTA = 0B00001010;
}

/*
   Function Name      : Left_Degree
   Input              : Degree
   Output             : None
   Logic              : Rotates the Firebird to Left by 'degrees'
   Example Call       : Left_Degree(90)
*/

void Left_Degree(unsigned int Degrees)
{
  int ReqdShaftCount = (Degrees - 25) / 4.090 ;                        //Rotate for degree-25
  ShaftCountRight = 0;
  while (ShaftCountRight < ReqdShaftCount)
    Left();
  ReqdShaftCount = (35) / 4.090 ;
  ShaftCountRight = 0;
  ms = analogRead(2);                                                     //Update sensor values
  while ((ms < Threshold) && (ShaftCountRight < ReqdShaftCount))          //Rotate while no black line detected
  {
    ms = analogRead(2);
    Left();
  }
  Stop();
}

/*
   Function Name      : Right_Degree
   Input              : Degree
   Output             : None
   Logic              : Rotates the Firebird to Right by 'degrees'
   Example Call       : Right_Degree(90)
*/

void Right_Degree(unsigned int Degrees)
{
  int ReqdShaftCount = (Degrees - 25) / 4.090 ;                         //Rotate for degree-25
  ShaftCountRight = 0;
  while (ShaftCountRight < ReqdShaftCount)
    Right();
  ReqdShaftCount = (35) / 4.090 ;
  ShaftCountRight = 0;
  ms = analogRead(2);                                                     //Update sensor values
  while ((ms < Threshold) && (ShaftCountRight < ReqdShaftCount))          //Rotate while no black line detected
  {
    ms = analogRead(2);
    Right();
  }
  Stop();
}

/*
   Function Name      : Line_Follow_Forward
   Input              : None
   Output             : None
   Logic              : Follows the line
   Example Call       : Line_Follow_Forward()
*/
int Line_Follow_Forward()
{
  //Update white line sensor values
  ms = analogRead(1);
  rs = analogRead(2);
  ls = analogRead(3);
  if ((ls <= Threshold) && (ms > Threshold) && (rs <= Threshold))
    Forward();
  if ((ls > Threshold) && (ms <= Threshold) && (rs <= Threshold))
    Left();
  else if ((ls <= Threshold) && (ms <= Threshold) && (rs > Threshold))
    Right();
  else
    Forward();
  
  //return 1 if a node is detected
  if ((ls + ms + rs) > 800)
  {
    return 1;
  }

  if (((ls > Threshold) && (ms > Threshold) && (rs > Threshold)) || ((ls > Threshold) && (ms > Threshold) && (rs <= Threshold)) || ((ls <= Threshold) && (ms > Threshold) && (rs > Threshold)))
  { //Move 7 Cm forward when node is detected
    Forward_Cm(7);
    return 1;
  }
  else
  {
    return 0;
  }
}


/*
   Function Name      : Shaft_Right
   Input              : None
   Output             : None
   Logic              : Interrupt Service Routine for Right Position Encoder
   Example Call       : Shaft_Right()
*/
void Shaft_Right()
{
  ShaftCountRight++;
}


/*
   Function Name      : Shaft_Left
   Input              : None
   Output             : None
   Logic              : Interrupt Service Routine for Left Position Encoder
   Example Call       : Shaft_Left()
*/
void Shaft_Left()
{
  ShaftCountLeft++;
}


/*
   Function Name      : Forward_Cm
   Input              : Distance
   Logic              : Follows the line in forward direction for 'distance' cm
   Example Cal        : Forward_Cm(7)
*/
void Forward_Cm(int Distance)
{
  // Mapping Function to calculate Shaft Counts
  int ReqdShaftCount = Distance / 0.5338 ;
  ShaftCountRight = 0;
  cli();
  sei();
  while (ShaftCountRight < ReqdShaftCount)
  {
    Line_Follow_Forward();
  }
  Stop();
}


/*
   Function Name      : Backward_Cm
   Input              : Distance
   Output             : None
   Logic              : Follows the line in backward direction for 'distance' cm
   Example Call       : Backard_Cm(7)
*/
void Backward_Cm(int Distance)
{
  // Mapping Function to calculate Shaft Counts
  int ReqdShaftCount = Distance / 0.5338 ;
  ShaftCountRight = 0;
  while (ShaftCountRight < ReqdShaftCount)
    Backward();
  Stop();
}

/*
   Function Name      : Buzzer
   Input              : msec
   Output             : None
   Logic              : Beeps a buzzer for number of miliseconds given in the parameter
   Example Call       : Buzzer(5000);
*/
void Buzzer(int msec)
{
  digitalWrite(34, HIGH);
  delay(msec);
  digitalWrite(34, LOW);

}

/*
   Function Name      : Direction
   Input              : msec
   Output             : None
   Logic              : Acts like a vitual compass in order to change the direction of the bot
   Example Call       : Direction('N');
*/

void Direction(char f)
{
    // Turns the bot right/left to face the given direction 'f'
  if (f == 'N')
  {
    if (Facing == 'S')
    { 
      Right_Degree(180);    
    }
    
    else if (Facing == 'W')
    {      
      Right_Degree(90); 
    }

    else if (Facing == 'E')
    { 
      Left_Degree(90);
    }
    Facing = 'N';
  }
  
  else if (f == 'S')
  {
    if (Facing == 'N')
    { 
      Right_Degree(180);
    }
    else if (Facing == 'E')
    { 
      Right_Degree(90);
    }
    else if (Facing == 'W')
    { 
      Left_Degree(90);
    }
    Facing = 'S';
  }

  
  else if (f == 'E')
  {
    if (Facing == 'N')
    { 
      Right_Degree(90);     
    }
    else if (Facing == 'S')
    { 
      Left_Degree(90);
    }
    else if (Facing == 'W')
    { 
      Right_Degree(180);    
    }
    Facing = 'E';
  }

  
  else if (f == 'W')
  {
    if (Facing == 'N')
    { 
      Left_Degree(90);    
    }
    else if (Facing == 'S')
    { 
      Right_Degree(90);
    }
    else if (Facing == 'E')
    { 
      Right_Degree(180);
    }
    Facing = 'W';
  }
}

/*
   Function Name      : Go
   Input              : nod
   Output             : None
   Logic              : Moves the firebird forward till 'a' number of nodes
   Example Call       : Go(5);
*/
int Go(int nod)
{
  int Node_Check = 0;
  
  papa = Facing;                        //Setting a variable to the initial Facing
  
  //Follow the line till 'nod' nodes
  while (nod >= 1)
  { bhuwan = 1;
    //loop to check for the optimal path 
    while (bhuwan == 1)
    {
      bhuwan = check();                     
      Direction(papa);
    }
    Node_Check = Line_Follow_Forward();
    nod--;
    while (Node_Check == 0)
      Node_Check = Line_Follow_Forward();
    if (Facing == 'N')
    { why++;
    }
    else if (Facing == 'E')
    { ex++;
    }
    else if (Facing == 'W')
    { ex--;
    }
    else if (Facing == 'S')
    { why--;
    }
    
  }

}


/*
   Function Name      : Move
   Input              : x1, y1
   Output             : None
   Logic              : Takes the bot to (x1,y1) coordinates
   Example Call       : Move(0,5);
*/
void Move(int x1, int y1)
{ // Match "y" coordinate
  if (y1 > why)
  {
    Direction('N');
    Go(y1 - why);
  }
  else if (y1 < why)
  {
    Direction('S');
    Go(why - y1);
  }
  y = y1;
  // Match "x" coordinate

  if (x1 > ex)
  {
    Direction('E');
    Go(x1 - ex);
  }
  else if (x1 < ex)
  {
    Direction('W');
    Go(ex - x1);
  }
  x = x1;
}

