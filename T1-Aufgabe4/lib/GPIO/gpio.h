#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// Basisadressen für GPIO-Ports
#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800
#define GPIOD_BASE 0x48000C00
#define GPIOE_BASE 0x48001000
#define GPIOF_BASE 0x48001400

// Register-Offsets
#define GPIO_MODER_OFFSET 0x00
#define GPIO_OTYPER_OFFSET 0x04
#define GPIO_OSPEEDR_OFFSET 0x08
#define GPIO_PUPDR_OFFSET 0x0C
#define GPIO_IDR_OFFSET 0x10
#define GPIO_ODR_OFFSET 0x14
#define GPIO_BSRR_OFFSET 0x18
#define GPIO_LCKR_OFFSET 0x1C
#define GPIO_AFRL_OFFSET 0x20
#define GPIO_AFRH_OFFSET 0x24
#define GPIO_BRR_OFFSET 0x28

// Register-Zugriff
#define REG32(addr) (*(volatile uint32_t *)(addr))

// Makros zur Berechnung von Registeradressen
#define GPIO_MODER(port) REG32((port) + GPIO_MODER_OFFSET)
#define GPIO_OTYPER(port) REG32((port) + GPIO_OTYPER_OFFSET)
#define GPIO_OSPEEDR(port) REG32((port) + GPIO_OSPEEDR_OFFSET)
#define GPIO_PUPDR(port) REG32((port) + GPIO_PUPDR_OFFSET)
#define GPIO_IDR(port) REG32((port) + GPIO_IDR_OFFSET)
#define GPIO_ODR(port) REG32((port) + GPIO_ODR_OFFSET)
#define GPIO_BSRR(port) REG32((port) + GPIO_BSRR_OFFSET)
#define GPIO_LCKR(port) REG32((port) + GPIO_LCKR_OFFSET)
#define GPIO_AFRL(port) REG32((port) + GPIO_AFRL_OFFSET)
#define GPIO_AFRH(port) REG32((port) + GPIO_AFRH_OFFSET)
#define GPIO_BRR(port) REG32((port) + GPIO_BRR_OFFSET)

// GPIO-Modi
#define GPIO_MODE_INPUT 0x00
#define GPIO_MODE_OUTPUT 0x01
#define GPIO_MODE_AF 0x02
#define GPIO_MODE_ANALOG 0x03

// Output-Typen
#define GPIO_OTYPE_PP 0x00
#define GPIO_OTYPE_OD 0x01

// Geschwindigkeiten
#define GPIO_SPEED_LOW 0x00
#define GPIO_SPEED_MEDIUM 0x01
#define GPIO_SPEED_HIGH 0x02
#define GPIO_SPEED_VERYHIGH 0x03

// Pull-Up/Pull-Down Konfigurationen
#define GPIO_NO_PUPD 0x00
#define GPIO_PU 0x01
#define GPIO_PD 0x02
#define GPIO_RESERVED 0x03

// Funktionen
void GPIO_InitInput(uint32_t port, uint8_t pin, uint8_t pupd);
void GPIO_InitOutput(uint32_t port, uint8_t pin, uint8_t type);
void GPIO_SetPinMode(uint32_t port, uint8_t pin, uint8_t mode);
void GPIO_SetPinOutputType(uint32_t port, uint8_t pin, uint8_t type);
void GPIO_SetPinSpeed(uint32_t port, uint8_t pin, uint8_t speed);
void GPIO_SetPinPullUpPullDown(uint32_t port, uint8_t pin, uint8_t pupd);
void GPIO_WritePin(uint32_t port, uint8_t pin, uint8_t state);
uint8_t GPIO_ReadPin(uint32_t port, uint8_t pin);
void GPIO_TogglePin(uint32_t port, uint8_t pin);

#endif // GPIO_H
