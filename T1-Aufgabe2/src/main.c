/**
 * EGR Praktikum
 * Termin 1 - Aufgabe 2
 */

#include <stdint.h>

#define LED_BLUE_PIN 8
#define LED_RED_PIN 9
#define LED_GREEN_PIN 10

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define BUTTON3_PIN 4

void turn_on_LED(int);
void turn_off_LED(int);
int is_button_pushed(int);
void GPIOInit();
void LEDInit(int);
void ButtonInit(int);

int main(void)
{
    // place code to run once here
    GPIOInit();
    LEDInit(LED_BLUE_PIN);
    LEDInit(LED_RED_PIN);
    LEDInit(LED_GREEN_PIN);
    ButtonInit(BUTTON1_PIN);
    ButtonInit(BUTTON2_PIN);
    ButtonInit(BUTTON3_PIN);

    while (1)
    {
        // place your loop code here
        if (is_button_pushed(BUTTON1_PIN))
        {
            turn_on_LED(LED_BLUE_PIN);
        }
        else
        {
            turn_off_LED(LED_BLUE_PIN);
        }
        if (is_button_pushed(BUTTON2_PIN))
        {
            turn_on_LED(LED_RED_PIN);
        }
        else
        {
            turn_off_LED(LED_RED_PIN);
        }
        if (is_button_pushed(BUTTON3_PIN))
        {
            turn_on_LED(LED_GREEN_PIN);
        }
        else
        {
            turn_off_LED(LED_GREEN_PIN);
        }
    }

    return 0;
}

void GPIOInit()
{
    // ------- STEP 1: Module aktivieren -------
    // Aktivierung des GPIO A Moduls
    uint32_t volatile *adresse = (uint32_t *)(0x40021000 + 0x4C);
    *adresse |= (1 << 0);
}

void LEDInit(int led_pin)
{
    // ------- STEP 2: Pin als Output konfigurieren -------
    // LED Pin als Output konfigurieren
    uint32_t volatile *adresse = (uint32_t *)(0x48000000 + 0x00);
    *adresse &= ~(1 << (2 * led_pin + 1));
    *adresse |= (1 << (2 * led_pin));

    // LED Pin als push-pull einstellen
    adresse = (uint32_t *)(0x48000000 + 0x04);
    *adresse &= ~(1 << led_pin);
}

void ButtonInit(int button_pin)
{
    // ------- STEP 2: Pin als Output konfigurieren -------
    // Taster Pin als Input konfigurieren
    uint32_t volatile *adresse = (uint32_t *)(0x48000000 + 0x00);
    *adresse &= ~(1 << (2 * button_pin + 1));
    *adresse &= ~(1 << (2 * button_pin));

    // Taster Pin als Pull-Up-Widerstand einstellen
    // (Pull-Up weil Taster gegen Ground verschaltet, vgl. Skript S. 111)
    adresse = (uint32_t *)(0x48000000 + 0x0C);
    *adresse |= (1 << (2 * button_pin));
    *adresse &= ~(1 << (2 * button_pin + 1));
}

void turn_on_LED(int led_pin)
{
    // ------- STEP 3: Pin einschalten -------
    // LED anschalten
    uint32_t volatile *adresse = (uint32_t *)(0x48000000 + 0x14);
    *adresse |= (1 << led_pin);
}

void turn_off_LED(int led_pin)
{
    // ------- STEP 3: Pin einschalten -------
    // LED anschalten
    uint32_t volatile *adresse = (uint32_t *)(0x48000000 + 0x14);
    *adresse &= ~(1 << led_pin);
}

int is_button_pushed(int button_pin)
{
    // ------- STEP 3: Taster einlesen -------
    // Taster einlesen
    uint32_t volatile *adresse = (uint32_t *)(0x48000000 + 0x10);
    int bit = ((*adresse & (1 << button_pin)));
    if (bit)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}