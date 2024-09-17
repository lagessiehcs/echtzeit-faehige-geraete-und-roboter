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

float speed = 9;
int decay_speed = FAST_DECAY;
int f_req = 1000000;

void dol()
{
    int auto_reload = 612;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}

void re()
{
    int auto_reload = 545;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}

void mi()
{
    int auto_reload = 485;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}
void fa()
{
    int auto_reload = 458;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}
void sol()
{
    int auto_reload = 408;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}
void la()
{
    int auto_reload = 364;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}
void si()
{
    int auto_reload = 324;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}
void do2()
{
    int auto_reload = 306;
    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, speed, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, speed, decay_speed);
}
int main(void)
{
    // place code to run once here

    GPIO_InputInit(BUTTON1, GPIO_PU);
    GPIO_InputInit(BUTTON2, GPIO_PU);

    // MOTOR_SetPWM(MOTOR21, auto_reload, 1);
    // MOTOR_SetPWM(MOTOR22, auto_reload, 100);

    while (1)
    {

        dol();
        delay_ms(500);
        dol();
        delay_ms(500);
        sol();
        delay_ms(500);
        sol();
        delay_ms(500);
        la();
        delay_ms(500);
        la();
        delay_ms(500);
        sol();
        delay_ms(500);
        delay_ms(500);
        fa();
        delay_ms(500);
        fa();
        delay_ms(500);
        mi();
        delay_ms(500);
        mi();
        delay_ms(500);
        re();
        delay_ms(500);
        re();
        delay_ms(500);
        dol();
        delay_ms(500);
        delay_ms(500);
        sol();
        delay_ms(500);
        sol();
        delay_ms(500);
        fa();
        delay_ms(500);
        fa();
        delay_ms(500);
        mi();
        delay_ms(500);
        mi();
        delay_ms(500);
        re();
        delay_ms(500);
        delay_ms(500);
        sol();
        delay_ms(500);
        sol();
        delay_ms(500);
        fa();
        delay_ms(500);
        fa();
        delay_ms(500);
        mi();
        delay_ms(500);
        mi();
        delay_ms(500);
        re();
        delay_ms(500);
        delay_ms(500);
        dol();
        delay_ms(500);
        dol();
        delay_ms(500);
        sol();
        delay_ms(500);
        sol();
        delay_ms(500);
        la();
        delay_ms(500);
        la();
        delay_ms(500);
        sol();
        delay_ms(500);
        delay_ms(500);
        fa();
        delay_ms(500);
        fa();
        delay_ms(500);
        mi();
        delay_ms(500);
        mi();
        delay_ms(500);
        re();
        delay_ms(500);
        re();
        delay_ms(500);
        dol();
        delay_ms(500);
        delay_ms(500);
    }
    return 0;
}

int is_button_pushed(uint32_t port, uint8_t pin)
{
    return GPIO_Read(port, pin);
}
