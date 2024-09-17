#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include <gpio.h>
#include <tim.h>
#include "stm32g431xx.h"

#define MOTOR1 1
#define MOTOR2 2

#define FAST_DECAY 1
#define SLOW_DECAY 2

#define MOTOR11_PIN 4
#define MOTOR12_PIN 5
#define MOTOR21_PIN 6
#define MOTOR22_PIN 7

#define MOTOR11 GPIOB_BASE, MOTOR11_PIN
#define MOTOR12 GPIOB_BASE, MOTOR12_PIN
#define MOTOR21 GPIOB_BASE, MOTOR21_PIN
#define MOTOR22 GPIOB_BASE, MOTOR22_PIN

void MOTOR_Init(uint32_t port, uint8_t pin, uint8_t afsel, int f_req, int ar);
void MOTOR_SetSpeedMotor(int motor, int ar, int speed, int decay_speed);
void MOTOR_SetPWM(uint32_t port, uint8_t pin, int ar, int speed); // speed -100 to 100

#endif