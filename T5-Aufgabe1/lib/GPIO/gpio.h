#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

// Basisadressen für GPIO-Ports
#define GPIO_BASE 0x48000000

#define GPIOA_BASE 0x48000000
#define GPIOB_BASE 0x48000400
#define GPIOC_BASE 0x48000800
#define GPIOD_BASE 0x48000C00
#define GPIOE_BASE 0x48001000
#define GPIOF_BASE 0x48001400
#define GPIOG_BASE 0x48001800

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
#define GPIO_AFRL_OFFSET 0x20
#define GPIO_AFRH_OFFSET 0x24

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
#define GPIO_AFRL(port) REG32((port) + GPIO_AFRL_OFFSET)
#define GPIO_AFRH(port) REG32((port) + GPIO_AFRH_OFFSET)

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

// Alternative Funktions Werte
// #define AF0 0
// #define AF1 1
// #define AF2 2
// #define AF3 3
// #define AF4 4
// #define AF5 5
// #define AF6 6
// #define AF7 7
// #define AF8 8
// #define AF9 9
// #define AF10 10
// #define AF11 11
// #define AF12 12
// #define AF13 13
// #define AF14 14
// #define AF15 15

// Funktionen
void GPIO_InputInit(uint32_t port, uint8_t pin, uint8_t pupd);
void GPIO_OutputInit(uint32_t port, uint8_t pin, uint8_t type);
void GPIO_AlternativeInit(uint32_t port, uint8_t pin, uint8_t afsel);
void GPIO_AnalogInit(uint32_t port, uint8_t pin);
void GPIO_Enable(uint32_t port);
void GPIO_SetMode(uint32_t port, uint8_t pin, uint8_t mode);
void GPIO_SetOutputType(uint32_t port, uint8_t pin, uint8_t type);
void GPIO_SetSpeed(uint32_t port, uint8_t pin, uint8_t speed);
void GPIO_SetPullUpPullDown(uint32_t port, uint8_t pin, uint8_t pupd);
void GPIO_Write(uint32_t port, uint8_t pin, uint8_t state);
void GPIO_SetAlternativeLow(uint32_t port, uint8_t pin, uint8_t afsel);
void GPIO_SetAlternativeHigh(uint32_t port, uint8_t pin, uint8_t afsel);
uint8_t GPIO_Read(uint32_t port, uint8_t pin);
void GPIO_Toggle(uint32_t port, uint8_t pin);

#endif // GPIO_H
