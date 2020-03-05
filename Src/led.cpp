#include "led.h"

#include "register_address.h"

Led* Led::instance = nullptr;

Led::Led()
{
  access = Mem_Access::getInstance();
  init();
}

Led::~Led()
{
  delete instance;
}

void Led::init()
{
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // set gpio output mode
  // set gpio pin 18
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 24);
  // set gpio pin 23
  access->setBit(RPI_GPIO_GPFSEL2, 1 << 9);
  // set gpio pin 24
  access->setBit(RPI_GPIO_GPFSEL2, 1 << 12);
  // set gpio pin 25
  access->setBit(RPI_GPIO_GPFSEL2, 1 << 15);

  access->closePeriperal();
  _mtx.unlock();
  
}

Led* Led::getInstance()
{
  if(instance == nullptr){
    instance = new Led();
  }
  return instance;
}

void Led::illuminate(uint8_t _light)
{
  uint8_t led0 = _light & 0x01;
  uint8_t led1 = (_light & 0x02) >> 1;
  uint8_t led2 = (_light & 0x04) >> 2;
  uint8_t led3 = (_light & 0x08) >> 3;
  uint32_t set_data = 0;
  uint32_t clear_data = 0;

  if(led0 == 1) set_data |= (1 << 25);
  else clear_data |= (1 << 25);

  if(led1 == 1) set_data |= (1 << 24);
  else clear_data |= (1 << 24);

  if(led2 == 1) set_data |= (1 << 23);
  else clear_data |= (1 << 23);

  if(led3 == 1) set_data |= (1 << 18);
  else clear_data |= (1 << 18);

  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  access->writeReg(RPI_GPIO_OUTPUT_SET_0, set_data);

  access->writeReg(RPI_GPIO_OUTPUT_CLR_0, clear_data);

  access->closePeriperal();

  _mtx.unlock();
}