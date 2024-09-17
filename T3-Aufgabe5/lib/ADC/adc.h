#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <gpio.h>
#include <Delay_ms.h>

#define ADC12_BASE 0x50000000
#define ADC2_BASE 0x50000100

// Offset
#define ADC_CR_OFFSET 0x08
#define ADC_SQR1_OFFSET 0x30
#define ADC_CFGR_OFFSET 0x0C
#define ADC_ISR_OFFSET 0x00
#define ADC_DR_OFFSET 0x40

// Register-Zugriff
#define REG32(addr) (*(volatile uint32_t *)(addr))

#define ADC_CR REG32(ADC2_BASE + ADC_CR_OFFSET)
#define ADC_SQR1 REG32(ADC2_BASE + ADC_SQR1_OFFSET)
#define ADC_CFGR REG32(ADC2_BASE + ADC_CFGR_OFFSET)
#define ADC_ISR REG32(ADC2_BASE + ADC_ISR_OFFSET)
#define ADC_DR REG32(ADC2_BASE + ADC_DR_OFFSET)

// #define ADC_CR REG32(ADC12_BASE + ADC_CR_OFFSET)
// #define ADC_SQR1 REG32(ADC12_BASE + ADC_SQR1_OFFSET)
// #define ADC_CFGR REG32(ADC12_BASE + ADC_CFGR_OFFSET)
// #define ADC_ISR REG32(ADC12_BASE + ADC_ISR_OFFSET)
// #define ADC_DR REG32(ADC12_BASE + ADC_DR_OFFSET)

// Modes
#define ADC_CFGR_SINGLECONVERSION 0
#define ADC_CFGR_CONTINUOUSCONVERSION 1

typedef struct
{
    int hell1;
    int hell2;
    int hell3;
} HELL;

void ADC_Config_Poti(uint32_t port, uint8_t pin);
void ADC_Config_Hell(uint32_t port1, uint8_t pin1, uint32_t port2, uint8_t pin2, uint32_t port3, uint8_t pin3);

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
int ADC_GetValue_Poti();
// HELL ADC_GetValue_Hell();
int *ADC_GetValue_Hell();
void ADC_EnableVoltageRegulator();
void ADC_StartADC();
#endif
