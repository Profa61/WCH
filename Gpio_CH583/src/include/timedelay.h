#ifndef __TIMEDELAY_H__
#define __TIMEDELAY_H__





#define FREQUENCY_DIVIDER      10000



bool TimeDelay (uint32_t delay);
void sysytem_initSystick(void);

void SysTick_Handler(void) __attribute__ ((interrupt("WCH-Interrupt-fast"))); // A����ڧҧ�� �էݧ� �ӧ�٧�ӧ� ��ҧ�ѧҧ���ڧܧ� ���֧��ӧѧߧڧ�












#endif // TIMEDELAY_H
