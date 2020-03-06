#include "switch.h"
#include "register_address.h"

Switch* Switch::instance = nullptr;

Switch::Switch()
{
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

  sw_data = access->readBit(RPI_GPIO_LEVEL_0, 1 << 20);

  access->closePeriperal();

  _mtx.unlock();

  return sw_data;
}

uint32_t Switch::get1()
{
  uint32_t sw_data = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  sw_data = access->readBit(RPI_GPIO_LEVEL_0, 1 << 26);

  access->closePeriperal();

  _mtx.unlock();

  return sw_data;
}

uint32_t Switch::get2()
{
  uint32_t sw_data = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  sw_data = access->readBit(RPI_GPIO_LEVEL_0, 1 << 21);

  access->closePeriperal();

  _mtx.unlock();

  return sw_data;
}