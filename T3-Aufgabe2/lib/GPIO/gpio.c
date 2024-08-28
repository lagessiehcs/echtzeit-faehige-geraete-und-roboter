#include "gpio.h"

void GPIO_InputInit(uint32_t port, uint8_t pin, uint8_t pupd)
{
    GPIO_Enable(port);
    GPIO_SetMode(port, pin, GPIO_MODE_INPUT);
    GPIO_SetPullUpPullDown(port, pin, pupd);
}

void GPIO_OutputInit(uint32_t port, uint8_t pin, uint8_t type)
{
    GPIO_Enable(port);
    GPIO_SetMode(port, pin, GPIO_MODE_OUTPUT);
    GPIO_SetOutputType(port, pin, type);
}

void GPIO_Enable(uint32_t port)
{
    // Aktivierung des GPIOx Moduls (x = A...G)
    int port_offset = (port - GPIO_BASE) / (0x400);
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x4C);
    *adresse |= (1 << port_offset);
}

void GPIO_SetMode(uint32_t port, uint8_t pin, uint8_t mode)
{
    GPIO_MODER(port) &= ~(0x3 << (pin * 2)); // Lösche die bestehenden Bits
    GPIO_MODER(port) |= (mode << (pin * 2)); // Setze den neuen Modus
}

void GPIO_SetOutputType(uint32_t port, uint8_t pin, uint8_t type)
{
    GPIO_OTYPER(port) &= ~(0x1 << pin); // Lösche das bestehende Bit
    GPIO_OTYPER(port) |= (type << pin); // Setze den neuen Typ
}

void GPIO_SetSpeed(uint32_t port, uint8_t pin, uint8_t speed)
{
    GPIO_OSPEEDR(port) &= ~(0x3 << (pin * 2));  // Lösche die bestehenden Bits
    GPIO_OSPEEDR(port) |= (speed << (pin * 2)); // Setze die neue Geschwindigkeit
}

void GPIO_SetPullUpPullDown(uint32_t port, uint8_t pin, uint8_t pupd)
{
    GPIO_PUPDR(port) &= ~(0x3 << (pin * 2)); // Lösche die bestehenden Bits
    GPIO_PUPDR(port) |= (pupd << (pin * 2)); // Setze die neue Pull-Up/Pull-Down Konfiguration
}

void GPIO_AlternativeInit(uint32_t port, uint8_t pin, uint8_t afsel)
{
    GPIO_Enable(port);
    GPIO_SetMode(port, pin, GPIO_MODE_AF);

    if (pin <= 7)
    {
        GPIO_SetAlternativeLow(port, pin, afsel);
    }
    else if (pin >= 8)
    {
        GPIO_SetAlternativeHigh(port, pin, afsel);
    }
}

void GPIO_SetAlternativeLow(uint32_t port, uint8_t pin, uint8_t afsel)
{
    GPIO_AFRL(port) &= ~(0b1111 << (4 * pin));
    GPIO_AFRL(port) |= (afsel << (4 * pin));
}
void GPIO_SetAlternativeHigh(uint32_t port, uint8_t pin, uint8_t afsel)
{
    GPIO_AFRH(port) &= ~(0b1111 << (4 * (pin - 8)));
    GPIO_AFRH(port) |= (afsel << (4 * (pin - 8)));
}

void GPIO_Write(uint32_t port, uint8_t pin, uint8_t state)
{
    if (state)
    {
        GPIO_BSRR(port) = (1 << pin); // Setze den Pin
    }
    else
    {
        GPIO_BRR(port) = (1 << pin); // Lösche den Pin
    }
}

uint8_t GPIO_Read(uint32_t port, uint8_t pin)
{
    int state = (GPIO_IDR(port) & (1 << pin)); // Lese den Pin-Zustand
    if (state)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void GPIO_Toggle(uint32_t port, uint8_t pin)
{
    GPIO_ODR(port) ^= (1 << pin); // Togglen des Pin-Zustands
}
