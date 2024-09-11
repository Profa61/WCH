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

volatile uint32_t timestamp;

// ���ѧ����ۧܧ� SysTick
void sysytem_initSystick(void)
{
  PFIC_EnableIRQ(SysTick_IRQn);  // Включаем прерывание SysTick
  SysTick_Config(FREQ_SYS / FREQUENCY_DIVIDER);
}




/*Ждет на входе задержку в МС
 *На выходе результат bool
 */

bool TimeDelay (uint32_t delay){
   static uint32_t time_delay;

    if(timestamp - time_delay >= delay){
        time_delay = timestamp;
        return true;

    }else return false;
    }



void SysTick_Handler(void)
{
    timestamp++;
  SysTick->SR = 0;   // Очищаем флаг прерывания
}
