#include "mcp3204.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>

Mcp3204* Mcp3204::instance = nullptr;

Mcp3204::Mcp3204()
{
  _mtx.lock();
  init();
  _mtx.unlock();
}

Mcp3204::~Mcp3204()
{
  close(fd);
  delete instance;
}

Mcp3204* Mcp3204::getInstance()
{
  if ( instance == nullptr ){
    instance = new Mcp3204();
  }
  return instance;
} 

void Mcp3204::init()
{
  int bits = 8;

  fd = open("/dev/spidev0.0", O_RDWR | O_SYNC);
  
  if(fd < 0){
    while(1){
      printf("Do not oepn spi device driver\r");
    }
  }

  // set spi mode
  // write mode
  ioctl(fd, SPI_IOC_WR_MODE, SPI_MODE_3);
  // read mode
  ioctl(fd, SPI_IOC_RD_MODE, SPI_MODE_3);

  // set communication bits
  ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);

	ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);

  // set communication speed
  ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

	ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);

}

void Mcp3204::communication(uint8_t *tx, uint8_t *rx, uint8_t length)
{

	struct spi_ioc_transfer tr = {
		.tx_buf = (unsigned long)tx,
		.rx_buf = (unsigned long)rx,
		.len = length,
    .speed_hz = speed,
		.delay_usecs = 0,
		.bits_per_word = bits,
	};

  _mtx.lock();

  ioctl(fd, SPI_IOC_MESSAGE(1), &tr);

  _mtx.unlock();
}

uint16_t Mcp3204::getAD(uint8_t sensor_number)
{
  uint8_t tx_buff[3];
  uint8_t rx_buff[3];

  // set send data
  tx_buff[0] = (0x06 | (sensor_number >> 2));
  tx_buff[1] = (sensor_number << 6);
  tx_buff[2] = 0x00;

  communication(tx_buff, rx_buff, 3);

  uint16_t ret = 0;
  ret = (rx_buff[1] & 0x0f) << 8;
  ret|= rx_buff[2];
  return ret;
}