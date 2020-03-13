/**
 * @file sensor.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined Sensor class and Sensor_Data sturuct.
*/ 

#ifndef __SENSOR_H
#define __SENSOR_H

#include <stdint.h>

#include "mem_access.h"
#include "mcp3204.h"

/**
 * @struct Sensor_Data
 * @brief
 *  store sensor data
 */ 
struct Sensor_Data
{
  int16_t now;
  int16_t diff;
  int16_t before;
  bool wall;
  int16_t threshold;
  int16_t referense;
};

/**
 * @class Sensor
 * @brief 
 *  control wall sensor and get A/D data.
 * @details
 *  wall sensor LED GPIO PIN Correspondence Table.
 * |  L_F    |  LEFT   |  RIGHT  |  R_F    | 
 * | :-----: | :-----: | :-----: | :-----: |
 * |  GPIO17 |  GPIO4  |  GPIO22 |  GPIO27 |
*/ 
class Sensor
{
private:

  /// class instance, initialize nullptr
  static Sensor *instance;
  
  /// Mem_Access class instance, initialize nullptr
  Mem_Access *access = nullptr;

  /// Mcp3204 class instance, initialize nullptr
  Mcp3204 *mcp3204 = nullptr;

  /// sensor left data
  Sensor_Data left;
  /// sensor right data
  Sensor_Data right;
  /// sensor left front data
  Sensor_Data left_front;
  /// sensor right front data
  Sensor_Data right_front;
  /// sensor front data((L_F + R_F) /2)
  Sensor_Data front;

  /**
   * @brief 
   *  initialize GPIO Pin mode.
  */ 
  void init();

  /**
   * @brief 
   *  sensor led off.
  */ 
  void turnOffSensorLED();

public:

  /**
   * constructor
  */  
  Sensor();

  /**
   * destructor
  */  
  ~Sensor();

  /**
   * @brief get this class instance
   * @return this instance pointer
   * @details
   *  if instance is nullptr, new create instance and return pointer.
  */
  static Sensor* getInstance();

  /**
  * @brief
  * get sensor struct data
  * @param Sensor_Name
  * @param set wall threshold
  * @param set sensor referense
  * @details
  * use MicroMause Program
  */  
  void setSensorParam(uint8_t select, int16_t _threshold, int16_t _referense);

  /**
  * @enum Sensor_Name
  * use function get sensor
  */
  enum Sensor_Name{
    LEFT_FRONT,
    LEFT,
    RIGHT,
    RIGHT_FRONT,
    FRONT,
  };

  /**
  * @brief
  * update sensor data
  * @details
  *  update sensor now, before, diff, wall(*)
  *  (*)attention. this function do not update wall information both left_front and right_front.
  *     if you need there's wall data, you need to write a program.
  */
  void update();

  /**
  * @brief
  * get sensor struct data
  * @param Sensor_Name
  * @return selected struct
  * @details
  */
  Sensor_Data get(uint8_t select);

};

#endif /* __SENSOR_H */