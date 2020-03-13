/**
 * @file led.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined Led class.
*/ 

#ifndef __LED_H
#define __LED_H

#include <stdint.h>
#include "mem_access.h"

/**
 * @class Led
 * @brief 
 *  Control to turn on / off UI LEDs.
 * @details
 * GPIO PIN Correspondence Table.
 * | LED0   | LED1   | LED2   | LED3   | 
 * | :----: | :----: | :----: | :----: |
 * | GPIO25 | GPIO24 | GPIO23 | GPIO18 |
*/ 
class Led
{
private:
  /// class instance, initialize nullptr
  static Led *instance;
  /// Mem_Access class instance, initialize nullptr
  Mem_Access *access = nullptr;

  /**
   * @brief 
   *  initialize GPIO Pin settings.
  */ 
  void init();
  
public:

  /**
   * constructor
  */ 
  Led();

  /**
   * destructor
  */  
  ~Led();

  /**
   * @brief get this class instance
   * @return this instance pointer
   * @details
   *  if instance is nullptr, new create instance and return pointer.
  */
  static Led* getInstance();

  /**
   * @brief Turn on / off UI leds.
   * @param _light Set the value corresponding to the LED on following UI LED Correspondence table.
   * @details 
   *  UI LED Correspondence Table. 
   * _light : Lower rank 4bit 
   * |   1    |   1    |   1    |   1    |
   * | :----: | :----: | :----: | :----: |
   * | LED3   | LED2   | LED1   | LED0   |
  */
  void illuminate(uint8_t _light);

};

#endif /* __LED_H */