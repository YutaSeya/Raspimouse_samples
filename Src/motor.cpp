#include "motor.h"
#include "register_address.h"

Motor* Motor::instance = nullptr;

Motor::Motor()
{
  access = Mem_Access::getInstance();
  pwm = Pwm::getInstance();
  init();
}

Motor::~Motor()
{
  delete instance;
}

void Motor::init()
{
  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_BASE);

  // gpio 5,6 output
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 15);
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 18);

  // GPIO16 output 
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 18);

  // setting dir bit(positive direction)
  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 5);

  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 16);

  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 6);

  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 6);

  access->closePeriperal();

  _mtx.unlock();
  
}

Motor* Motor::getInstance()
{
  if(instance == nullptr){
    instance = new Motor();
  }
  return instance;
}

void Motor::turnOnOff(bool left, bool right)
{
  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_BASE);

  if(left){
    // GPIO12 set alt 0 
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 6);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 8);
  } else {
    // GPIO12 gpio output
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 8);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 6);
  }

  if(right){
    // GPIO13 set alt 0 
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 9);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 11);
  } else {
    // GPIO13 gpio output
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 11);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 9);
  }

  access->closePeriperal();

  _mtx.unlock();
}

void Motor::set(int32_t left, int32_t right)
{
  if(left == 0 && right == 0){
    turnOnOff(false, false);
  } else if(left == 0){
    turnOnOff(false, true);
  } else if(right == 0){
    turnOnOff(true, false);
  } else {
    turnOnOff(true, true);
  }

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_BASE);

  if(left == 0 && right == 0){
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 5);
  } else {
    access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 5);
  }

  if(left < 0 ){
    left = -1 * left;
    access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 16);
  } else {
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 16);
  }

  if(right < 0){
    right = -1 * right;    
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 6);
  } else {
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 6);
    access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 6);
  }
  
  access->closePeriperal();

  _mtx.unlock();
  
  pwm->set(left, right);
}