#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include "mem_access.h"

class Led
{
  // inform pin
  // LED0 GPIO25
  // LED1 GPIO24
  // LED2 GPIO23
  // LED3 GPIO18
private:
  static Led *instance;
  Mem_Access *access;

  void init();
  
public:
  Led();
  ~Led();

  static Led* getInstance();
  void illuminate(uint8_t _light);

};

#endif /* __LED_H */