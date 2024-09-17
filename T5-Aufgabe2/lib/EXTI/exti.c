#include "exti.h"

void EXTI_Config(uint8_t pin, uint8_t im, uint8_t rt, uint8_t ft)
{
    EXTI_SetInterruptMask(pin, im);
    EXTI_SetRisingTriggerEvent(pin, rt);
    EXTI_SetFallingTriggerEvent(pin, ft);
}

void EXTI_SetInterruptMask(uint8_t pin, uint8_t im)
{
    uint32_t volatile *imr = 0;
    int offset = 0;

    if (pin >= 0 && pin <= 31)
    {
        imr = &EXTI_IMR1;
        offset = pin;
    }
    else if (pin >= 32 && pin <= 43)
    {
        imr = &EXTI_IMR2;
        offset = 32 - pin;
    }

    if (im)
    {
        *imr |= (1 << offset); // Setze den neuen Modus
    }
    else
    {
        *imr &= ~(1 << offset); // Lösche den Pin
    }
}

void EXTI_SetEventMask(uint8_t pin, uint8_t em)
{
    uint32_t volatile *emr = 0;
    int offset = 0;

    if (pin >= 0 && pin <= 31)
    {
        emr = &EXTI_EMR1;
        offset = pin;
    }
    else if (pin >= 32 && pin <= 43)
    {
        emr = &EXTI_EMR2;
        offset = 32 - pin;
    }

    if (em)
    {
        *emr |= (1 << offset); // Setze den neuen Modus
    }
    else
    {
        *emr &= ~(1 << offset); // Lösche den Pin
    }
}

void EXTI_SetRisingTriggerEvent(uint8_t pin, uint8_t rt)
{
    uint32_t volatile *rtsr = 0;
    int offset = 0;

    if (pin >= 0 && pin <= 31)
    {
        rtsr = &EXTI_RTSR1;
        offset = pin;
    }
    else if (pin >= 32 && pin <= 41)
    {
        rtsr = &EXTI_RTSR2;
        offset = 32 - pin;
    }
    if (rt)
    {
        *rtsr |= (1 << offset); // Setze den neuen Modus
    }
    else
    {
        *rtsr &= ~(1 << offset); // Lösche den Pin
    }
}

void EXTI_SetFallingTriggerEvent(uint8_t pin, uint8_t ft)
{
    uint32_t volatile *ftsr = 0;
    int offset = 0;

    if (pin >= 0 && pin <= 31)
    {
        ftsr = &EXTI_FTSR1;
        offset = pin;
    }
    else if (pin >= 32 && pin <= 41)
    {
        ftsr = &EXTI_FTSR2;
        offset = 32 - pin;
    }
    if (ft)
    {
        *ftsr |= (1 << offset); // Setze den neuen Modus
    }
    else
    {
        *ftsr &= ~(1 << offset); // Lösche den Pin
    }
}
void EXTI_SetSoftwareInteruptEventPending(uint8_t pin)
{
    uint32_t volatile *imr = 0;
    uint32_t volatile *pr = 0;
    uint32_t volatile *swier = 0;
    int offset = 0;

    if (pin >= 0 && pin <= 31)
    {
        imr = (uint32_t *)EXTI_IMR1;
        pr = (uint32_t *)EXTI_PR1;
        swier = (uint32_t *)EXTI_SWIER1;
        offset = pin;
    }
    else if (pin >= 32 && pin <= 43)
    {
        imr = &EXTI_IMR2;
        pr = &EXTI_PR2;
        swier = &EXTI_SWIER2;
        offset = 32 - pin;
    }

    int line_state = (*imr & (1 << offset));

    if (line_state)
    {
        *swier |= (1 << offset); // Setze den neuen Modus
    }
    else
    {
        *pr |= (1 << offset); // Setze den neuen Modus
    }
}