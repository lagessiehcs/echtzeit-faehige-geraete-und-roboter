/**
 * EGR Praktikum
 * Termin 1 - Aufgabe 4
 */

#include <stdint.h>
#include <gpio.h>
#include <Delay_ms.h>

#define BLUE 1
#define RED 2
#define GREEN 3

#define LED_BLUE GPIOA_BASE, 8
#define LED_RED GPIOA_BASE, 9
#define LED_GREEN GPIOA_BASE, 10

#define BUTTON1 GPIOA_BASE, 2
#define BUTTON2 GPIOA_BASE, 3

uint32_t milliseconds = 500;
int color_change_on = 1;
int color_change_on_prevous = 0;
int current_color = 0;

void change_color_LED();
int is_button_pushed(uint32_t port, uint8_t pin);

int main(void)
{
    // place code to run once here
    GPIO_OutputInit(LED_BLUE, GPIO_OTYPE_PP);
    GPIO_OutputInit(LED_RED, GPIO_OTYPE_PP);
    GPIO_OutputInit(LED_GREEN, GPIO_OTYPE_PP);

    GPIO_InputInit(BUTTON1, GPIO_PU);
    GPIO_InputInit(BUTTON2, GPIO_PU);

    while (1)
    {
        // place your loop code here

        if (is_button_pushed(BUTTON1))
        {
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
        }
    }

    return 0;
}

void change_color_LED()
{
    if (current_color == BLUE)
    {
        GPIO_Toggle(LED_RED);
        delay_ms(milliseconds);
        GPIO_Toggle(LED_RED);
        current_color = RED;
    }
    else if (current_color == RED)
    {
        GPIO_Toggle(LED_GREEN);
        delay_ms(milliseconds);
        GPIO_Toggle(LED_GREEN);
        current_color = GREEN;
    }
    else if (current_color == GREEN)
    {
        GPIO_Toggle(LED_BLUE);
        delay_ms(milliseconds);
        GPIO_Toggle(LED_BLUE);
        current_color = BLUE;
    }
    else
    {
        GPIO_Toggle(LED_BLUE);
        delay_ms(milliseconds);
        GPIO_Toggle(LED_BLUE);
        current_color = BLUE;
    }
}
int is_button_pushed(uint32_t port, uint8_t pin)
{
    return GPIO_Read(port, pin);
}