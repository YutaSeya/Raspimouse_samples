#include "sensor.h"

#include "register_address.h"

#include <unistd.h>

Sensor* Sensor::instance = nullptr;

Sensor::Sensor()
{
  access = Mem_Access::getInstance();
  mcp3204 = Mcp3204::getInstance();
  init();
}

Sensor::~Sensor()
{
  delete instance;
}

Sensor* Sensor::getInstance()
{
  if ( instance == nullptr ){
    instance = new Sensor();
  }
  return instance;
}

void Sensor::init()
{
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // set gpio output mode
  // set gpio pin 4
  access->setBit(RPI_GPIO_GPFSEL0, 1 << 12);
  // set gpio pin 17
  access->setBit(RPI_GPIO_GPFSEL1, 1 << 21);
  // set gpio pin 22
  access->setBit(RPI_GPIO_GPFSEL2, 1 << 6);
  // set gpio pin 27
  access->setBit(RPI_GPIO_GPFSEL2, 1 << 21);

  access->closePeriperal();
  _mtx.unlock();
}

void Sensor::setSensorParam(uint8_t select, int16_t _threshold, int16_t _referense)
{
  if(select == LEFT_FRONT){
    left_front.threshold = _threshold;
    left_front.referense = _referense;
  } else if(select == LEFT){
    left.threshold = _threshold;
    left.referense = _referense;
  } else if (select == RIGHT){
    right.threshold = _threshold;
    right.referense = _referense;
  } else if(select == RIGHT_FRONT) {
    right_front.threshold = _threshold;
    right_front.referense = _referense;
  } else {
    front.threshold = _threshold;
    front.referense = _referense;
  }
}

void Sensor::update()
{
  int16_t off_data[4];
  int16_t on_data[4];
  // get light off sensor data
  off_data[LEFT_FRONT] = mcp3204->getAD(Mcp3204::SENSOR_LEFT_FRONT);
  off_data[LEFT] = mcp3204->getAD(Mcp3204::SENSOR_LEFT);
  off_data[RIGHT] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT);
  off_data[RIGHT_FRONT] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT_FRONT);

  // left front
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // write pin
  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 17);

  access->closePeriperal();
  _mtx.unlock();

  usleep(3);
  on_data[LEFT_FRONT] = mcp3204->getAD(Mcp3204::SENSOR_LEFT_FRONT);

  // left
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // clear pin
  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 17);

  // write pin
  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 4);

  access->closePeriperal();
  _mtx.unlock();

  usleep(3);

  on_data[LEFT] = mcp3204->getAD(Mcp3204::SENSOR_LEFT);

  // right
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // clear pin
  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 4);

  // write pin
  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 22);

  access->closePeriperal();
  _mtx.unlock();

  usleep(3);

  on_data[RIGHT] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT);

  // right front
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // clear pin
  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 22);

  // write pin
  access->setBit(RPI_GPIO_OUTPUT_SET_0, 1 << 27);

  access->closePeriperal();
  _mtx.unlock();

  usleep(3);

  on_data[RIGHT_FRONT] = mcp3204->getAD(Mcp3204::SENSOR_RIGHT_FRONT);

  // off r_f led
  _mtx.lock();
  // wait busy flag down
  while( access->checkBusy() );

  access->openPeriperal(RPI_GPIO_SIZE, RPI_GPIO_BASE);

  // clear pin
  access->setBit(RPI_GPIO_OUTPUT_CLR_0, 1 << 27);

  access->closePeriperal();
  _mtx.unlock();

  // update sensor data
  left_front.before = left_front.now;
  left.before = left.now;
  right.before = right.now;
  right_front.before = right_front.now;

  left_front.now = on_data[LEFT_FRONT] - off_data[LEFT_FRONT];
  left.now = on_data[LEFT] - off_data[LEFT];
  right.now = on_data[RIGHT] - off_data[RIGHT];
  right_front.now = on_data[RIGHT_FRONT] - off_data[RIGHT_FRONT];

  left_front.diff = left_front.now - left_front.before;
  left.diff = left.now - left.before;
  right.diff = right.now - right.before;
  right_front.diff = right_front.now - right_front.before;
  if(left_front.diff < 0) left_front.diff = -1 * left_front.diff;
  if(left.diff < 0) left.diff = -1 * left.diff;
  if(right.diff < 0) right.diff = -1 * right.diff;
  if(right_front.diff < 0) right_front.diff = -1 * right_front.diff; 

  front.before = front.now;

  front.now = (left_front.now + right_front.now) / 2;
  front.diff = front.now - front.before;
  if(front.diff < 0) front.diff = -1 * front.diff;

  // update wall data. do not update l_f and r_f 
  if(left.now > left.threshold) left.wall = true;
  else left.wall = false;

  if(right.now > right.threshold) right.wall = true;
  else right.wall = false;

  if(front.now > front.threshold) front.wall = true; 
  else front.wall = false;

}

Sensor_Data Sensor::get(uint8_t select)
{
  if(select == LEFT_FRONT){
    return left_front;
  } else if(select == LEFT){
    return left;
  } else if (select == RIGHT){
    return right;
  } else if(select == RIGHT_FRONT) {
    return right_front;
  } else {
    return front;
  }
}
