#include "adc.h"

void ADC_Config_Poti(uint32_t port, uint8_t pin)
{
    ADC_RCC_Enable();
    ADC_RCC_CCIPR_IndependentClockConfig();
    GPIO_AnalogInit(port, pin);
    ADC_DisableDeepDown();
    ADC_EnableVoltageRegulator();
    delay_ms(10);
    ADC_DisableADC();
    ADC_SQR1_SetSequenceLength(1);
    ADC_SQR1_SetSequence(15, 1);
    ADC_SetSingleEndedMode();
    ADC_SetConversionMode(ADC_CFGR_SINGLECONVERSION);
}

void ADC_Config_Hell(uint32_t port1, uint8_t pin1, uint32_t port2, uint8_t pin2, uint32_t port3, uint8_t pin3)
{
    ADC_RCC_Enable();
    ADC_RCC_CCIPR_IndependentClockConfig();
    GPIO_AnalogInit(port1, pin1);
    GPIO_AnalogInit(port2, pin2);
    GPIO_AnalogInit(port3, pin3);
    ADC_DisableDeepDown();
    ADC_EnableVoltageRegulator();
    delay_ms(10);
    ADC_DisableADC();
    ADC_SQR1_SetSequenceLength(3);
    ADC_SQR1_SetSequence(1, 1);
    ADC_SQR1_SetSequence(2, 2);
    ADC_SQR1_SetSequence(4, 3);
    ADC_SetSingleEndedMode();
    ADC_SetConversionMode(ADC_CFGR_SINGLECONVERSION);
}

void ADC_Calibrate()
{
    int adcal = 1;
    ADC_CR |= (1 << 31); // ADCAL setzen

    while (adcal)
    {
        adcal = (ADC_CR >> 31) & 1;
    }

    ADC_ISR |= (1 << 0); // ADRDY =1

    delay_ms(1);
}
void ADC_StartADC()
{
    int adrdy = 0;
    ADC_CR |= (1 << 0); // ADEN = 1
    while (!adrdy)
    {
        adrdy = (ADC_ISR >> 0) & 1;
    }
}

int ADC_GetValue_Poti()
{
    ADC_StartConversion();
    int value = ADC_ReadData();
    ADC_DeleteEOS();
    return value;
}

// HELL ADC_GetValue_Hell()
// {

//     HELL value;

//     value.hell1 = ADC_ReadData();
//     value.hell2 = ADC_ReadData();
//     value.hell3 = ADC_ReadData();

//     ADC_DeleteEOS();

//     return value;
// }

int *ADC_GetValue_Hell()
{

    static int value[3] = {0, 0, 0};
    ADC_StartConversion();

    value[0] = ADC_ReadData();
    value[1] = ADC_ReadData();
    value[2] = ADC_ReadData();

    ADC_DeleteEOS();

    return value;
}

void ADC_DeleteEOS()
{
    // EOS = 1
    ADC_ISR |= (1 << 3);
}

void ADC_StartConversion()
{
    // ADSTART setzen
    ADC_CR |= (1 << 2);
}

int ADC_ReadData()
{
    int eoc = 0;
    while (!eoc)
    {
        eoc = (ADC_ISR >> 2) & 1;
    }
    int a = ADC_DR;
    return a;
}

void ADC_RCC_Enable()
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x4C);
    *adresse |= (1 << 13);
}

void ADC_RCC_CCIPR_IndependentClockConfig()
{
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x88);
    *adresse |= (1 << 29);  // Set system clock
    *adresse &= ~(1 << 28); // Set system clock
}

void ADC_DisableDeepDown()
{
    ADC_CR &= ~(1 << 29);
}

void ADC_EnableVoltageRegulator()
{
    ADC_CR |= (1 << 28);
}

void ADC_DisableADC()
{
    ADC_CR &= ~(1 << 0);
}

void ADC_SQR1_SetSequenceLength(int L)
{
    ADC_SQR1 &= ~(0b1111 << 0);
    ADC_SQR1 |= ((L - 1) << 0);
}
void ADC_SQR1_SetSequence(int chanel, int sequence_nr)
{
    ADC_SQR1 &= ~(0b11111 << 6 * sequence_nr);
    ADC_SQR1 |= (chanel << 6 * sequence_nr);
}

void ADC_SetSingleEndedMode()
{
    ADC_CR &= ~(1 << 30);
}

void ADC_SetConversionMode(int mode)
{
    ADC_CFGR &= ~(1 << 13);
    ADC_CFGR |= (mode << 13);
}