/**
 * @file motor.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined Motor class.
*/ 

#ifndef __MOTOR_H
#define __MOTOR_H

#include "mem_access.h"
#include "pipwm.h"

// gpio16 leftdir
// gpio6 rightdir 

/**
 * @class Motor
 * @brief 
 *  Control motor.
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
   *  initialize GPIO setting.
  */ 
  void init();

  /**
   * @brief 
   *  set GPIO mode ALT(use PWM) or GPIO output mode.
  */ 
  void controlPWMOutput(bool left, bool right);

  /**
   * @brief 
   *  motor dir pin turn on/off
  */ 
  void controlDirection(bool left, bool right);
  
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

  /**
   * @brief 
   *  set GPIO motor enable Pin.
  */ 
  void enable();

  /**
   * @brief 
   *  clear GPIO motor enable Pin.
  */ 
  void disable();

  /**
   * @brief
   *  control motor left/right.
   * @param left set left motor frequency
   * @param right set right motor frequency
   */ 
  void control(int left, int right);

};

#endif /* __MOTOR_H */