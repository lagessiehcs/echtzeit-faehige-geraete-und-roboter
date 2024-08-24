#include "gpio.h"

void GPIO_SetPinMode(uint32_t port, uint8_t pin, uint8_t mode) {
    GPIO_MODER(port) &= ~(0x3 << (pin * 2)); // Lösche die bestehenden Bits
    GPIO_MODER(port) |= (mode << (pin * 2)); // Setze den neuen Modus
}

void GPIO_SetPinOutputType(uint32_t port, uint8_t pin, uint8_t type) {
    GPIO_OTYPER(port) &= ~(0x1 << pin); // Lösche das bestehende Bit
    GPIO_OTYPER(port) |= (type << pin); // Setze den neuen Typ
}

void GPIO_SetPinSpeed(uint32_t port, uint8_t pin, uint8_t speed) {
    GPIO_OSPEEDR(port) &= ~(0x3 << (pin * 2)); // Lösche die bestehenden Bits
    GPIO_OSPEEDR(port) |= (speed << (pin * 2)); // Setze die neue Geschwindigkeit
}

void GPIO_SetPinPullUpPullDown(uint32_t port, uint8_t pin, uint8_t pupd) {
    GPIO_PUPDR(port) &= ~(0x3 << (pin * 2)); // Lösche die bestehenden Bits
    GPIO_PUPDR(port) |= (pupd << (pin * 2)); // Setze die neue Pull-Up/Pull-Down Konfiguration
}

void GPIO_WritePin(uint32_t port, uint8_t pin, uint8_t state) {
    if (state) {
        GPIO_BSRR(port) = (1 << pin); // Setze den Pin
    } else {
        GPIO_BRR(port) = (1 << pin); // Lösche den Pin
    }
}

uint8_t GPIO_ReadPin(uint32_t port, uint8_t pin) {
    return (GPIO_IDR(port) & (1 << pin)) ? 1 : 0; // Lese den Pin-Zustand
}

void GPIO_TogglePin(uint32_t port, uint8_t pin) {
    GPIO_ODR(port) ^= (1 << pin); // Togglen des Pin-Zustands
}
