#include "pypwm.h"

Pwm* Pwm::instance = nullptr;

Pwm::Pwm()
{

}

Pwm::~Pwm()
{

}

Pwm* Pwm::getInstance()
{
  if(instance == nullptr){
    instance = new Pwm();
  }
  return instance;
}

void Pwm::init()
{
  
}