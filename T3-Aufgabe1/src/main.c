/**
 * EGR Praktikum
 * Termin 3 - Aufgabe 1
 */

#include <stdint.h>
#include <gpio.h>
#include <syscfg.h>
#include <exti.h>
#include <tim.h>
#include <Delay_ms.h>
#include "stm32g431xx.h"

#define MOTOR11_PIN 4
#define MOTOR12_PIN 5
#define MOTOR21_PIN 6
#define MOTOR22_PIN 7

#define MOTOR11 GPIOB_BASE, MOTOR11_PIN
#define MOTOR12 GPIOB_BASE, MOTOR12_PIN
#define MOTOR21 GPIOB_BASE, MOTOR21_PIN
#define MOTOR22 GPIOB_BASE, MOTOR22_PIN

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3

#define BUTTON1 GPIOA_BASE, BUTTON1_PIN
#define BUTTON2 GPIOA_BASE, BUTTON2_PIN

void forward();
void backward();
void standby();
int is_button_pushed(uint32_t port, uint8_t pin);

int main(void)
{
    // place code to run once here
    GPIO_OutputInit(MOTOR11, GPIO_OTYPE_PP);
    GPIO_OutputInit(MOTOR12, GPIO_OTYPE_PP);
    GPIO_OutputInit(MOTOR21, GPIO_OTYPE_PP);
    GPIO_OutputInit(MOTOR22, GPIO_OTYPE_PP);
    GPIO_InputInit(BUTTON1, GPIO_PU);
    GPIO_InputInit(BUTTON2, GPIO_PU);

    while (1)
    {
        if (is_button_pushed(BUTTON1))
        {
            backward();
        }
        else if (is_button_pushed(BUTTON2))
        {
            forward();
        }
        else
        {
            standby();
        }
    }

    return 0;
}

void forward()
{
    GPIO_Write(MOTOR11, 0);
    GPIO_Write(MOTOR12, 1);
    GPIO_Write(MOTOR21, 0);
    GPIO_Write(MOTOR22, 1);
}

void backward()
{
    GPIO_Write(MOTOR11, 1);
    GPIO_Write(MOTOR12, 0);
    GPIO_Write(MOTOR21, 1);
    GPIO_Write(MOTOR22, 0);
}

void standby()
{
    GPIO_Write(MOTOR11, 0);
    GPIO_Write(MOTOR12, 0);
    GPIO_Write(MOTOR21, 0);
    GPIO_Write(MOTOR22, 0);
}

int is_button_pushed(uint32_t port, uint8_t pin)
{
    return GPIO_Read(port, pin);
}