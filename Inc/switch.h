#ifndef __SWITCH_H
#define __SWITCH_H

#include <stdint.h>
#include "mem_access.h"

class Switch
{
private:
  Mem_Access *access;
  static Switch* instance;

  void init();

public:
  Switch();
  ~Switch();

  static Switch* getInstance();
};

#endif /* __SWITCH_H */