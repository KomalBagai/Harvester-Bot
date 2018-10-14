/*
   Function Name      : check_adjacent
   Input              : x2, y2
   Output             : None
   Logic              : Checks if any adjecent node contains any tree
   Example Call       : check_adjacent(ex, why);
*/


void check_adjacent(int x2, int y2)
{ 
  //check for adjacent right node
  if (path[x2 + 1][y2] == 0)
  {
    Direction('E');
    Stop();
    delay(1000);
    Serial2.print("c");
    delay(100);

    fruitdetect();
    delay(1000);

    var--;
    path[x2][y2] = -1;
  }

  //check for adjacent front node
  if (path[x2][y2 + 1] == 0)
  {
    Direction('N');
    Stop();
    delay(1000);
    Serial2.print("c");
    delay(100);

    fruitdetect();
    delay(1000);
    
    var--;
    path[x2][y2] = -1;

  }

  //check for adjacent left node
  if (path[x2 - 1][y2] == 0)
  {
    Direction('W');
    Stop();
    delay(1000);
    Serial2.print("c");
    delay(100);

    fruitdetect();
    delay(1000);
    var--;
    path[x2][y2] = -1;
  }

  //check for adjacent back node
  if (path[x2][y2 - 1] == 0)
  {
    Direction('S');
    Stop();
    delay(1000);
    Serial2.print("c");
    delay(100);

    fruitdetect();
    delay(1000);

    var--;
    path[x2][y2] = -1;
  }

}



/*
   Function Name      : Go1
   Input              : b
   Output             : None
   Logic              : Moves the firebird forward till 'b' number of nodes
   Example Call       : Go1(1);
*/
int Go1(int b)
{
  int Node_Check = 0;
  //Follow the line till 'a' nodes
  while (b >= 1)
  {
    Node_Check = Line_Follow_Forward();
    b--;
    if (Facing == 'N')
      why++;
    else if (Facing == 'S')
      why--;
    else if (Facing == 'W')
      ex--;
    else if (Facing == 'E')
      ex++;

    while (Node_Check == 0)
      Node_Check = Line_Follow_Forward();

  }
  Stop();

}



/*
   Function Name      : check
   Input              : None
   Output             : 0, 1
   Logic              : Avoids the obstacles and finds the optimal path between current and reaching coordinates
   Example Call       : check();
*/
int  check()
{
  if ((Facing == 'N') && (ex <= 5) && (ex >= 0))
  {
    if ((path[ex][why - 1] != 0) && (path[ex][why + 1] == 0) && (path[ex + 1][why] == 0))
    {
      if (tempx <= ex)
      {

        Direction('W');
        Go1(1);

        bkl = 0;
        return 1;
      }

      else if (tempx > ex)
      {

        Direction('S');
        Go1(1);

        Direction('E');
        Go1(1);

        bkl = 1;
        return 1;
      }
    }

    else if (path[ex + 1][why] != 0 && path[ex][why + 1] == 0 && path[ex - 1][why] == 0)
    {
      if (tempx >= ex)
      {

        Direction('E');
        Go1(1);
    
        bkl = 0;
        return 1;
      }

      else if (tempx < ex)
      {
        Direction('S');
        Go1(1);

        Direction('W');
        Go1(1);

        bkl = 1;
        return 1;
      }
    }

    else if (path[ex + 1][why] != 0 && path[ex][why + 1] == 0 && path[ex - 1][why] != 0)
    {
      if (tempx >= ex)
      {

        Direction('E');
        Go1(1);
   
        bkl = 0;
        return 1;
      }

      else if (tempx < ex)
      {

        Direction('W');
        Go1(1);
        
        bkl = 0;
        return 1;
      }
    }


    else
    {
      bkl = 0;
      return 0;
    }

  }

  if ((Facing == 'E') && (why <= 5) && (why >= 0))
  {
    if ((path[ex][why + 1] == 0) && (path[ex - 1][why] != 0) && (path[ex + 1][why] == 0))
    {
      if (tempy > why)

      {
        Direction('W');
        Go1(1);

        Direction('N');
        Go1(1);
        
        bkl = 1;
        return 1;
      }
      else if (tempy <= why)
      {

        Direction('S');
        Go1(1);

        bkl = 0;
        return 1;
      }
    }

    else if (path[ex][why + 1] != 0 && path[ex + 1][why] == 0 && path[ex][why - 1] == 0)
    {
      if (tempy >= why)

      {
        Direction('N');
        Go1(1);

        bkl = 0;
        return 1;
      }
      else if (tempy < why)
      {
        Direction('W');
        Go1(1);

        Direction('S');
        Go1(1);

        bkl = 1;
        return 1;
      }
    }

    else if (path[ex][why + 1] != 0 && path[ex + 1][why] == 0 && path[ex][why - 1] != 0)
    {
      if (tempy >= why)
      {
        Direction('N');
        Go1(1);

        bkl = 0;
        return 1;
      }
      else if (tempy < why)
      {

        Direction('S');
        Go1(1);

        bkl = 0;
        return 1;
      }
    }
    else
    {
      bkl = 0;

      return 0;
    }

  }


  if ((Facing == 'S') && (ex <= 5) && (ex >= 0))
  {
    if ((path[ex][why - 1] == 0) && (path[ex + 1][why] == 0) && (path[ex][why + 1] != 0))
    { if (tempx <= ex)
      {


        Direction('W');
        Go1(1);
        
        bkl = 0;
        return 1;
      }

      else if (tempx > ex)
      {
        Direction('N');
        Go1(1);

        Direction('E');
        Go1(1);
       
        bkl = 1;
        return 1;
      }

    }
    else if ((path[ex][why - 1] == 0) && (path[ex - 1][why] == 0) && (path[ex][why + 1] != 0))
    { if (tempx >= ex)
      {

        Direction('E');
        Go1(1);
        
        bkl = 0;
        return 1;
      }

      else if (tempx < ex)
      {
        Direction('N');
        Go1(1);

        Direction('W');
        Go1(1);
        
        bkl = 1;
        return 1;
      }

    }


    else if (path[ex + 1][why] != 0 && path[ex][why - 1] == 0)
    {
      if (tempx <= ex)
      {
        Direction('W');
        Go1(1);
      }

      else if (tempx > ex)
      {
        Direction('E');
        Go1(1);
      }
      
      bkl = 0;
      return 1;

    }
    else
    {
      bkl = 0;
      return 0;
    }
  }

  if ((Facing == 'W') && (why <= 5) && (why >= 0 ))
  {
    if ((path[ex + 1][why] != 0) && (path[ex][why + 1] == 0) && (path[ex - 1][why] == 0))
    { if (tempy > why)
      {
        Direction('E');
        Go1(1);

        Direction('N');
        Go1(1);
       
        bkl = 1;
        return 1;
      }
      else if (tempy <= why)
      {
        Direction('S');
        Go1(1);
        
        bkl = 0;
        return 1;
      }
    }

    else if ((path[ex + 1][why] != 0) && (path[ex][why - 1] == 0) && (path[ex - 1][why] == 0))
    {
      if (tempy < why)

      {
        Direction('E');
        Go1(1);

        Direction('S');
        Go1(1);
        
        bkl = 1;
        return 1;
      }
      else if (tempy >= why)
      {
        Direction('N');
        Go1(1);
        
        bkl = 0;
        return 1;

      }
    }

    else if (path[ex][why + 1] != 0 && path[ex - 1][why] == 0 && path[ex][why - 1] != 0)
    { if (tempy < why)
      {

        Direction('S');
        Go1(1);
        
        bkl = 0;
        return 1;
      }
      else if (tempy >= why)
      {
        Direction('N');
        Go1(1);

        bkl = 0;
        return 1;

      }
    }
    else
    {
      bkl = 0;
      return 0;
    }
  }

  x = ex;
  y = why;
}



