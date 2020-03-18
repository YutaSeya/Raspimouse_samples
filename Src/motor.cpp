#include "motor.h"

#include "register_address.h"

#include <cstdio>

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

Motor* Motor::getInstance()
{
  if(instance == nullptr){
    instance = new Motor();
  }
  return instance;
}

void Motor::init()
{

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);
  // GPIO5 set output 
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 15);

  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 5);

  // GPIO16 set output
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 18);

  // GPIO6 set output
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 18);

  access->closePeriperal();

  _mtx.unlock();

}

void Motor::controlPWMOutput(bool left, bool right)
{
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );
  
  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  if(left){
    // set gpio pin 12 ALT0
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 6);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 8);
  } else {
    // set gpio pin 12 GPIO output
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 8);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 6);
  }
  

  if(right){
    // set gpio pin 13 ALT0
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 9);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 11);
  } else {
    // set gpio pin 13 GPIO output
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 11);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 9);
  }


  access->closePeriperal();

  _mtx.unlock();
}

void Motor::enable()
{
  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 5);

  access->closePeriperal();

  _mtx.unlock();
}

void Motor::disable()
{
  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 5);

  access->closePeriperal();

  _mtx.unlock();

  controlPWMOutput(false, false);

}

void Motor::controlDirection(bool left, bool right)
{
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );
  
  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  if(left){
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 16);
  } else {
    access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 16);
  }
  

  if(right){
    access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 6);
  } else {
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 6);
  }


  access->closePeriperal();

  _mtx.unlock();
}

void Motor::control(int left, int right)
{
  bool left_dir = false;
  bool right_dir = false;

  bool left_control = true;
  bool right_control = true;

  if(left == 0){
    left_control = false;
  } else if(left < 0){  
    left_dir = false;
    left = -1 * left;
  } else {
    left_dir = true;
  }

  if(right == 0){
    right_control = false;
  } else if(right < 0){
    right_dir = false;
    right = -1 * right;
  } else {
    right_dir = true;
  }

  uint32_t left_buff = left;
  uint32_t right_buff = right;

  std::printf("%d, %d\n", left_buff, right_buff);
  std::printf("%d, %d\n", left_dir, right_dir);
  std::printf("%d, %d\n", left_control, right_control);

  controlDirection(left_dir, right_dir);

  controlPWMOutput(left_control, right_control);

  pwm->set(left_buff, right_buff);

}