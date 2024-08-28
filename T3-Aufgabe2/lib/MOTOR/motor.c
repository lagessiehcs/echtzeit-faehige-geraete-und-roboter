#include "motor.h"

void MOTOR_Init(uint32_t port, uint8_t pin, uint8_t afsel, int f_req, int ar)
{
    uint32_t timer_base = 0;

    if (pin == 4 || pin == 5)
    {
        timer_base = TIM3_BASE;
    }
    else if (pin == 6 || pin == 7)
    {
        timer_base = TIM4_BASE;
    }

    GPIO_AlternativeInit(port, pin, afsel); // GPIO aktivieren und Pin AF zuweisen
    TIM_Enable();                           // Timer aktivieren
    TIM_SetPWM(timer_base);
    TIM_SetPreload(timer_base);
    TIM_SetPrescaler(timer_base, f_req);
    TIM_SetAutoReload(timer_base, ar);
    TIM_EnableCaptureCompare(timer_base); // Output aktivieren
    TIM_EnableInterrupt(timer_base);      // Output aktivieren
    TIM_GenerateUpdateEvent(timer_base);  // Timer initialisieren
    TIM_StartUpdateEvent(timer_base);     // Timer einschalten#
}

void MOTOR_SetSpeedMotor(int motor, int ar, int speed, int decay_speed)
{
    if (motor == MOTOR1)
    {
        if (speed >= 0 && decay_speed == FAST_DECAY)
        {
            MOTOR_SetPWM(MOTOR11, ar, 0);
            MOTOR_SetPWM(MOTOR12, ar, speed);
        }
        else if (speed >= 0 && decay_speed == SLOW_DECAY)
        {
            MOTOR_SetPWM(MOTOR11, ar, speed);
            MOTOR_SetPWM(MOTOR12, ar, 100);
        }
        else if (speed < 0 && decay_speed == FAST_DECAY)
        {
            MOTOR_SetPWM(MOTOR11, ar, speed);
            MOTOR_SetPWM(MOTOR12, ar, 0);
        }
        else if (speed < 0 && decay_speed == SLOW_DECAY)
        {
            MOTOR_SetPWM(MOTOR11, ar, 100);
            MOTOR_SetPWM(MOTOR12, ar, speed);
        }
    }
    else if (motor == MOTOR2)
    {
        if (speed >= 0 && decay_speed == FAST_DECAY)
        {
            MOTOR_SetPWM(MOTOR21, ar, speed);
            MOTOR_SetPWM(MOTOR22, ar, 0);
        }
        else if (speed >= 0 && decay_speed == SLOW_DECAY)
        {
            MOTOR_SetPWM(MOTOR21, ar, 100);
            MOTOR_SetPWM(MOTOR22, ar, speed);
        }
        else if (speed < 0 && decay_speed == FAST_DECAY)
        {
            MOTOR_SetPWM(MOTOR21, ar, 0);
            MOTOR_SetPWM(MOTOR22, ar, -speed);
        }
        else if (speed < 0 && decay_speed == SLOW_DECAY)
        {
            MOTOR_SetPWM(MOTOR21, ar, -speed);
            MOTOR_SetPWM(MOTOR22, ar, 100);
        }
    }
}

void MOTOR_SetPWM(uint32_t port, uint8_t pin, int ar, int speed)
{
    uint32_t timer_base = 0;
    int compare = 0;

    if (pin == 4 || pin == 5)
    {
        timer_base = TIM3_BASE;
    }
    else if (pin == 6 || pin == 7)
    {
        timer_base = TIM4_BASE;
    }

    if (speed < 0)
    {
        compare = -speed * ar / 100;
    }
    else if (speed >= 0)
    {
        compare = speed * ar / 100;
    }

    if (pin == 4 || pin == 6)
    {
        TIM_SetCompare1Value(timer_base, (int)compare);
    }
    else if (pin == 5 || pin == 7)
    {
        TIM_SetCompare2Value(timer_base, (int)compare);
    }
}