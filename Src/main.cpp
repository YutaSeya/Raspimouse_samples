#include <iostream>

#include <unistd.h>

#include "led.h"

int main()
{
  Led *led = Led::getInstance();

  for(int i = 0; i < 16; i++){
    led->illuminate(i);
    sleep(1);
  }
  
  led->illuminate(0);

  return 0;
}