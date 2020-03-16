/**
 * @file register_address.h
 * @author Yuta S.
 * @version 0.1
 * @brief The file defined the Raspberry Pi registers.
*/ 

#ifndef __REGISTER_ADDRESS_H
#define __REGISTER_ADDRESS_H

/* bcm2835 param */
#define BCM2835_CORE_CLK_HZ 250000000

/* --- Register Address --- */
/* Base Addr */
#define RPI_REG_BASE 0x3f000000

/* GPIO Addr */
#define RPI_GPIO_OFFSET 0x200000
#define RPI_GPIO_SIZE 0xC0
#define RPI_GPIO_BASE (RPI_REG_BASE + RPI_GPIO_OFFSET)

#define RPI_GPIO_GPFSEL0 0x000000
#define RPI_GPIO_GPFSEL1 0x000004
#define RPI_GPIO_GPFSEL2 0x000008
#define RPI_GPIO_GPFSEL3 0x00000C
#define RPI_GPIO_GPFSEL4 0x000010
#define RPI_GPIO_GPFSEL5 0x000014

#define RPI_GPIO_OUTPUT_SET_0 0x001C
#define RPI_GPIO_OUTPUT_SET_1 0x0020

#define RPI_GPIO_OUTPUT_CLR_0 0x0028
#define RPI_GPIO_OUTPUT_CLR_1 0x002C

#define RPI_GPIO_LEVEL_0      0x0034
#define RPI_GPIO_LEVEL_1      0x0038

/* Pwm Addr */
#define RPI_PWM_OFFSET 0x20C000
#define RPI_PWM_SIZE 0xC0
#define RPI_PWM_BASE (RPI_REG_BASE + RPI_PWM_OFFSET)

/* PWM Index */
#define RPI_PWM_CTRL 0x0
#define RPI_PWM_STA 0x4
#define RPI_PWM_DMAC 0x8
#define RPI_PWM_RNG1 0x10
#define RPI_PWM_DAT1 0x14
#define RPI_PWM_FIF1 0x18
#define RPI_PWM_RNG2 0x20
#define RPI_PWM_DAT2 0x24

#define PWM_BASECLK 9600000

/* Clock Addr */
#define RPI_CLK_OFFSET 0x101000
#define RPI_CLK_SIZE 0x100
#define RPI_CLK_BASE (RPI_REG_BASE + RPI_CLK_OFFSET)

#define BCM2835_PWM_PASSWRD (0x5A << 24)

/* Clock Offset */
#define CLK_PWM_INDEX 0xA0
#define CLK_PWMDIV_INDEX 0xA4

#endif /* __REGISTER_ADDRESS_H */