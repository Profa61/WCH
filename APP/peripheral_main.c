/********************************** (C) COPYRIGHT *******************************
 * File Name          : main.c
 * Author             : WCH
 * Version            : V1.1
 * Date               : 2020/08/06
 * Description        : 外设从机应用主函数及任务系统初始化
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
/* 头文件包含 */
#include "CONFIG.h"
#include "HAL.h"
#include "gattprofile.h"
#include "peripheral.h"
#include "app_uart.h"
#include "blink.h"
#include "CH58x_common.h"
#include "timedelay.h"
#include "lis3dhspi.h"



//__attribute__((aligned(4))) UINT8 spiBuff[] = {0x32, 0x01, 0x33, 0x01, 0x30, 0x55 };







/*********************************************************************
 * GLOBAL TYPEDEFS
 */
__attribute__((aligned(4))) u32 MEM_BUF[BLE_MEMHEAP_SIZE / 4];

#if(defined(BLE_MAC)) && (BLE_MAC == TRUE)
u8C MacAddr[6] = {0x84, 0xC2, 0xE4, 0x03, 0x02, 0x02};
#endif

/*******************************************************************************
 * Function Name  : Main_Circulation
 * Description    : 主循环
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
__HIGH_CODE
__attribute__((noinline))
void Main_Circulation()

{

    while(1)
    {

        TMOS_SystemProcess();
        app_uart_process();
        gpio_blink();

    }
}

/*******************************************************************************
 * Function Name  : main
 * Description    : 主函数
 * Input          : None
 * Output         : None
 * Return         : None
 *******************************************************************************/
int main(void)
{
    SetSysClock(CLK_SOURCE_PLL_60MHz);

    GPIOA_ModeCfg(LIS_INT1, GPIO_ModeIN_PU);
    GPIOA_ITModeCfg(LIS_INT1, GPIO_ITMode_LowLevel);
    PFIC_EnableIRQ(GPIO_A_IRQn);


    GPIOB_ModeCfg(BUTTON, GPIO_ModeIN_PU);
    GPIOB_ITModeCfg(BUTTON, GPIO_ITMode_LowLevel);
    PFIC_EnableIRQ(GPIO_B_IRQn);

    GPIOB_ResetBits(LED1);
    GPIOB_ModeCfg(LED1, GPIO_ModeOut_PP_5mA);

    GPIOB_ResetBits(LED2);
    GPIOB_ModeCfg(LED2, GPIO_ModeOut_PP_5mA);



#ifdef DEBUG
    GPIOA_SetBits(bTXD1);                       //bTXD1
    GPIOA_ModeCfg(bTXD1, GPIO_ModeOut_PP_5mA);  //bTXD1
    UART1_DefInit();
#endif


  // PRINT("%s\n", VER_LIB);
   CH58X_BLEInit();
   HAL_Init();
   GAPRole_PeripheralInit();
   Peripheral_Init();
   app_uart_init();
   sysytem_initSystick();
   SpiIinit();
   Main_Circulation();
} //main()










/******************************** endfile @ main ******************************/
