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

#define DELAY_BLINK    1  // Сек

#define LED1           GPIO_Pin_18
#define LED2           GPIO_Pin_19
#define BUTTON         GPIO_Pin_4

/*********************************************************************
 * @fn      main
 *
 * @brief   ������
 *
 * @return  none
 */
int main()
{


    GPIOB_ModeCfg(BUTTON, GPIO_ModeIN_PU);
    GPIOB_ITModeCfg(BUTTON, GPIO_ITMode_LowLevel);   // Установка прерывания на вход PB4 при низком уровне
    PFIC_EnableIRQ(GPIO_B_IRQn);

    GPIOB_SetBits(LED1);                         // Инициализация PB 18 на выход
    GPIOB_ModeCfg(LED1, GPIO_ModeOut_PP_5mA);

    GPIOB_SetBits(LED2);                         // Инициализация PB 19 на выход
    GPIOB_ModeCfg(LED2, GPIO_ModeOut_PP_5mA);

///


    while(1)
    {     /* Мигалка на таймере */
        if(((time / 1000)/60 >= DELAY_BLINK) && (flag_led == false)){
        time = 0;
        flag_led = true;
        GPIOB_ResetBits(LED1);
        }

        if(((time / 1000)/60 >= DELAY_BLINK) && (flag_led)){
        time = 0;
        flag_led = false;
        GPIOB_SetBits(LED1);
        }
        time++;


           /* Переключение состояния светодиода по состоянию флага прерывания*/
        if (interrupt_flag){
            GPIOB_InverseBits(LED2);
            DelayMs(50);                       //Защита от дребезга
            interrupt_flag = false;
        } // (interrupt_flag)


         /*Мигалка на задержке*/
//        GPIOB_InverseBits(LED1);
//        DelayMs(1000);


    } // while(1)

} // main




__INTERRUPT
__HIGH_CODE
void GPIOB_IRQHandler(void) {
    if(GPIOB_ReadITFlagBit(BUTTON)){  // Если прерывание сработало по входу PB4
        interrupt_flag = true;
        GPIOB_ClearITFlagBit(BUTTON);
    }




}


