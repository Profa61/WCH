#ifndef __TIMEDELAY_H__
#define __TIMEDELAY_H__





#define FREQUENCY_DIVIDER      10000



bool TimeDelay (uint32_t delay);
void sysytem_initSystick(void);

void SysTick_Handler(void) __attribute__ ((interrupt("WCH-Interrupt-fast"))); // A§ä§ä§â§Ú§Ò§å§ä §Õ§Ý§ñ §Ó§í§Ù§à§Ó§Ñ §à§Ò§â§Ñ§Ò§à§ä§é§Ú§Ü§Ñ §á§â§Ö§â§í§Ó§Ñ§ß§Ú§ñ












#endif // TIMEDELAY_H
