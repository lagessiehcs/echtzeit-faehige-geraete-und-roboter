

#include <stdint.h>
#include <adc.h>
#include "UART.h"
#include <motor.h>

#define LEFT 0
#define STRAIGHT 1
#define RIGHT 2
#define STOP 3

#define HELL1 GPIOA_BASE, 0
#define HELL2 GPIOA_BASE, 1
#define HELL3 GPIOA_BASE, 7

#define MOTOR11_PIN 4
#define MOTOR12_PIN 5
#define MOTOR21_PIN 6
#define MOTOR22_PIN 7

#define MOTOR11 GPIOB_BASE, MOTOR11_PIN
#define MOTOR12 GPIOB_BASE, MOTOR12_PIN
#define MOTOR21 GPIOB_BASE, MOTOR21_PIN
#define MOTOR22 GPIOB_BASE, MOTOR22_PIN

void straight();
void turnleft(int);
void turnright(int);
void backleft();

void stop();
int decay_speed = FAST_DECAY;
int auto_reload = 1000;
int f_req = 100000;
int straightvel1 = 20;
int straightvel2 = 20;
int smallvel = 30;
int bigvel = 30;
int last = STRAIGHT;
int back = 50;
int backsmall = 20;

int delay = 50;

int main(void)
{

    MOTOR_Init(MOTOR11, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR12, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR21, 0b0010, f_req, auto_reload);
    MOTOR_Init(MOTOR22, 0b0010, f_req, auto_reload);
    int *hell;
    char hell_buf[50];

    ADC_Config_Hell(HELL1, HELL2, HELL3);

    ADC_Calibrate();
    ADC_StartADC();

    int left = 0;
    int middle = 0;
    int right = 0;

    int lastleft = 0;
    int lastmiddle = 0;
    int lastright = 0;

    while (1)
    {
        lastleft = left;
        lastmiddle = middle;
        lastright = right;

        hell = ADC_GetValue_Hell();
        for (int i = 0; i < 3; i++)
        {
            if (hell[i] < 200)
            {
                hell[i] = 0;
            }
            else
            {
                hell[i] = 1;
            }
        }

        left = hell[0];
        middle = hell[1];
        right = hell[2];

        sprintf(hell_buf, "Left1: %i, Middle2: %i, Right3: %i \r\n", left, middle, right);

        // Befehl zum Senden einer Zeichenkette
        UARTsend((uint8_t *)hell_buf, strlen(hell_buf));

        if (left == 0 && middle == 0 && right == 0)
        {
            // turnleft(bigvel);
            straight();
        }
        else if (left == 0 && middle == 0 && right == 1)
        {
            straight();
            last = STRAIGHT;
        }
        else if (left == 0 && middle == 1 && right == 1)
        {
            turnleft(smallvel);
            last = LEFT;
        }

        else if (left == 1 && middle == 1 && right == 0)
        {
            turnright(bigvel);
            last = RIGHT;
        }
        else if (left == 1 && middle == 1 && right == 1)
        {
            backleft();
            last = STRAIGHT;
        }
        // else if (left == 1 && middle == 0 && right == 1)
        // {
        //     stop();
        //     last = STOP;
        // }
        // else if (left == 0 && middle == 1 && right == 0)
        // {
        //     straight();
        //     last = STRAIGHT;
        // }
    }

    return 0;
}

void straight()
{
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, straightvel1, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, straightvel2, decay_speed);
}
void backleft()
{
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, -back, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, -backsmall, decay_speed);
}

void turnleft(int bigsmall)
{
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, bigsmall, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, 0, decay_speed);
}
void turnright(int bigsmall)
{
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, 0, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, bigsmall, decay_speed);
}
void stop()
{
    MOTOR_SetSpeedMotor(MOTOR1, auto_reload, 0, decay_speed);
    MOTOR_SetSpeedMotor(MOTOR2, auto_reload, 0, decay_speed);
}