#ifndef EXTI_H
#define EXTI_H

#include <stdint.h>

// Basisadressen für EXTI
#define EXTI_BASE 0x40010400

// Register-Offsets
#define EXTI_IMR1_OFFSET 0x00
#define EXTI_EMR1_OFFSET 0x04
#define EXTI_RTSR1_OFFSET 0x08
#define EXTI_FTSR1_OFFSET 0x0C
#define EXTI_SWIER1_OFFSET 0x10
#define EXTI_PR1_OFFSET 0x14

#define EXTI_IMR2_OFFSET 0x20
#define EXTI_EMR2_OFFSET 0x24
#define EXTI_RTSR2_OFFSET 0x28
#define EXTI_FTSR2_OFFSET 0x2C
#define EXTI_SWIER2_OFFSET 0x30
#define EXTI_PR2_OFFSET 0x34

// Register-Zugriff
#define REG32(addr) (*(volatile uint32_t *)(addr))

// Makros zur Berechnung von Registeradressen
#define EXTI_IMR1 REG32(EXTI_BASE + EXTI_IMR1_OFFSET)
#define EXTI_EMR1 REG32(EXTI_BASE + EXTI_EMR1_OFFSET)
#define EXTI_RTSR1 REG32(EXTI_BASE + EXTI_RTSR1_OFFSET)
#define EXTI_FTSR1 REG32(EXTI_BASE + EXTI_FTSR1_OFFSET)
#define EXTI_SWIER1 REG32(EXTI_BASE + EXTI_SWIER1_OFFSET)
#define EXTI_PR1 REG32(EXTI_BASE + EXTI_PR1_OFFSET)

#define EXTI_IMR2 REG32(EXTI_BASE + EXTI_IMR2_OFFSET)
#define EXTI_EMR2 REG32(EXTI_BASE + EXTI_EMR2_OFFSET)
#define EXTI_RTSR2 REG32(EXTI_BASE + EXTI_RTSR2_OFFSET)
#define EXTI_FTSR2 REG32(EXTI_BASE + EXTI_FTSR2_OFFSET)
#define EXTI_SWIER2 REG32(EXTI_BASE + EXTI_SWIER2_OFFSET)
#define EXTI_PR2 REG32(EXTI_BASE + EXTI_PR2_OFFSET)

// Interrupt-Masks
#define EXTI_IM_MASKED 0x0
#define EXTI_IM_NOT_MASKED 0x1

// Event-Masks
#define EXTI_EM_MASKED 0x0
#define EXTI_EM_NOT_MASKED 0x1

// Rising trigger event configuration
#define EXTI_RT_RISING_DISABLED 0x0
#define EXTI_RT_RISING_ENABLE 0x1

// Falling trigger event configuration
#define EXTI_FT_FALLING_DISABLED 0x0
#define EXTI_FT_FALLING_ENABLE 0x1

// Software Interrupt
#define EXTI_SWIER_NOT_CLEARED 0x0
#define EXTI_SWIER_CLEARED 0x1

// Pending interrupt flag
#define EXTI_PIF_NO_TRIGGER_REQUEST_OCCURED 0x0
#define EXTI_PIF_TRIGGER_REQUEST_OCCURED 0x1

void EXTI_Config(uint8_t pin, uint8_t im, uint8_t rt, uint8_t ft);
void EXTI_SetInterruptMask(uint8_t pin, uint8_t im);
void EXTI_SetEventMask(uint8_t pin, uint8_t em);
void EXTI_SetRisingTriggerEvent(uint8_t pin, uint8_t rt);
void EXTI_SetFallingTriggerEvent(uint8_t pin, uint8_t ft);
void EXTI_SetSoftwareInteruptEventPending(uint8_t pin);

#endif