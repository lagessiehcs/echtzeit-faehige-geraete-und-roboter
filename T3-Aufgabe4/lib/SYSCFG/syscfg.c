#include <syscfg.h>

void SYSCFG_Config(uint32_t port, uint8_t pin)
{
    SYSCFG_Enable();
    SYSCFG_SetEXTISourceInput(port, pin);
}

void SYSCFG_SetEXTISourceInput(uint32_t port, uint8_t pin)
{
    int exti_pin_position = pin % 4;
    SYSCFG_EXTICR(pin) &= ~(0xF << (exti_pin_position * 4));              // Lösche die bestehenden Bits
    SYSCFG_EXTICR(pin) |= (SYSCFG_EXTI(port) << (exti_pin_position * 4)); // Setze den neuen Port
}

void SYSCFG_Enable()
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x60);
    *adresse |= (1 << 0);
}