#include "gpio.h"
void GPIO_Init_Input(uint32_t port, uint8_t pin, uint8_t pupd)
{
    GPIO_Set_Mode(port, pin, GPIO_MODE_INPUT);
    GPIO_Set_Pull_Up_Pull_Down(port, pin, pupd);
}
void GPIO_Init_Output(uint32_t port, uint8_t pin, uint8_t type)
{
    GPIO_Set_Mode(port, pin, GPIO_MODE_OUTPUT);
    GPIO_Set_Output_Type(port, pin, type);
}
void GPIO_Set_Mode(uint32_t port, uint8_t pin, uint8_t mode)
{
    GPIO_MODER(port) &= ~(0x3 << (pin * 2)); // Lösche die bestehenden Bits
    GPIO_MODER(port) |= (mode << (pin * 2)); // Setze den neuen Modus
}

void GPIO_Set_Output_Type(uint32_t port, uint8_t pin, uint8_t type)
{
    GPIO_OTYPER(port) &= ~(0x1 << pin); // Lösche das bestehende Bit
    GPIO_OTYPER(port) |= (type << pin); // Setze den neuen Typ
}

void GPIO_Set_Speed(uint32_t port, uint8_t pin, uint8_t speed)
{
    GPIO_OSPEEDR(port) &= ~(0x3 << (pin * 2));  // Lösche die bestehenden Bits
    GPIO_OSPEEDR(port) |= (speed << (pin * 2)); // Setze die neue Geschwindigkeit
}

void GPIO_Set_Pull_Up_Pull_Down(uint32_t port, uint8_t pin, uint8_t pupd)
{
    GPIO_PUPDR(port) &= ~(0x3 << (pin * 2)); // Lösche die bestehenden Bits
    GPIO_PUPDR(port) |= (pupd << (pin * 2)); // Setze die neue Pull-Up/Pull-Down Konfiguration
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
    return (GPIO_IDR(port) & (1 << pin)) ? 1 : 0; // Lese den Pin-Zustand
}

void GPIO_Toggle(uint32_t port, uint8_t pin)
{
    GPIO_ODR(port) ^= (1 << pin); // Togglen des Pin-Zustands
}
