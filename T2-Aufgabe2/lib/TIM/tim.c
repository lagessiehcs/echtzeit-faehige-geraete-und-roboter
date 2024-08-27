#include <tim.h>

void TIM_Enable()
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x58 + 0x0);
    *adresse |= (1 << 0);
}

void TIM_SetPrescaler(uint32_t timer_base, int f_req) // Für Timer 2 bis 5
{
    TIM_PSC(timer_base) = (F_SYS / f_req) - 1;
}

void TIM_SetAutoReload(uint32_t timer_base, int arr) // Für Timer 2 bis 5
{
    TIM_ARR(timer_base) = arr;
}

void TIM_ConfigCompareMode(uint32_t timer_base)
{
    TIM_CCER(timer_base) |= (1 << 0x0);
}

void TIM_SetCompareValue(uint32_t timer_base, int compare)
{
    TIM_CCR1(timer_base) = compare;
}
void TIM_EnableInterrupt(uint32_t timer_base)
{
    TIM_EnableUpdateInterrupt(timer_base);
    TIM_EnableCompare1Interrupt(timer_base);
}

void TIM_EnableUpdateInterrupt(uint32_t timer_base) // Für Timer 2 bis 5
{
    TIM_DIER(timer_base) |= (1 << 0x0);
}
void TIM_EnableCompare1Interrupt(uint32_t timer_base) // Für Timer 2 bis 5
{
    TIM_DIER(timer_base) |= (1 << 0x1);
}

void TIM_GenerateUpdateEvent(uint32_t timer_base) // Für Timer 2 bis 5
{
    TIM_EGR(timer_base) |= (1 << 0x0);
}

void TIM_DeleteUpdateEvent(uint32_t timer_base)
{
    TIM_SR(timer_base) &= ~(1 << 0x0);
}

void TIM_StartUpdateEvent(uint32_t timer_base)
{
    TIM_CR1(timer_base) |= (1 << 0x0);
}