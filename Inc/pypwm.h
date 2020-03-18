/**
 * @file pwm.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined Pwm class.
*/ 

#ifndef __PYPWM_H
#define __PYPWM_H

#include "mem_access.h"

/**
 * @class Pwm
 * @brief 
 *  Control pwm parameter.
 * @details
 * GPIO PIN Correspondence Table.
 * | PWM0   | PWM1   |
 * | :----: | :----: |
 * | GPIO12 | GPIO13 |
*/ 
class Pwm
{
private:
   /// class instance, initialize nullptr
  static Pwm *instance;
  /// Mem_Access class instance, initialize nullptr
  Mem_Access *access = nullptr;

  /**
   * @brief 
   *  initialize GPIO Pin settings.
  */ 
  void init();

  int getPWMCount(uint32_t freq);

public:
  
  /**
   * constructor
  */ 
  Pwm();

  /**
   * destructor
  */  
  ~Pwm();

  /**
   * @brief get this class instance
   * @return this instance pointer
   * @details
   *  if instance is nullptr, new create instance and return pointer.
  */
  static Pwm* getInstance();

  void set1(uint32_t freq);

  void set2(uint32_t freq);

  void set(uint32_t ch1_freq, uint32_t ch2_freq);

};

#endif /* __PYPWM_H */