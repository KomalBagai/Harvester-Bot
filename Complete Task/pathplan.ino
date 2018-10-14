

int cordinates[3][16], cordinates2[3][16];

/*
   Function Name      : count_adjacent
   Input              : None
   Output             : color
   Logic              : To count the number of accessible adjacent nodes
   Example Call       : count_adjacent()
*/

int count_adjacent()
{ color = 0;
  for (i = 0; i < 7; i++)
  { for (j = 0; j < 7; j++)
    { if (path2[i][j] == 0)
      { if (path2[i - 1][j] != 0 && (i - 1 >= 0) && path2[i - 1][j] != -1)
        {
          color++;;
        }

        if (path2[i][j - 1] != 0 && (j - 1 >= 0) && path2[i ][j - 1] != -1)
        {
          color++;
        }

        if (path2[i + 1][j] != 0 && (i + 1 <= 6) && path2[i + 1][j] != -1)
        {
          color++;
        }

        if (path2[i][j + 1] != 0 && (j + 1 <= 6) && path2[i][j + 1] != -1)
        {
          color++;
        }
      }
    }
  }
  return color;
}


/*
   Function Name      : traversal
   Input              : None
   Output             : None
   Logic              : It governs the overall path of the Firebird
   Example Call       : traversal();
*/

int traversal()
{ tempx = 0;
  tempy = 0;
  var = count_adjacent();
  while (var != 0)
  { 
    for (i = 0; i < 16; i++)
    { if (cordinates[2][i] != 0)
      { hmm++;
      }
    }
    weightage(tempx, tempy, Facing);

    search();
    Move(tempx, tempy);
    check_adjacent(tempx, tempy);
    if ((path[ex - 1][why] == 0) && (path[ex + 1][why] == 0) && (path[ex][why + 1] == 0))
    {
      Direction('N');
    }
    else if ((path[ex - 1][why] == 0) && (path[ex][why + 1] == 0) && (path[ex][why - 1] == 0))
    {
      Direction('W');
    }
    else if ((path[ex - 1][why] == 0) && (path[ex + 1][why] == 0) && (path[ex][why - 1] == 0))
    {
      Direction('S');
    }
    else if ((path[ex + 1][why] == 0) && (path[ex][why + 1] == 0) && (path[ex][why - 1] == 0))
    {
      Direction('E');
    }

    for (i = 0; i < 16; i++)
    { if (cordinates[2][i] == -1)
      { count++;
      }
    }
  }

}



/*
   Function Name      : weightage
   Input              : x, y, f
   Output             : None
   Logic              : Assigns weightage to different nodes from the current coordinate
   Example Call       : weightage(tempx, tempy, Facing);
*/

void weightage(int x, int y, char f)
{
  int i, j, count = 0;
  for (i = 0; i < 7; i++)
  { for (j = 0; j < 7; j++)
    {
      maze[i][j] = path2[i][j];
    }
  }
  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < 7; j++)
    { if (f == 'N' || f == 'S')
      {
        count = abs(y - j) + (2 * abs(x - i));
        path2[i][j] = count;
        if (f == 'N')
        { if (maze[i][j - 1] == 0)
          {
            path2[i][j] += 5;
          }
        }
        if (f == 'S')
        {
          if (maze[i][j + 1] == 0)
          {
            path2[i][j] += 5;
          }
        }
      }

      else if (f == 'E' || f == 'W')
      {
        count = (2 * abs(y - j)) + abs(x - i);
        path2[i][j] = count;
        if (f == 'E')
        { if (maze[i - 1][j] == 0)
          {
            path2[i][j] += 5;
          }
        }
        else if (f == 'W')
        {
          if (maze[i + 1][j] == 0)
          {
            path2[i][j] += 5;
          }
        }
      }
    }
  }

  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < 7; j++)
    {
      if (maze[i][j] == 0)
      {
        path2[i][j] = 0;
      }
    }
  }
  if (f == 'N' || f == 'S')
  { if (maze[x][y + 1] == 0)
    {
      path2[x][y + 2] += 5;
    }
    if (maze[x][y - 1] == 0)
    {
      path2[x][y - 2] += 5;
    }
  }
  if (f == 'E' || f == 'W')
  { if (maze[x + 1][y] == 0)
    {
      path2[x + 2][y] += 5;
    }
    if (maze[x - 1][y] == 0)
    {
      path2[x - 2][y] += 5;
    }
  }
  path2[x][y] = -1;
}

/*
   Function Name      : search
   Input              : None
   Output             : None
   Logic              : Searches  for the nearest adjacent node of a particular tree
   Example Call       : search();
*/

void search()
{
  int i, j, p = 0;
  for (i = 0; i < 7; i++)
  { for (j = 0; j < 7; j++)
    { if (maze[i][j] == -1)
      {
        path2[i][j] = -1;
      }
    }
  }

  for (i = 0; i < 7; i++)
  { for (j = 0; j < 7; j++)
    { if (maze[i][j] == 0 && (i - 1 >= 0))
      { if (path2[i - 1][j] != 0)
        {
          cordinates[0][p] = i - 1;
          cordinates[1][p] = j;
          cordinates[2][p] = path2[i - 1][j];
          p++;
        }

        if (path2[i][j - 1] != 0 && (j - 1 >= 0))
        { cordinates[0][p] = i;
          cordinates[1][p] = j - 1;
          cordinates[2][p] = path2[i][j - 1];
          p++;
        }

        if (path2[i + 1][j] != 0 && (i + 1 <= 6))
        { cordinates[0][p] = i + 1;
          cordinates[1][p] = j;
          cordinates[2][p] = path2[i + 1][j];
          p++;
        }

        if (path2[i][j + 1] != 0 && (j + 1 <= 6))
        { cordinates[0][p] = i;
          cordinates[1][p] = j + 1;
          cordinates[2][p] = path2[i][j + 1];
          p++;
        }
      }
    }
  }

  temp2 = 50;

  for (i = 0; i < p; i++)
  { if (cordinates[2][i] != -1)
    {
      if (temp2 > cordinates[2][i])
      { temp2 = cordinates[2][i];
        tempx = cordinates[0][i];
        tempy = cordinates[1][i];
      }
    }
  }

}


