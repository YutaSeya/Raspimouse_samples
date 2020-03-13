/**
 * @file mcp3204.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined MCP3204 class.
*/ 

#ifndef __MCP3204_H
#define __MCP3204_H

#include "mem_access.h"

/**
 * @class Mcp3204
 * @brief 
 *  get mcp3204 AD convert data by SPI(Serial Peripheral Interface).
 * | MISO   | MOSI   | SCLK   | CS     | 
 * | :----: | :----: | :----: | :----: |
 * | GPIO9  | GPIO10 | GPIO11 | GPIO8  |
 * MCP3204 ch table.
 * |  L_F    |  LEFT   |  RIGHT  |  R_F    | 
 * | :-----: | :-----: | :-----: | :-----: |
 * |  CH1    |  CH0    |  CH3    |  CH2    |
*/ 
class Mcp3204
{
private:
  /// class instance, initialize nullptr
  static Mcp3204 *instance;

  /// spi File descriptor
  int fd;
  // spi communication bits
  uint8_t bits = 8;
  // spi communication speed
  uint32_t speed = 1000000;

  /**
   * @brief 
   *  initialize SPI configration.
  */ 
  void init();

public:
  
  /**
   * constructor
  */  
  Mcp3204();
  
  /**
   * destructor
  */  
  ~Mcp3204();

  /**
   * @brief get this class instance
   * @return this instance pointer
   * @details
   *  if instance is nullptr, new create instance and return pointer.
  */
  static Mcp3204* getInstance();

  /**
  * @enum Sensor_Number
  * use function getAD param 
  */
  enum Sensor_Number{
    SENSOR_LEFT,
    SENSOR_LEFT_FRONT,
    SENSOR_RIGHT_FRONT,
    SENSOR_RIGHT,
  };

  /**
   * @brief 
   *  communication SPI
   * @param *tx send data
   * @param *rx read data
   * @param length send/read data length
   * @details
   */ 
  void communication(uint8_t *tx, uint8_t *rx, uint8_t length);

  /**
   * @brief 
   *  get MCP3204 A/D convert data
   * @param sensor_number SENSOR_NUMBER 
   * @return A/D Convert Data
   * @details
   *  Get the value of the port specified 
   *  in the argument.
   */ 
  uint16_t getAD(uint8_t sensor_number);

};

#endif /* __MCP3204_H */