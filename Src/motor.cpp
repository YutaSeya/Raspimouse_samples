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

}

void Motor::controlLeft(int freq)
{

  int32_t left = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );
  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);
  
  if(freq == 0){
    // set gpio pin 12 GPIO output
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 8);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 6);

    access->closePeriperal();
    return;
  } else {
    // set gpio pin 12 ALT0
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 6);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 8);
  }

  if(freq < 0){
    left = -1 * freq;
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 16);
  } else {
    left = freq;
    access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 16);
  } 

  access->closePeriperal();
  _mtx.unlock();

  pwm->set1(left);

}

void Motor::controlRight(int freq)
{
  int32_t right = 0;
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );
  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);
  
  if(freq == 0){
    // set gpio pin 13 GPIO output
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 11);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 9);

    access->closePeriperal();
    return;
  } else {
    // set gpio pin 13 ALT0
    access->clearBit(RPI_GPIO_GPFSEL1, 1 << 9);
    access->setBit(RPI_GPIO_GPFSEL1, 1 << 11);
  }

  if(freq < 0){
    right = -1 * freq;
    access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 6);
  } else {
    right = freq;
    access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 6);
  } 

  access->closePeriperal();
  _mtx.unlock();

  pwm->set2(right);
}

void Motor::control(int left, int right)
{
  controlLeft(left);
  controlRight(right);
}