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

#define SERVO GPIOA_BASE, 12

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define BUTTON3_PIN 4

#define BUTTON1 GPIOA_BASE, BUTTON1_PIN
#define BUTTON2 GPIOA_BASE, BUTTON2_PIN
#define BUTTON3 GPIOA_BASE, BUTTON3_PIN

int compare = 100000 - 1; // compare value

void TIM2_IRQHandler(void)
{

    if ((TIM_SR(TIM2_BASE)) & (0x01))
    {
        GPIO_Write(SERVO, 1);
    }
    else if ((TIM_SR(TIM2_BASE)) & (0x10))
    {
        GPIO_Write(SERVO, 0);
    }

    // Löschen des Interrupt-Flags
    TIM_SR(TIM2_BASE) &= ~(1 << 0x0);
    TIM_SR(TIM2_BASE) &= ~(1 << 0x1);
}

int is_button_pushed(uint32_t port, uint8_t pin);

int main(void)
{
    int f_req = 50000; // Zähl-Frequenz
    int arr = 1000;    // Auto-Reload

    // Blue LED Config
    GPIO_OutputInit(SERVO, GPIO_OTYPE_PP);

    // Button config
    GPIO_InputInit(BUTTON1, GPIO_PU);
    GPIO_InputInit(BUTTON2, GPIO_PU);
    GPIO_InputInit(BUTTON3, GPIO_PU);

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
    TIM_StartUpdateEvent(TIM2_BASE);

    while (1)
    {
        // place your loop code here
        if (is_button_pushed(BUTTON1))
        {
            compare = 125;
        }
        else if (is_button_pushed(BUTTON3))
        {
            compare = 25;
        }
        else if (is_button_pushed(BUTTON2))
        {
            compare = 75;
        }

        TIM_SetCompareValue(TIM2_BASE, compare);
    }

    return 0;
}
int is_button_pushed(uint32_t port, uint8_t pin)
{
    return GPIO_Read(port, pin);
}