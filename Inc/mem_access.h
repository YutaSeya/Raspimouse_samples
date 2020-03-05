#ifndef __MEM_ACCESS_H
#define __MEM_ACCESS_H

#include <stdint.h>
#include <mutex>

extern std::mutex _mtx;

class Mem_Access
{
private:
  #define REG(addr) (*((volatile uint32_t*)(addr)))
  bool busy = false;
  int fd;
  uint32_t address; 
  uint32_t now_periperal_length = 0;
  int8_t error = 0;
  static Mem_Access *instance;
  
  void openMEM();
  void getAddress(uint32_t length, uint32_t offset);
  void closeMEM(uint32_t size);
  
public:
  Mem_Access();
  ~Mem_Access();

  static Mem_Access* getInstance();
  void openPeriperal(uint32_t length, uint32_t offset);
  void openPeriperal(uint32_t offset);
  void closePeriperal();
  void setBit(uint32_t reg_offset, uint32_t bit);
  void writeReg(uint32_t reg_offset, uint32_t val);
  uint32_t readBit(uint32_t reg_offset, uint32_t bit);
  uint32_t readByte(uint32_t reg_offset);
  bool checkBusy() const { return busy; }

};

#endif /* __MEM_ACCESS_H */