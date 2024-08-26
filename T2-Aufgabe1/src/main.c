/**
 * EGR Praktikum
 * Termin 1 - Aufgabe 4
 */

#include <stdint.h>
#include <gpio.h>
#include <syscfg.h>
#include <exti.h>
#include <Delay_ms.h>
#include "stm32g431xx.h"

#define BLUE 1
#define RED 2
#define GREEN 3

#define LED_BLUE GPIOA_BASE, 8
#define LED_RED GPIOA_BASE, 9
#define LED_GREEN GPIOA_BASE, 10

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define BUTTON3_PIN 4

#define BUTTON1 GPIOA_BASE, BUTTON1_PIN
#define BUTTON2 GPIOA_BASE, BUTTON2_PIN
#define BUTTON3 GPIOA_BASE, BUTTON3_PIN

uint32_t milliseconds = 500;
int color_change_on = 1;
int current_color = 0;

void turn_off_LED();
void change_color_LED();
int is_button_pushed(uint32_t port, uint8_t pin);

void EXTI4_IRQHandler(void)
{
    color_change_on = 0;
    turn_off_LED();

    // Löschen des Interrupt-Flags
    uint32_t volatile *adresse = (uint32_t *)(EXTI_BASE + EXTI_PR1_OFFSET);
    *adresse |= (1 << BUTTON3_PIN);
}

int main(void)
{
    // place code to run once here
    GPIO_OutputInit(LED_BLUE, GPIO_OTYPE_PP);
    GPIO_OutputInit(LED_RED, GPIO_OTYPE_PP);
    GPIO_OutputInit(LED_GREEN, GPIO_OTYPE_PP);

    GPIO_InputInit(BUTTON1, GPIO_PU);
    GPIO_InputInit(BUTTON2, GPIO_PU);
    GPIO_InputInit(BUTTON3, GPIO_PU);

    SYSCFG_Config(BUTTON3);
    EXTI_Config(BUTTON3_PIN, EXTI_IM_NOT_MASKED, EXTI_RT_RISING_DISABLED, EXTI_FT_FALLING_ENABLE);

    NVIC_SetPriority(EXTI4_IRQn, 1);
    NVIC_EnableIRQ(EXTI4_IRQn);

    while (1)
    {
        // place your loop code here

        if (is_button_pushed(BUTTON1))
        {
            turn_off_LED();
            color_change_on = !color_change_on;
            delay_ms(1000);
        }

        if (is_button_pushed(BUTTON2))
        {
            milliseconds -= 100;
            if (milliseconds < 0)
            {
                milliseconds = 0;
            }
        }

        if (color_change_on)
        {
            change_color_LED();
            delay_ms(milliseconds);
        }
    }

    return 0;
}

void turn_off_LED()
{
    if (current_color == BLUE)
    {
        GPIO_Toggle(LED_BLUE);
    }
    else if (current_color == RED)
    {
        GPIO_Toggle(LED_RED);
    }
    else if (current_color == GREEN)
    {
        GPIO_Toggle(LED_GREEN);
    }
    current_color = 0;
}

void change_color_LED()
{
    if (current_color == BLUE)
    {
        GPIO_Toggle(LED_BLUE);
        GPIO_Toggle(LED_RED);
        current_color = RED;
    }
    else if (current_color == RED)
    {
        GPIO_Toggle(LED_RED);
        GPIO_Toggle(LED_GREEN);
        current_color = GREEN;
    }
    else if (current_color == GREEN)
    {
        GPIO_Toggle(LED_GREEN);
        GPIO_Toggle(LED_BLUE);
        current_color = BLUE;
    }
    else
    {
        GPIO_Toggle(LED_BLUE);
        current_color = BLUE;
    }
}

int is_button_pushed(uint32_t port, uint8_t pin)
{
    return GPIO_Read(port, pin);
}