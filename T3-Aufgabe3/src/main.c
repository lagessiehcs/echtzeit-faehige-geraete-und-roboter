/**
 * EGR Praktikum
 * Termin 3 - Aufgabe 3
 */

#include <stdint.h>
#include <adc.h>
#include "UART.h"

#define POTI GPIOB_BASE, 0

int main(void)
{
    int voltage = 0;
    char voltage_buf[32];

    ADC_Config_Poti(POTI);
    ADC_Calibrate();
    ADC_StartADC();

    while (1)
    {
        voltage = ADC_GetValue();

        sprintf(voltage_buf, "Voltage: %i \r\n", voltage);

        // Befehl zum Senden einer Zeichenkette
        UARTsend((uint8_t *)voltage_buf, strlen(voltage_buf));

        delay_ms(500);
    }

    return 0;
}