#ifndef __SWITCH_H
#define __SWITCH_H

#include <stdint.h>
#include "mem_access.h"

class Switch
{
  // switch 0 GPIO 20
  // switch 1 GPIO 26
  // switch 2 GPIO 21

private:
  Mem_Access *access;
  static Switch* instance;

  void init();

public:
  Switch();
  ~Switch();

  static Switch* getInstance();

  uint32_t getSW0();

  uint32_t getSW1();

  uint32_t getSW2();
};

#endif /* __SWITCH_H */