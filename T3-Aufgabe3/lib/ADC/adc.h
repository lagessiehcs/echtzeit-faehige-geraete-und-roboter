#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <gpio.h>
#include <Delay_ms.h>

#define ADC12_BASE 0x50000000

// Offset
#define ADC_CR_OFFSET 0x08
#define ADC_SQR1_OFFSET 0x30
#define ADC_CFGR_OFFSET 0x0C
#define ADC_ISR_OFFSET 0x00
#define ADC_DR_OFFSET 0x40

// Register-Zugriff
#define REG32(addr) (*(volatile uint32_t *)(addr))

#define ADC_CR REG32(ADC12_BASE + ADC_CR_OFFSET)
#define ADC_SQR1 REG32(ADC12_BASE + ADC_SQR1_OFFSET)
#define ADC_CFGR REG32(ADC12_BASE + ADC_CFGR_OFFSET)
#define ADC_ISR REG32(ADC12_BASE + ADC_ISR_OFFSET)
#define ADC_DR REG32(ADC12_BASE + ADC_DR_OFFSET)

// Modes
#define ADC_CFGR_SINGLECONVERSION 0
#define ADC_CFGR_CONTINUOUSCONVERSION 1

void ADC_Config_Poti(uint32_t port, uint8_t pin);

void ADC_RCC_Enable();
void ADC_RCC_CCIPR_IndependentClockConfig();
void ADC_DisableDeepDown();
void ADC_DisableADC();
void ADC_SQR1_SetSequenceLength(int L);
void ADC_SQR1_SetSequence(int chanel, int sequence_nr);
void ADC_SetSingleEndedMode();
void ADC_SetConversionMode(int mode);
void ADC_Calibrate();
void ADC_StartConversion();
int ADC_ReadData();
void ADC_DeleteEOS();
int ADC_GetValue();
void ADC_EnableVoltageRegulator();
void ADC_StartADC();
#endif
