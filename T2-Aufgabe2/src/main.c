/**
 * EGR Praktikum
 * Termin 2 - Aufgabe 2
 */

#include <stdint.h>
#include <gpio.h>
#include <syscfg.h>
#include <exti.h>
#include <Delay_ms.h>
#include "stm32g431xx.h"
#include <tim.h>

#define LED_BLUE GPIOA_BASE, 8

void TIM2_IRQHandler(void)
{
    // int volatile a = TIM_SR_UIF_VALUE(TIM2_BASE) & 0x01;
    // int volatile b = TIM_SR_CC1IF_VALUE(TIM2_BASE) & 0x01;
    if ((TIM_SR(TIM2_BASE)) & (0x01))
    {
        GPIO_Write(LED_BLUE, 1);
        // Löschen des Interrupt-Flags
    }
    else if ((TIM_SR(TIM2_BASE)) & (0x10))
    {
        GPIO_Write(LED_BLUE, 0);
        // Löschen des Interrupt-Flags
    }

    TIM_SR(TIM2_BASE) &= ~(1 << 0x0);
    TIM_SR(TIM2_BASE) &= ~(1 << 0x1);
}

int main(void)
{
    int f_req = 1000;  // Zähl-Frequenz
    int arr = 1000;    // Auto-Reload
    int compare = 500; // compare value

    // Blue LED Config
    GPIO_OutputInit(LED_BLUE, GPIO_OTYPE_PP);

    // Timer Config
    TIM_Enable(); // Timer aktivieren
    TIM_SetPrescaler(TIM2_BASE, f_req);
    TIM_SetAutoReload(TIM2_BASE, arr);
    TIM_SetCompareValue(TIM2_BASE, compare);
    TIM_ConfigCompareMode(TIM2_BASE);
    TIM_EnableInterrupt(TIM2_BASE);

    // Priorität festlegen
    NVIC_SetPriority(TIM2_IRQn, 2);
    // Interrupt aktivieren
    NVIC_EnableIRQ(TIM2_IRQn);

    TIM_GenerateUpdateEvent(TIM2_BASE);
    TIM_DeleteUpdateEvent(TIM2_BASE);
    TIM_StartUpdateEvent(TIM2_BASE);

    while (1)
    {
        // place your loop code here
    }

    return 0;
}