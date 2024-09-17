#include <stdint.h>
#include <Delay_ms.h>
#include <gpio.h>
#include "stm32g431xx.h"

#ifndef I2C_h
#define I2C_h

#define I2C_BASE 0x40005400
// Offset
#define I2C_CR1_OFFSET 0x00
#define I2C_CR2_OFFSET 0x04
#define I2C_TIMINGR_OFFSET 0x10
#define I2C_ISR_OFFSET 0x18
#define I2C_TXDR_OFFSET 0x28
#define I2C_ICR_OFFSET 0x1C
#define I2C_RXDR_OFFSET 0x24

// Register-Zugriff
#define REG32(addr) (*(volatile uint32_t *)(addr))

#define I2C_CR1 REG32(I2C_BASE + I2C_CR1_OFFSET)
#define I2C_CR2 REG32(I2C_BASE + I2C_CR2_OFFSET)
#define I2C_TIMINGR REG32(I2C_BASE + I2C_TIMINGR_OFFSET)
#define I2C_ISR REG32(I2C_BASE + I2C_ISR_OFFSET)
#define I2C_TXDR REG32(I2C_BASE + I2C_TXDR_OFFSET)
#define I2C_ICR REG32(I2C_BASE + I2C_ICR_OFFSET)
#define I2C_RXDR REG32(I2C_BASE + I2C_RXDR_OFFSET)

#define I2C_SCL GPIOA_BASE, 15
#define I2C_SDA GPIOB_BASE, 7

#define I2C_ANFILTER_ENABLED 0  // Analog noise filter enabled
#define I2C_ANFILTER_DISABLED 1 // Analog noise filter disabled

#define I2C_DNF_DISBLED 0
#define I2C_DNF_ENABLED1 1
#define I2C_DNF_ENABLED2 2
#define I2C_DNF_ENABLED3 3
#define I2C_DNF_ENABLED4 4
#define I2C_DNF_ENABLED5 5
#define I2C_DNF_ENABLED6 6
#define I2C_DNF_ENABLED7 7
#define I2C_DNF_ENABLED8 8
#define I2C_DNF_ENABLED9 9
#define I2C_DNF_ENABLED10 10
#define I2C_DNF_ENABLED11 11
#define I2C_DNF_ENABLED12 12
#define I2C_DNF_ENABLED13 13
#define I2C_DNF_ENABLED14 14
#define I2C_DNF_ENABLED15 15

#define I2C_STRETCHING_ENABLED 0
#define I2C_STRETCHING_DISABLED 1

void I2C_Initialize();
void I2C_SendData();
void I2C_GetData();

// Hilfefunktionen
// Initialize()
void I2C_RCC_Enable();
void I2C_CR1_ClearPE();
void I2C_ConfigANFOFF(int state);
void I2C_ConfigDNF(int state);
void I2C_TIMINGR_Config();
void I2C_NOSTRETCH_Config(int state);
void I2C_CR1_SetPE();

void I2C_ConfigSlaveAddress();

// SendData()
void I2C_MasterSendInit();
int I2C_ISR_isNACKF();
int I2C_ISR_isTXIS();
void I2C_TXDR_Write(int data);
int I2C_isNBYTESTransmitted();

// SendData()
void I2C_MasterGetInit();
int I2C_ISR_isRXNE();
void I2C1_EV_IRQHandler();

#endif