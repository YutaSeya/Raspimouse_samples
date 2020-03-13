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

#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

/**
 * @class Mcp3204
 * @brief 
 *  This class is get mcp3204 AD convert data by SPI(Serial Peripheral Interface).
 * | MISO   | MOSI   | SCLK   | CS     | 
 * | :----: | :----: | :----: | :----: |
 * | GPIO9  | GPIO10 | GPIO11 | GPIO8  |
*/ 
class Mcp3204
{
private:
  /// class instance, intialize nullptr
  static Mcp3204 *instance;


  /**
   * @brief 
   *  
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

};

#endif /* __MCP3204_H */