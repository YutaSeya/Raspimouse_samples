#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "led.h"
#include "switch.h"
#include "mcp3204.h"

void led_test();
void sw_test();

void mcp3204_test()
{

  Mcp3204 *mcp3204 = Mcp3204::getInstance();

  while (1)
  {
    mcp3204->communication(0x06);
    mcp3204->communication(0x00);
    uint8_t ret = mcp3204->communication(0x00);
    printf("ch0 = %d\r\n", ret);
    sleep(1);
  }
  
}

int main()
{
  //led_test();
  //sw_test();
  mcp3204_test();
  
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

  std::printf("ctr + c exit this program\n");

  while(1){
    std::printf("sw0 : %d, sw1 : %d, sw2 : %d, all : %d\r", sw->get0(), sw->get1(), sw->get2(), sw->getAll() );
  }
  
}