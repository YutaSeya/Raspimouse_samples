#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "led.h"
#include "switch.h"
#include "mcp3204.h"

void led_test();
void sw_test();
void mcp3204_test();

int main()
{
  #if SW_TEST
    sw_test();
  #elif MCP_TEST
    mcp3204_test();
  #else 
    led_test();
  #endif
  
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

void mcp3204_test()
{

  Mcp3204 *mcp3204 = Mcp3204::getInstance();
  
  std::printf("ctr + c exit this program\n");
  std::printf("left_front, left, right, right_fornt\n");

  while(1)
  {
    uint16_t ad_data[4];
    ad_data[0] = mcp3204->getAD(Mcp3204::SENSOR_LEFT_FRONT);
    ad_data[1] = mcp3204->getAD(Mcp3204::SENSOR_LEFT);
    ad_data[2] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT);
    ad_data[3] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT_FRONT);
    std::printf("%4d,%4d,%4d,%4d\r\n",ad_data[0], ad_data[1], ad_data[2], ad_data[3]);
    sleep(1);
  }

}