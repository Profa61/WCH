/********************************** (C) COPYRIGHT *******************************
 * File Name          : Main.c
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2020/08/06
 * Description        : ����1�շ���ʾ
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#include "CH58x_common.h"
#include <stdbool.h>
#include <stdint.h>








uint32_t time;
uint32_t time_anti_bounce;
bool flag_led;
volatile bool interrupt_flag = false;

#define DELAY_BLINK    1  // ��֧�

/*********************************************************************
 * @fn      main
 *
 * @brief   ������
 *
 * @return  none
 */
int main()
{


    GPIOB_ModeCfg(GPIO_Pin_4, GPIO_ModeIN_PU);
    GPIOB_ITModeCfg(GPIO_Pin_4, GPIO_ITMode_LowLevel);   // ���ѧ���ѧڧӧѧ֧� PB4 ���� ���֧��ӧѧߧڧ� ���� �ߧڧ٧ܧ�� ����ӧߧ�
    PFIC_EnableIRQ(GPIO_B_IRQn);

    GPIOB_SetBits(GPIO_Pin_18);                         // �����ѧߧ�ӧܧ� PB18 �ߧ� �ӧ����
    GPIOB_ModeCfg(GPIO_Pin_18, GPIO_ModeOut_PP_5mA);

    GPIOB_SetBits(GPIO_Pin_19);                         // �����ѧߧ�ӧܧ� PB19 �ߧ� �ӧ����
    GPIOB_ModeCfg(GPIO_Pin_19, GPIO_ModeOut_PP_5mA);




    while(1)
    {     /* ���ѧ�ڧѧߧ� �ާڧԧѧݧܧ� �ߧ� ��ѧۧާ֧�� �ҧ֧� �٧ѧէ֧�ا֧� */
        if(((time / 1000)/60 >= DELAY_BLINK) && (flag_led == false)){
        time = 0;
        flag_led = true;
        GPIOB_ResetBits(GPIO_Pin_18);
        }

        if(((time / 1000)/60 >= DELAY_BLINK) && (flag_led)){
        time = 0;
        flag_led = false;
        GPIOB_SetBits(GPIO_Pin_18);
        }
        time++;


           /* ���֧�֧ܧݧ��֧ߧڧ� �������ߧڧ� ��ӧ֧��էڧ�է�  ��� ��ݧѧԧ� ���֧��ӧѧߧڧ�*/
        if (interrupt_flag){
            GPIOB_InverseBits(GPIO_Pin_19);
            DelayMs(50);                       //���ѧ�ڧ�� ��� �է�֧ҧ֧٧ԧ�
            interrupt_flag = false;
        } // (interrupt_flag)


         /*���ڧԧѧݧܧ� �ߧ� �٧ѧէ֧�اܧ�*/
//        GPIOB_InverseBits(GPIO_Pin_18);
//        DelayMs(1000);


    } // while(1)

} // main




__INTERRUPT
__HIGH_CODE
void GPIOB_IRQHandler(void) {
    if(GPIOB_ReadITFlagBit(GPIO_Pin_4)){  // ����ݧ� ���֧��ӧѧߧڧ� ��� �ӧ��է� PB 4
        interrupt_flag = true;
        GPIOB_ClearITFlagBit(GPIO_Pin_4);
    }




}


