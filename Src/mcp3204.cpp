#include "mcp3204.h"

#include "register_address.h"

Mcp3204* Mcp3204::instance = nullptr;

Mcp3204::Mcp3204()
{
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
  

}
