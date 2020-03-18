/**
 * @file pipwm.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined Pwm class.
*/ 

#ifndef __PIPWM_H
#define __PIPWM_H

#include "mem_access.h"

/**
 * @class Pwm
 * @brief 
 *  Control pwm parameter.
 * @details
 * GPIO PIN Correspondence Table.
 * | PWM0    | PWM1    | PWM1   |
 * | :----:  | :----:  | :----: |
 * | GPIO12  | GPIO13  | GPIO19 |
 * | Motor_L | Motor_R | Buzzer |
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
   *  initialize PWM and CLK register.
  */ 
  void init();

  /**
   * @brief 
   *  calculate pwm count. 
   * @return pwm count
  */ 
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

  /**
   * @brief 
   *  set pwm1 frequency
   * @param freq set frequency
  */ 
  void set1(uint32_t freq);

  /**
   * @brief 
   *  set pwm2 frequency
   * @param freq set frequency
  */ 
  void set2(uint32_t freq);

  /**
   * @brief 
   *  set pwm1 , 2 frequency
   * @param ch1_freq set pwm1 frequency
   * @param ch2_freq set pwm2 frequency
  */ 
  void set(uint32_t ch1_freq, uint32_t ch2_freq);

};

#endif /* __PIPWM_H */