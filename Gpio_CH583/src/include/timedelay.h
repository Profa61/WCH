#ifndef __TIMEDELAY_H__
#define __TIMEDELAY_H__





#define FREQUENCY_DIVIDER      10000



bool TimeDelay (uint32_t delay);
void sysytem_initSystick(void);

void SysTick_Handler(void) __attribute__ ((interrupt("WCH-Interrupt-fast"))); // Aттрибут для вызова обработчика прерывания












#endif // TIMEDELAY_H
