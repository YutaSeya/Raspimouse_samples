#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "led.h"
#include "switch.h"
#include "register_address.h"

void led_test();
void sw_test();

void mcp3204_test(uint8_t val)
{
  Mem_Access *access = Mem_Access::getInstance();

  while( access->checkBusy() );
  // GPIO ALT0 (enable SPI mode setting)
  access->openPeriperal(RPI_CLK_BASE);
  // set GPIO9 to MISO 
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 29);
  // set GPIO10 to MOSI
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 3);
  // set GPIO11 to SCLK
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 6);
  // set GPIO8 to SPI's CS Pin
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 26);
  // close pheripheral
  access->closePeriperal();
  while( access->checkBusy() );
  // open spi base
  access->openPeriperal(RPI_SPI_BASE);
  // spi clear tx and rx fifos
  access->setBit(RPI_SPI_CS, 1 << 4);
  access->setBit(RPI_SPI_CS, 1 << 5);

  // set SPI mode 3
  access->setBit(RPI_SPI_CS, 1 << 3);
  access->setBit(RPI_SPI_CS, 1 << 2);

  // calc spi speed hz setting parameter
  uint16_t divider = (uint16_t) ((uint32_t)BCM2835_CORE_CLK_HZ / 1000000);
  divider &= 0xFFFE;

  // set clock divider
  access->writeReg(RPI_SPI_CLK, divider);

  // connection spi
  // spi clear tx and rx fifos
  access->setBit(RPI_SPI_CS, 1 << 4);
  access->setBit(RPI_SPI_CS, 1 << 5);

  // set TA(transfer active)
  access->setBit(RPI_SPI_CS, 1 << 7);

  // maybe wait for txd
  while(!((access->readBit(RPI_SPI_CS,1 << 18) >> 18) & 0x01));

  // write to FIFO, no barrier
  uint32_t write_data = val;
  access->writeReg(RPI_SPI_FIFO, write_data);

  // wait for done to be set
  while(!((access->readBit(RPI_SPI_CS,1 << 16) >> 16) & 0x01));

  uint32_t ret = access->readByte(RPI_SPI_FIFO);

  printf("ret = %d\r\n", ret);

  // clear TA(transfer active)
  access->clearBit(RPI_SPI_CS, 1 << 7);

  access->closePeriperal();

}

int main()
{
  //led_test();
  //sw_test();
  mcp3204_test(0x06);
  mcp3204_test(0x00);
  mcp3204_test(0x00);
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