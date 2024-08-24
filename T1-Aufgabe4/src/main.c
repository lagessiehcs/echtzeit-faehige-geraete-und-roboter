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
int current_color = BLUE;

void change_color_LED(uint32_t port, uint8_t pin);
int is_button_pushed(uint32_t port, uint8_t pin);

int main(void)
{
    // place code to run once here
    GPIO_Init_Output(LED_BLUE, GPIO_OTYPE_PP);
    GPIO_Init_Output(LED_RED, GPIO_OTYPE_PP);
    GPIO_Init_Output(LED_GREEN, GPIO_OTYPE_PP);

    GPIO_Init_Input(BUTTON1, GPIO_PU);
    GPIO_Init_Input(BUTTON2, GPIO_PU);

    while (1)
    {
        // place your loop code here

        if (is_button_pushed(BUTTON1))
        {
            color_change_on = !color_change_on;
        }

        if (is_button_pushed(BUTTON2))
        {
            milliseconds -= 10;
            if (milliseconds < 0)
            {
                milliseconds = 0;
            }
        }

        if (color_change_on)
        {
            change_color_LED(LED_BLUE);
        }
    }

    return 0;
}

void change_color_LED(uint32_t port, uint8_t pin)
{
    if (current_color == BLUE)
    {
        GPIO_TogglePin(LED_RED);
        current_color = RED;
    }
    else if (current_color == RED)
    {
        GPIO_TogglePin(LED_GREEN);
        current_color = GREEN;
    }
    else if (current_color == GREEN)
    {
        GPIO_TogglePin(LED_BLUE);
        current_color = BLUE;
    }
    delay_ms(milliseconds);
}
int is_button_pushed(uint32_t port, uint8_t pin)
{
    return GPIO_ReadPin(port, pin);
}