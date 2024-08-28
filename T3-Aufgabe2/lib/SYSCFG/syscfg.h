#ifndef SYSCFG_H
#define SYSCFG_H

#include <stdint.h>
#include <gpio.h>

// Basisadressen für SYSCFG
#define SYSCFG_BASE 0x40010000

// Register-Offsets
#define SYSCFG_EXTICR_OFFSET(pin) (0x08 + (4 * (pin / 4)))

// Register-Zugriff
#define REG32(addr) (*(volatile uint32_t *)(addr))

// Makros zur Berechnung von Registeradressen
#define SYSCFG_EXTICR(pin) REG32(SYSCFG_BASE + SYSCFG_EXTICR_OFFSET(pin))

// EXTI
#define SYSCFG_EXTI(port) ((port - GPIOA_BASE) / (0x400))

void SYSCFG_Config(uint32_t port, uint8_t pin);
void SYSCFG_SetEXTISourceInput(uint32_t port, uint8_t pin);
void SYSCFG_Enable();

#endif