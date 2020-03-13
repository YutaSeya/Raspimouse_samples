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
  
  std::printf("ctr + c exit this program\n");
  std::printf("ad0, ad1, ad2, ad3\n");

  while(1)
  {
    uint16_t ad_data[4];
    ad_data[0] = mcp3204->getAD(Mcp3204::SENSOR0);
    std::printf("%d\r",ad_data[0]);
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