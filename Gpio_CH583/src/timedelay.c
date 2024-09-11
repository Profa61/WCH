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

// §¯§Ñ§ã§ä§â§à§Û§Ü§Ñ SysTick
void sysytem_initSystick(void)
{
  PFIC_EnableIRQ(SysTick_IRQn);  // §£§Ü§Ý§ð§é§Ñ§ð §á§â§Ö§â§í§Ó§Ñ§ß§Ú§Ö §à§ä §³§Ú§ã§ä§Ö§Þ§ß§à§Ô§à §ä§Ñ§Û§Þ§Ö§â§Ñ
  SysTick_Config(FREQ_SYS / FREQUENCY_DIVIDER);
}




/*§±§Ö§â§Ö§Õ§Ñ§Ö§ä§ã§ñ §Ó§â§Ö§Þ§ñ §Ù§Ñ§Õ§Ö§â§Ø§Ü§Ú §Ó §Þ§Ú§Ý§Ý§Ú§ã§Ö§Ü§å§ß§Õ§Ñ§ç
 §¯§Ñ §Ó§í§ç§à§Õ§Ö bool*/

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
  SysTick->SR = 0;   // §°§é§Ú§ë§Ñ§ð §Ñ§á§á§Ñ§â§Ñ§ä§ß§í§Û §æ§Ý§Ñ§Ô
}
