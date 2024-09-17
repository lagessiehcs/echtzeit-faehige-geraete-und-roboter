/**
 * EGR Praktikum
 * Termin 3 - Aufgabe 3
 */

#include <stdint.h>
#include <adc.h>
#include "UART.h"

#define HELL1 GPIOA_BASE, 0
#define HELL2 GPIOA_BASE, 1
#define HELL3 GPIOA_BASE, 7

int main(void)
{
    int *hell;
    // HELL hell;
    char hell_buf[50];

    ADC_Config_Hell(HELL1, HELL2, HELL3);

    ADC_Calibrate();
    ADC_StartADC();

    while (1)
    {
        hell = ADC_GetValue_Hell();
        // int volatile a = hell[0];
        // int volatile b = hell[1];
        // int volatile c = hell[2];

        // sprintf(hell_buf, "Hell1: %i, Hell2: %i, Hell3: %i \r\n", hell.hell1, hell.hell2, hell.hell3);
        sprintf(hell_buf, "Left1: %i, Middle2: %i, Right3: %i \r\n", hell[0], hell[1], hell[2]);

        // Befehl zum Senden einer Zeichenkette
        UARTsend((uint8_t *)hell_buf, strlen(hell_buf));

        // delay_ms(500);
    }

    return 0;
}