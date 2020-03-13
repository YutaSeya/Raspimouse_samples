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
  
  uint8_t tx_buffer[3];
  uint8_t rx_buffer[3];

  tx_buffer[0] = 0x06;
  tx_buffer[1] = 0;
  tx_buffer[2] = 0;

  while (1)
  {

    mcp3204->communication(tx_buffer, rx_buffer, 3);

    printf("rx_buffer 1 : %d, 2: %d\r\n", rx_buffer[1], rx_buffer[2]);
    
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