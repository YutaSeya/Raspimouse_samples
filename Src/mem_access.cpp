#include "mem_access.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

std::mutex _mtx;

//#define __USE_64BITOS

Mem_Access* Mem_Access::instance = nullptr;

Mem_Access::Mem_Access()
{
}

Mem_Access::~Mem_Access()
{
  delete instance;
}

Mem_Access* Mem_Access::getInstance()
{
  if ( instance == nullptr ){
    instance = new Mem_Access();
  }
  return instance;
}

void Mem_Access::openMEM()
{
  if ((fd = open("/dev/mem", O_RDWR | O_SYNC)) < 0) {
    perror("open");
    error = -1;
  }
  busy = true;
}

void Mem_Access::getAddress(uint32_t length, uint32_t offset)
{
  // addressを取得する
  if(error == 0){
    #if __USE_64BITOS 
      address = (uint32_t)mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED|MAP_FIXED, fd, offset);
    #else 
      address = (uint32_t)mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_SHARED, fd, offset);
    #endif
    if (address == MAP_FAILED) {
      perror("mmap");
      close(fd);
      error = -2;
    } else {
      now_periperal_length = length;
    }
  } 
}

void Mem_Access::openPeriperal(uint32_t length, uint32_t offset)
{
  // fdを開く
  openMEM();
  // アドレスを取得する
  getAddress(length, offset);

  if(error <0){
    while(1){
      if(error == -1){
        printf("not open fd\r");
      } else if(error == -2){ 
        printf("not get correct address\n");
      }
    }
  }
}

void Mem_Access::openPeriperal(uint32_t offset)
{
  // fdを開く
  openMEM();
  // アドレスを取得する
  getAddress(0x1000, offset);

  if(error <0){
    while(1){
      if(error == -1){
        printf("not open fd\r");
      } else if(error == -2){ 
        printf("not get correct address\n");
      }
    }
  }
}

void Mem_Access::closeMEM(uint32_t length)
{
  munmap((void*)address, length);
  close(fd);
  busy = false;
}

void Mem_Access::closePeriperal()
{
  closeMEM(now_periperal_length);
  error = false;
}

void Mem_Access::setBit(uint32_t reg_offset, uint32_t bit)
{
  REG(address + reg_offset) |= bit;
}

void Mem_Access::writeReg(uint32_t reg_offset, uint32_t val)
{
  REG(address + reg_offset) = val;
}

uint32_t Mem_Access::readBit(uint32_t reg_offset, uint32_t bit)
{
  return (uint32_t)(REG(address  + reg_offset) & bit);
}
  
uint32_t Mem_Access::readByte(uint32_t reg_offset)
{
  return (uint32_t)(REG(address  + reg_offset));
}