/*
   Function Name      : deposition
   Input              : None
   Output             : None
   Logic              : Deposits the fruits to the required deposition zones 
   Example Call       : deposition();
*/


void deposition()
{
  db.attach(9);                                       //6 pin for Atmega 2650
  dr.attach(8);                                       //5 pin for Atmega 2560
  dl.attach(47);                                      //30 pin for Atmega 2560
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 7; j++)
    {
      if (i == 1 && j == 4)
      {
        Move(0, 5);
        Direction('N');
        Forward_Cm(17);

        Direction('S');
        Stop();
        delay(500);
        dl.write(180);
        delay(15);
        Direction('N');
        dl.write(0);
        delay(15);
        dl.detach();
        Backward_Cm(17);
        
      }
      if ((i == 2) && (j == 1))
      {
        Move(2, 5);
        Direction('N');
        Forward_Cm(17);
        Direction('W');
        Stop();
        delay(500);
        db.write(180);
        Direction('N');
        db.write(0);
        delay(15);
        db.detach();
        Backward_Cm(17);
        
      }
      if ((i == 4) && (j == 2))
      {
        Move(5, 5);
        Direction('N');
        Forward_Cm(17);
        //Direction('N');
        Stop();
        delay(500);
        dr.write(180);
        delay(15);
        
        Backward_Cm(17);
        
        dr.write(0);
        delay(15);
        dr.detach();
      }

    }
  }
}



