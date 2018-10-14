/*
   Function Name      : fruitdetect
   Input              : None
   Output             : None
   Logic              : It uses Serial communication to recognise the fruit and put it in the respective deposition box 
   Example Call       : fruitdetect();
*/

void fruitdetect()
{ Buzzer(500);
  if (Serial2.available())
  {
    //read the incoming char
    if (Serial2.read() == "a")
    {
      //Serial2.print("Apple");
      pick();
      // Buzzer(100);
      drop_b();

    }
    else if (Serial2.read() == "o")
    {
      //Serial2.print("Orange");
      pick();
      //Buzzer(1000);
      drop_r();
    }
    else if (Serial2.read() == "b")
    {
      //Serial2.print("Blueberry");
      pick();
      // Buzzer(500);
      drop_l();
    }
    else
    {
      // Serial2.print("nothing");
    }

  }
}



