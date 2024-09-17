#ifndef TIM_H
#define TIM_H

#include <stdint.h>

// #define TIM2_BASE 0x40000000

#define TIM_DIER_OFFSET 0x00C // Für Timer 2 bis 5
#define TIM_PSC_OFFSET 0x028  // Für Timer 2 bis 5
#define TIM_ARR_OFFSET 0x02C  // Für Timer 2 bis 5
#define TIM_EGR_OFFSET 0x014  // Für Timer 2 bis 5
#define TIM_SR_OFFSET 0x010   // Für Timer 2 bis 5
#define TIM_CR1_OFFSET 0x000  // Für Timer 2 bis 5
#define TIM_CCER_OFFSET 0x020 // Für Timer 2 bis 5
#define TIM_CCR1_OFFSET 0x034 // Chanel 1
#define TIM_CCR2_OFFSET 0x038 // Chanel 2
#define TIM_CCMR1_OFFSET 0x018

// Register-Zugriff
#define REG32(addr) (*(volatile uint32_t *)(addr))

// Makros zur Berechnung von Registeradressen
#define TIM_DIER(timer_base) REG32(timer_base + TIM_DIER_OFFSET) // Für Timer 2 bis 5
#define TIM_PSC(timer_base) REG32(timer_base + TIM_PSC_OFFSET)   // Für Timer 2 bis 5
#define TIM_ARR(timer_base) REG32(timer_base + TIM_ARR_OFFSET)   // Für Timer 2 bis 5
#define TIM_EGR(timer_base) REG32(timer_base + TIM_EGR_OFFSET)   // Für Timer 2 bis 5
#define TIM_SR(timer_base) REG32(timer_base + TIM_SR_OFFSET)     // Für Timer 2 bis 5
#define TIM_CR1(timer_base) REG32(timer_base + TIM_CR1_OFFSET)   // Für Timer 2 bis 5
#define TIM_CCER(timer_base) REG32(timer_base + TIM_CCER_OFFSET) // Für Timer 2 bis 5
#define TIM_CCR1(timer_base) REG32(timer_base + TIM_CCR1_OFFSET) // Chanel 1
#define TIM_CCR2(timer_base) REG32(timer_base + TIM_CCR2_OFFSET) // Chanel 2
#define TIM_CCMR1(timer_base) REG32(timer_base + TIM_CCMR1_OFFSET)

// Systemtakt
#define F_SYS 16000000

void TIM_Enable();
void TIM_EnableTimer2();
void TIM_EnableTimer3();
void TIM_EnableTimer4();
void TIM_SetPrescaler(uint32_t timer_base, int f_req); // Für Timer 2 bis 5
void TIM_SetAutoReload(uint32_t timer_base, int arr);  // Für Timer 2 bis 5
void TIM_EnableCaptureCompare(uint32_t timer_base);    // Für Timer 2 bis 5
void TIM_SetCompare1Value(uint32_t timer_base, int compare);
void TIM_SetCompare2Value(uint32_t timer_base, int compare);
void TIM_EnableInterrupt(uint32_t timer_base);       // Für Timer 2 bis 5
void TIM_EnableUpdateInterrupt(uint32_t timer_base); // Für Timer 2 bis 5
void TIM_EnableCompare1Interrupt(uint32_t timer_base);
void TIM_EnableCompare2Interrupt(uint32_t timer_base);
void TIM_GenerateUpdateEvent(uint32_t timer_base); // Für Timer 2 bis 5
void TIM_DeleteUpdateEvent(uint32_t timer_base);   // Für Timer 2 bis 5
void TIM_StartUpdateEvent(uint32_t timer_base);    // Für Timer 2 bis 5
void TIM_SetPreload(uint32_t timer_base);
void TIM_SetPWM(uint32_t timer_base);

#endif