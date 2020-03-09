#include "mcp3204.h"

#include "register_address.h"

Mcp3204* Mcp3204::instance = nullptr;

Mcp3204::Mcp3204()
{
  access = Mem_Access::getInstance();
  init();
}

Mcp3204::~Mcp3204()
{
  delete instance;
}

Mcp3204* Mcp3204::getInstance()
{
  if ( instance == nullptr ){
    instance = new Mcp3204();
  }
  return instance;
} 

void Mcp3204::init()
{
  // GPIO Setting
  while( access->checkBusy() );
  access->openPeriperal(RPI_CLK_BASE);
  // GPIO ALT0 (enable SPI mode setting)
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

  // SPI Setting
  while( access->checkBusy() );
  // open spi base
  access->openPeriperal(RPI_SPI_BASE);
  // spi clear tx and rx fifos
  access->setBit(RPI_SPI_CS, 1 << 4);
  access->setBit(RPI_SPI_CS, 1 << 5);

  // set SPI mode 3
  access->setBit(RPI_SPI_CS, 1 << 3);
  access->setBit(RPI_SPI_CS, 1 << 2);

  // set clock divider(781.25kHz)
  access->writeReg(RPI_SPI_CLK, 0x0200);

  access->closePeriperal();

}

void Mcp3204::communication(uint8_t *tx, uint8_t *rx, uint8_t length)
{

  // SPI Setting
  while( access->checkBusy() );
  // open spi base
  access->openPeriperal(RPI_SPI_BASE);

  // connection spi
  // spi clear tx and rx fifos
  access->setBit(RPI_SPI_CS, 1 << 4);
  access->setBit(RPI_SPI_CS, 1 << 5);

  // set TA(transfer active)
  access->setBit(RPI_SPI_CS, 1 << 7);
  
  for(int i = 0; i < length; i++){
    // maybe wait for txd
    while(!(access->readBit(RPI_SPI_CS,1 << 18) >> 18) & 0x01);
    // write to FIFO, no barrier
    access->writeReg(RPI_SPI_FIFO, tx[i]);

    while((access->readBit(RPI_SPI_CS,1 << 17) >> 17) & 0x01);

    // wait for done to be set
    while(!(access->readBit(RPI_SPI_CS,1 << 16) >> 16 )& 0x01);

    // read from fifo to prevent stalling
    while((access->readBit(RPI_SPI_CS,1 << 17) >> 17) & 0x01);

    rx[i] = access->readByte(RPI_SPI_FIFO);
    
  }



  // clear TA(transfer active)
  access->clearBit(RPI_SPI_CS, 1 << 7);

  access->closePeriperal();

}