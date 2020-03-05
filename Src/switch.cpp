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

}

Switch* Switch::getInstance()
{
  if(instance == nullptr){
    instance = new Switch();
  }
  return instance;
}