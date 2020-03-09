/**
 * @file mem_access.h
 * @author Yuta S.
 * @version 0.1
 * @brief 
 * The file defined Mem_Access class.
*/ 

#ifndef __MEM_ACCESS_H
#define __MEM_ACCESS_H

#include <stdint.h>
#include <mutex>

extern std::mutex _mtx;

/**
 * @class Mem_Access
 * @brief 
 *  This class is open /dev/mem and get address 
 *  for read / write register
 *  Afterwards, Write / Read register.
*/ 
class Mem_Access
{
private:
  /**
   * @def 
   * access the register at addr.
   */ 
  #define REG(addr) (*((volatile uint32_t*)(addr)))

  /// busy check flag. Simultaneous access measures.
  bool busy = false;
  /// File descriptor
  int fd;
  /// store getting Address
  uint32_t address; 
  /// store useing address length
  uint32_t now_periperal_length = 0;
  /// use errror check 
  int8_t error = 0;
  /// class instance, intialize nullptr
  static Mem_Access *instance;
  
  /**
   * @brief open /dev/mem.
   * @details
   * if open error, assign -1 to error.
  */  
  void openMEM();

  /**
   * @brief get addresss by offset and length.
   * @param lenght set getting address length
   * @param offset set offset device address
   * @details
   * if open error, assign -2 to error.
  */
  void getAddress(uint32_t length, uint32_t offset);
  
  /**
   * @brief close fd, release address
   * @param size set releasing address length
   * @details
  */
  void closeMEM(uint32_t length);
  
public:
  /**
   * constructor
  */  
  Mem_Access();
  
  /**
   * destructor
  */  
  ~Mem_Access();

  /**
   * @brief get this class instance
   * @return this instance pointer
   * @details
   *  if instance is nullptr, new create instance and return pointer.
  */
  static Mem_Access* getInstance();

  /**
   * @brief open peripheral by length and offset.
   * @param lenght set getting address length
   * @param offset set offset device address
   * @details
   *  if error, output error code and while loop.
  */
  void openPeriperal(uint32_t length, uint32_t offset);

  /**
   * @brief open peripheral by offset.
   * @param offset set offset device address
   * @details
   *  if error, output error code and while loop.
  */
  void openPeriperal(uint32_t offset);

  /**
   * @brief close peripheral.
   * @details
  */
  void closePeriperal();

  /**
   * @brief set bit by reg_offset.
   * @param reg_offset set offset device address
   * @param bit set bit data
   * @details
   *  Use exsample, Set GPIO4 Pin setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 4)
  */
  void setBit(uint32_t reg_offset, uint32_t bit);

  /**
   * @brief clear bit by reg_offset.
   * @param reg_offset set offset device address
   * @param bit set bit data
   * @details
   *  Use exsample, clear GPIO4 Pin clearBit(RPI_GPIO_OUTPUT_SET_0, 1 << 4)
  */
  void clearBit(uint32_t reg_offset, uint32_t bit);

  /**
   * @brief write byte by reg_offset.
   * @param reg_offset set offset device address
   * @param val set byte data
   * @details
   *  Use exsample, Set GPIO3 and GPIO4 writeReg(RPI_GPIO_OUTPUT_SET_0, 0x0007)
  */
  void writeReg(uint32_t reg_offset, uint32_t val);

  /**
   * @brief read bit by reg_offset.
   * @param reg_offset set offset device address
   * @param bit set bit data
   * @return uint32_t bit data
   * @details
   *  Use exsample, read GPIO4 Pin readBit(RPI_GPIO_OUTPUT_SET_0, 1 << 4);
   *  if you want to read in binary, you need to add a bit shift.
   *  sample: (readBit(RPI_GPIO_OUTPUT_SET_0, 1 << 4) >> 4);
  */
  uint32_t readBit(uint32_t reg_offset, uint32_t bit);

  /**
   * @brief read byte by reg_offset.
   * @param reg_offset set offset device address
   * @return uint32_t read byte data
   * @details
   *  Use exsample, read input pin register readByte(RPI_GPIO_OUTPUT_SET_0)
  */
  uint32_t readByte(uint32_t reg_offset);
  
  /**
   * @brief check busy flags.
   * @param 
   * @return bool busy
   * @details
   *  Use exsample, while( access->checkBusy() );
   *  you wait until resources are released.
  */
  bool checkBusy() const { return busy; }

};

#endif /* __MEM_ACCESS_H */