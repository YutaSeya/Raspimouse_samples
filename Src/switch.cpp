#include "switch.h"
#include "register_address.h"

Switch* Switch::instance = nullptr;

Switch::Switch()
{
  access = Mem_Access::getInstance();
  init();
}

Switch::~Switch()
{
  delete instance;
}

void Switch::init()
{
  // reset value sets input mode
}

Switch* Switch::getInstance()
{
  if(instance == nullptr){
    instance = new Switch();
  }
  return instance;
}

uint32_t Switch::get0()
{
  uint32_t sw_data = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  sw_data = (access->readBit(RPI_GPIO_LEVEL_0, 1 << 20) >> 20);

  access->closePeriperal();

  _mtx.unlock();

  return (~sw_data & 0x01);
}

uint32_t Switch::get1()
{
  uint32_t sw_data = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  sw_data = (access->readBit(RPI_GPIO_LEVEL_0, 1 << 26) >> 26);

  access->closePeriperal();

  _mtx.unlock();

  return (~sw_data & 0x01);
}

uint32_t Switch::get2()
{
  uint32_t sw_data = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  sw_data = (access->readBit(RPI_GPIO_LEVEL_0, 1 << 21) >> 21);

  access->closePeriperal();

  _mtx.unlock();

  return (~sw_data & 0x01);
}

uint32_t Switch::getAll()
{
  uint32_t sw_data = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  sw_data = access->readByte(RPI_GPIO_LEVEL_0);

  access->closePeriperal();

  _mtx.unlock();

  // sw1 data 
  uint32_t sw0 =  ((~sw_data & 1 << 20) >> 20) & 0x01;
  uint32_t sw1 = ((~sw_data & 1 << 26) >> 26) & 0x01;
  uint32_t sw2 = ((~sw_data & 1 << 21) >> 21) & 0x01;

  sw_data = 0;
  sw_data = sw0 | sw1 << 1 | sw2 << 2;

  return sw_data;
}