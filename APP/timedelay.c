/*
 * Timedelay.c
 *
 *  Created on: Sep 11, 2024
 *      Author: v.tsaregorodtsev
 */

#include "CH58x_common.h"
#include <stdbool.h>
#include <stdint.h>
#include "include/timedelay.h"

volatile uint32_t timestamp = 0;

//===================================================================================
// Инициализация SysTick

void sysytem_initSystick(void)
{
    PFIC_EnableIRQ(SysTick_IRQn);  // Включаем прерывание SysTick
    SysTick_Config(FREQ_SYS / FREQUENCY_DIVIDER);
}

//===================================================================================

/*Ждет на входе задержку в МС
 *На выходе результат bool
 */

void TimeDelayMs(uint32_t DelayMs)
{
    uint32_t start_time = timestamp;

    while(1)
    {
        uint32_t current_time = timestamp;

        if( (current_time - start_time) >= DelayMs )
        {
            break;
        }
    }
}


//=====================================================================================
uint32_t millis()
{
    return timestamp;
}

//======================================================================================



void SysTick_Handler(void)__attribute__ ((interrupt("WCH-Interrupt-fast"))); // Aттрибут для вызова обработчика прерывания
void SysTick_Handler(void)
{
    timestamp++;
    SysTick->SR = 0;   // Очищаем флаг прерывания
}
