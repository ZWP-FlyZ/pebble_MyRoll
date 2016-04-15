
#pragma once
#include <pebble.h>


int my_roll_int(int min,int max)
{
  if(min>=max)
    return -1;
  srand(rand());
  return min+rand()%(max-min+1);
}



