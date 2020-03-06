#include <iostream>

#include <unistd.h>

#include "led.h"
#include "switch.h"

void led_test();
void sw_test();

int main()
{
  //led_test();
  sw_test();
  return 0;
}

void led_test()
{
  Led *led = Led::getInstance();

  for(int i = 0; i < 16; i++){
    led->illuminate(i);
    sleep(1);
  }
  
  led->illuminate(0);
}

void sw_test()
{
  Switch *sw = Switch::getInstance();

  printf("sw0 : %d, sw1 : %d, sw2 : %d\r", sw->get0(), sw->get1(), sw->get2() );

}