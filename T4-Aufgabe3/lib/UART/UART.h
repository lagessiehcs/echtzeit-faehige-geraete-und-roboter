#ifndef UART_H
#define UART_H

#include "stm32g4xx_hal.h"
#include "stdio.h"
#include "string.h"

// using HAL functions given by STM

void UARTsend(uint8_t *data, uint16_t length);

#endif