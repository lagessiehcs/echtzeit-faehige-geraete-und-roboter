/**
 * EGR Praktikum
 * Termin 3 - Aufgabe 2
 */

#include <stdint.h>
#include <gpio.h>
#include <syscfg.h>
#include <exti.h>
#include <tim.h>
#include <motor.h>
#include <Delay_ms.h>
#include "stm32g431xx.h"

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define BUTTON1 GPIOA_BASE, BUTTON1_PIN
#define BUTTON2 GPIOA_BASE, BUTTON2_PIN

int is_button_pushed(uint32_t port, uint8_t pin);

float speed = 0;
int decay_speed = FAST_DECAY;

int main(void)
{
    // place code to run once here
    int auto_reload = 10000;
    int f_req = 1000000;

    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);

    GPIO_InputInit(BUTTON1, GPIO_PU);
    GPIO_InputInit(BUTTON2, GPIO_PU);

    // MOTOR_SetPWM(MOTOR21, auto_reload, 1);
    // MOTOR_SetPWM(MOTOR22, auto_reload, 100);

    while (1)
    {
        if (is_button_pushed(BUTTON1))
        {
            speed -= 0.001;
            if (speed < -100)
            {
                speed = -100;
            }
        }
        else if (is_button_pushed(BUTTON2))
        {
            speed += 0.001;
            if (speed > 100)
            {
                speed = 100;
            }
        }

        MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
        MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
    }
    return 0;
}

int is_button_pushed(uint32_t port, uint8_t pin)
{
    return GPIO_Read(port, pin);
}