#include "pypwm.h"

#include "register_address.h"

#include <unistd.h>

Pwm* Pwm::instance = nullptr;

Pwm::Pwm()
{
  access = Mem_Access::getInstance();
  init();
}

Pwm::~Pwm()
{
  delete instance;
}

Pwm* Pwm::getInstance()
{
  if(instance == nullptr){
    instance = new Pwm();
  }
  return instance;
}

void Pwm::init()
{
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // set gpio ALT0
  // set gpio pin 12
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 8);
  // set gpio pin 13
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 11);

  // set gpio 19 pwm output
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 27);

  // set gpio 18 gpio output
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 24);

  access->closePeriperal();

  // setting clk 
  access->openPeriperal(RPI_CLK_BASE);
  
  // stop pwm clock
  access->writeReg(CLK_PWM_INDEX, (BCM2835_PWM_PASSWRD | 1 << 5));

  // wait clock down
  sleep(1);

  // clk set
  access->writeReg(CLK_PWMDIV_INDEX, (BCM2835_PWM_PASSWRD | (2 << 12)) );
  access->writeReg(CLK_PWM_INDEX, (BCM2835_PWM_PASSWRD | 0x03));

  sleep(1);
  
  access->closePeriperal();

  // start pwm setting
  access->openPeriperal(RPI_PWM_BASE);

  // pwm enable ch1, ch2
  access->writeReg(RPI_PWM_CTRL, 0x00008181);
  
  access->closePeriperal();

  _mtx.unlock();
}

int Pwm::getPWMCount(uint32_t freq)
{
  if(freq < 1) return PWM_BASECLK;
  
  if(freq > 10000) return PWM_BASECLK / 10000;

  return PWM_BASECLK / freq;
}

void Pwm::set1(uint32_t freq)
{
  uint32_t dat = getPWMCount(freq);
  
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );
  // start pwm setting
  access->openPeriperal(RPI_PWM_BASE);

  access->writeReg(RPI_PWM_RNG1, dat);
  access->writeReg(RPI_PWM_DAT1, dat >> 1);
  
  access->closePeriperal();

  _mtx.unlock();
}

void Pwm::set2(uint32_t freq)
{
  uint32_t dat = getPWMCount(freq);
  
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );
  // start pwm setting
  access->openPeriperal(RPI_PWM_BASE);

  access->writeReg(RPI_PWM_RNG2, dat);
  access->writeReg(RPI_PWM_DAT2, dat >> 1);
  
  access->closePeriperal();

  _mtx.unlock();
}

void Pwm::set(uint32_t ch1_freq, uint32_t ch2_freq)
{
  uint32_t ch1_dat = getPWMCount(ch1_freq);
  uint32_t ch2_dat = getPWMCount(ch2_freq);

  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );
  // start pwm setting
  access->openPeriperal(RPI_PWM_BASE);

  access->writeReg(RPI_PWM_RNG1, ch1_dat);
  access->writeReg(RPI_PWM_DAT1, ch1_dat >> 1);

  access->writeReg(RPI_PWM_RNG2, ch2_dat);
  access->writeReg(RPI_PWM_DAT2, ch2_dat >> 1);
  
  access->closePeriperal();

  _mtx.unlock();
}