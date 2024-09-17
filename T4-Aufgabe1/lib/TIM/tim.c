#include <tim.h>

void TIM_Enable()
{
    TIM_EnableTimer2();
    TIM_EnableTimer3();
    TIM_EnableTimer4();
}
void TIM_EnableTimer2()
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x58);
    *adresse |= (1 << 0x0);
}
void TIM_EnableTimer3()
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x58);
    *adresse |= (1 << 0x1);
}
void TIM_EnableTimer4()
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x58);
    *adresse |= (1 << 0x2);
}

void TIM_SetPrescaler(uint32_t timer_base, int f_req) // Für Timer 2 bis 5
{
    TIM_PSC(timer_base) = (F_SYS / f_req) - 1;
}

void TIM_SetAutoReload(uint32_t timer_base, int ar) // Für Timer 2 bis 5
{
    TIM_ARR(timer_base) = ar;
}

void TIM_EnableCaptureCompare(uint32_t timer_base)
{
    TIM_CCER(timer_base) |= (1 << 0x0);
    TIM_CCER(timer_base) |= (1 << 0x4);
}

void TIM_SetCompare1Value(uint32_t timer_base, int compare)
{
    TIM_CCR1(timer_base) = compare;
}
void TIM_SetCompare2Value(uint32_t timer_base, int compare)
{
    TIM_CCR2(timer_base) = compare;
}
void TIM_EnableInterrupt(uint32_t timer_base)
{
    TIM_EnableUpdateInterrupt(timer_base);
    TIM_EnableCompare1Interrupt(timer_base);
    TIM_EnableCompare2Interrupt(timer_base);
}

void TIM_EnableUpdateInterrupt(uint32_t timer_base) // Für Timer 2 bis 5
{
    TIM_DIER(timer_base) |= (1 << 0x0);
}
void TIM_EnableCompare1Interrupt(uint32_t timer_base)
{
    TIM_DIER(timer_base) |= (1 << 0x1);
}
void TIM_EnableCompare2Interrupt(uint32_t timer_base)
{
    TIM_DIER(timer_base) |= (1 << 0x2);
}

void TIM_SetPWM(uint32_t timer_base)
{
    // Chanel 1
    TIM_CCMR1(timer_base) |= (0b110 << 4);
    TIM_CCMR1(timer_base) |= (0 << 16);

    // Chanel 2
    TIM_CCMR1(timer_base) |= (0b110 << 12);
    TIM_CCMR1(timer_base) |= (0 << 24);
}
void TIM_SetPreload(uint32_t timer_base)
{
    TIM_CCMR1(timer_base) |= (1 << 3);  // Preload Chanel 1
    TIM_CCMR1(timer_base) |= (1 << 11); // Preload Chanel 2
}

void TIM_GenerateUpdateEvent(uint32_t timer_base) // Für Timer 2 bis 5
{
    TIM_EGR(timer_base) |= (1 << 0x0);
    TIM_EGR(timer_base) |= (1 << 0x1);
    TIM_EGR(timer_base) |= (1 << 0x2);
}

void TIM_DeleteUpdateEvent(uint32_t timer_base)
{
    TIM_SR(timer_base) &= ~(1 << 0x0);
}

void TIM_StartUpdateEvent(uint32_t timer_base)
{
    TIM_CR1(timer_base) |= (1 << 0x0);
}