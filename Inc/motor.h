/**
 * @file motor.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined motor class.
*/ 

#ifndef __MOTOR_H
#define __MOTOR_H

#include <stdint.h>
#include "mem_access.h"
#include "pipwm.h"

/**
 * @class Motor
 * @brief 
 *  Control motors.
 * @details
*/ 
class Motor
{
private:
  /// class instance, initialize nullptr
  static Motor *instance;
  /// Mem_Access class instance, initialize nullptr
  Mem_Access *access = nullptr;

  /// Pwm class instance, initialize nullptr
  Pwm *pwm = nullptr;

  /**
   * @brief 
   *  initialize GPIO Pin settings.
  */ 
  void init();
  
public:

  /**
   * constructor
  */ 
  Motor();

  /**
   * destructor
  */  
  ~Motor();

  /**
   * @brief get this class instance
   * @return this instance pointer
   * @details
   *  if instance is nullptr, new create instance and return pointer.
  */
  static Motor* getInstance();

  void turnOnOff(bool left, bool right);

  void set(int32_t left, int32_t right);
};

#endif /* __MOTOR_H */