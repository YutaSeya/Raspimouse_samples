/**
 * @file switch.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined Switch class.
*/ 

#ifndef __SWITCH_H
#define __SWITCH_H

#include <stdint.h>
#include "mem_access.h"

/**
 * @class Switch
 * @brief 
 *  Get Switch data.
 * @details
 * GPIO PIN Correspondence Table.
 * | SW0    | SW1    | SW2    | 
 * | :----: | :----: | :----: |
 * | GPIO20 | GPIO26 | GPIO21 | 
*/ 
class Switch
{

private:
  /// class instance, intialize nullptr
  static Switch* instance;

  /// Mem_Access class instance, intialize nullptr
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
  Switch();

  /**
   * destructor
  */  
  ~Switch();

  /**
   * @brief get this class instance
   * @return this instance pointer
   * @details
   *  if instance is nullptr, new create instance and return pointer.
  */
  static Switch* getInstance();

  /**
   * @brief get sw0
   * @return uint32_t 1(on) / 0(off) 
  */
  uint32_t get0();

  /**
   * @brief get sw1
   * @return uint32_t 1(on) / 0(off) 
  */
  uint32_t get1();

  /**
   * @brief get sw2
   * @return uint32_t 1(on) / 0(off) 
  */
  uint32_t get2();

  /**
   * @brief get sw all
   * @return uint32_t all sw data on follwoing Switch correspondence table
   * @details
   *  Switch correspondence table : return lower rank 3bit
   *  |   1    |   1    |   1    | 
   *  | :----: | :----: | :----: |
   *  |  SW2   |  SW1   |  SW0   |
  */
  uint32_t getAll();
};

#endif /* __SWITCH_H */