#include <iostream>
#include <cstdio>
#include <unistd.h>

#include "register_address.h"
#include "mem_access.h"

#include "led.h"
#include "switch.h"
#include "mcp3204.h"
#include "sensor.h"
#include "pipwm.h"

void led_test();
void sw_test();
void mcp3204_test();
void sensor_test();

void motor_left_test()
{
  // motor enable pin setting
  Mem_Access *access = Mem_Access::getInstance();

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE);

  // GPIO12 set alt 0 
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 6);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 8);
  // GPIO13 set alt 0 
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 9);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 11);

  // gpio 5 output
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 15);

  // GPIO16 output 
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 18);
  // setting dir bit
  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 16);

  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 5);

  access->closePeriperal();

  _mtx.unlock();

  Pwm *pwm = Pwm::getInstance();

  std::printf("pwm setting done.\n");
  for(int i = 500; i < 1500; i+=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(i, 0);
    sleep(1);
  }

  for(int i = 1300; i > 400; i-=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(i, 0);
    sleep(1);
  }

  pwm->set(0,0);

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE);

  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 16);

  access->closePeriperal();

  _mtx.unlock();

  std::printf("inverse check\r\n");
  for(int i = 500; i < 1000; i+=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(i, 0);
    sleep(1);
  }

  for(int i = 900; i > 400; i-=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(i, 0);
    sleep(1);
  }

  pwm->set(0,0);

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE);

  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 5);

  // GPIO12 gpio output
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 8);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 6);
  // GPIO13 gpio output
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 11);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 9);

  access->closePeriperal();

  _mtx.unlock();
}

void motor_right_test()
{
  // motor enable pin setting
  Mem_Access *access = Mem_Access::getInstance();

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE);

  // GPIO12 set alt 0 
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 6);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 8);
  // GPIO13 set alt 0 
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 9);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 11);

  // GPIO5 output
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 15);
  // GPIO6 output 
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 18);

  // setting dir bit
  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 5);

  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 6);

  access->closePeriperal();

  _mtx.unlock();

  Pwm *pwm = Pwm::getInstance();

  std::printf("pwm setting done.\n");
  for(int i = 500; i < 1000; i+=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(0, i);
    sleep(1);
  }

  for(int i = 900; i > 400; i-=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(0, i);
    sleep(1);
  }

  pwm->set(0,0);

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE);

  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 6);

  access->closePeriperal();

  _mtx.unlock();

  std::printf("inverse check\r\n");
  for(int i = 500; i < 1000; i+=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(0, i);
    sleep(1);
  }

  for(int i = 900; i > 400; i-=100){
    std::printf("set 1 set2 %d\n", i);
    pwm->set(0, i);
    sleep(1);
  }

  pwm->set(0,0);

  _mtx.lock();
  while(access->checkBusy());

  access->openPeriperal(RPI_GPIO_SIZE);

  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 5);

  // GPIO12 gpio output
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 8);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 6);
  // GPIO13 gpio output
  access->clearBit(RPI_GPIO_GPFSEL1, 1 << 11);
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 9);

  access->closePeriperal();

  _mtx.unlock();
}

int main()
{
  //led_test();
  //sw_test();
  //mcp3204_test();
  //sensor_test();
  motor_left_test();
  motor_right_test();

  return 0;
}

void led_test()
{
  Led *led = Led::getInstance();

  for(int i = 0; i < 16; i++){
    led->illuminate(i);
    sleep(1);
  }
  
  led->illuminate(0);
}

void sw_test()
{
  Switch *sw = Switch::getInstance();

  std::printf("ctr + c exit this program\n");

  while(1){
    std::printf("sw0 : %d, sw1 : %d, sw2 : %d, all : %d\r", sw->get0(), sw->get1(), sw->get2(), sw->getAll() );
  }
  
}

void mcp3204_test()
{

  Mcp3204 *mcp3204 = Mcp3204::getInstance();
  
  std::printf("ctr + c exit this program\n");
  std::printf("left_front, left, right, right_fornt\n");

  while(1)
  {
    uint16_t ad_data[4];
    ad_data[0] = mcp3204->getAD(Mcp3204::SENSOR_LEFT_FRONT);
    ad_data[1] = mcp3204->getAD(Mcp3204::SENSOR_LEFT);
    ad_data[2] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT);
    ad_data[3] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT_FRONT);
    std::printf("%4d,%4d,%4d,%4d\r\n",ad_data[0], ad_data[1], ad_data[2], ad_data[3]);
    sleep(1);
  }

}

void sensor_test()
{
  Sensor *sensor = Sensor::getInstance();
  Sensor_Data sensor_data;
  int16_t sensor_value[5];
  std::printf("ctr + c exit this program\n");
  std::printf("left_front, left, right, right_front, front\n");
  int count = 0;

  while(1){
    sensor->update();
    sensor_data = sensor->get(Sensor::LEFT_FRONT);
    sensor_value[0] = sensor_data.now;

    sensor_data = sensor->get(Sensor::LEFT);
    sensor_value[1] = sensor_data.now;

    sensor_data = sensor->get(Sensor::RIGHT);
    sensor_value[2] = sensor_data.now;

    sensor_data = sensor->get(Sensor::RIGHT_FRONT);
    sensor_value[3] = sensor_data.now;

    sensor_data = sensor->get(Sensor::FRONT);
    sensor_value[4] = sensor_data.now;

    std::printf("%4d, %4d, %4d, %4d, %4d\n", sensor_value[0],
    sensor_value[1],sensor_value[2],sensor_value[3],sensor_value[4] );
    count++;
    sleep(1);
    if(count > 120) break;
  }

  sensor->turnOffSensorLED();

}