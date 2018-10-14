/*
   Function Name      : pick
   Input              : None
   Output             : None
   Logic              : picks the fruit from the tree 
   Example Call       : pick();
*/
void  pick()
{
  int value1=0;
  upservo.attach(13);
  downservo.attach(12);
  pickservo.attach(11);
  downservo.write(95);
  upservo.write(85);
  pickservo.write(0);
  delay(1000);
  for ( up = 85; up <= 180&&value1!=1; up += 2)
  {
    value1 = sharpsensor();
    Serial2.print("up:");
    Serial2.println(up);
    upservo.write(up);
    delay(5);
    
    Serial2.print("value1 ");
    Serial2.println(value1);
//    if (value1 == 1) {
//      //upservo.write(i+3);
//      Serial2.println("break");
//      break;
   // }
  }
  delay(1000);
  downservo.write(80);
  delay(1000);

  for (int i = 0; i <= 52; i += 2)
  {
    pickservo.write(i);
    delay(15);
    Serial2.print("pick");
  }
  delay(1000);


  Backward_Cm(2);
  delay(100);
  Stop();
  delay(1000);
  for (int i = up; i >= 90; i--) {
    upservo.write(i);
    delay(15);
  }
  delay(1000);
}

/*
   Function Name      : drop_r
   Input              : None
   Output             : None
   Logic              : Drops the fruits in the right deposition box 
   Example Call       : drop_r();
*/

void drop_r()
{
  dr.attach(8);  //5
  //drop in dr
  downservo.write(0);
  delay(1000);
  upservo.write(0);
  delay(1000);
  pickservo.write(0);
  delay(1000);
  upservo.detach();
  downservo.detach();
  pickservo.detach();

}

/*
   Function Name      : drop_b
   Input              : None
   Output             : None
   Logic              : Drops the fruits in the back deposition box 
   Example Call       : drop_b();
*/

void drop_b() 
{
  db.attach(9);  //6
  //drop in db
  downservo.write(70);
  delay(1000);
  upservo.write(0);
  delay(1000);
  pickservo.write(0);
  delay(1000);

  //downservo.write(0);
  upservo.write(0);
  delay(100);
  upservo.write(90);
  upservo.detach();
  downservo.detach();
  pickservo.detach();

}


/*
   Function Name      : drop_l
   Input              : None
   Output             : None
   Logic              : Drops the fruits in the left deposition box 
   Example Call       : drop_l();
*/

void drop_l() 
{
  dl.attach(47); //30
  //drop in dl
  upservo.write(90);
  delay(1000);
  downservo.write(15);
  //upservo.write(0);
  delay(1000);
  upservo.write(180);
  delay(1000);
  pickservo.write(0);
  delay(1000);
  upservo.write(90);
  //downservo.write(0);
  //upservo.write(0);
  upservo.detach();
  downservo.detach();
  pickservo.detach();

}

/*
   Function Name      : sharpsensor
   Input              : None
   Output             : 1, 0
   Logic              : To detect the position of the fruit 
   Example Call       : sharpsensor();
*/


int sharpsensor()
{
  float volts = analogRead(sensor) * 0.0048828125;        // value from sensor * (5/1024)
  distance = 13 * pow(volts, -1);                         // worked out from datasheet graph
//  Serial.print("distance:");
//  Serial.println(distance);
  //int value = analogRead(sensor);

  if (distance<10)
  { //Serial.print(value);
    //delay(5);
    return 1;
  }
  else
    return 0;
}






