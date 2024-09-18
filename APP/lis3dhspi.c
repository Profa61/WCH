/*
 * lis3dhspi.c
 *
 *  Created on: Sep 11, 2024
 *      Author: v.tsaregorodtsev
 */
#include "lis3dhspi.h"
#include "CONFIG.h"
#include "timedelay.h"

//=====================================================================================
void SpiIinit()
{
 uint8_t lis_init[] =
 {       0x88,       // CTRL_REG5
         0x57,       // LIS3DH_CTRL_REG1
         0x20,       // INT1_THS
         0x01,       // INT1_DURATION
         0x20,       // INT1_CFG
         0x20,       // INT1_SOURCE
         0x40,       // CTRL_REG3
 };

    uint8_t buff;
    /* SPI 0 */
    GPIOA_ModeCfg(GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14, GPIO_ModeOut_PP_5mA);
    uint32_t sys_freq = GetSysClock();
    uint32_t spi_freq = SPI_FREQ;
    uint32_t div = sys_freq / spi_freq;
    SPI0_MasterDefInit();
    SPI0_CLKCfg(div);
    //SPI0_DataMode(Mode3_LowBitINFront);

    //SpiWrite(CTRL_REG5, lis_init[0]);
    TimeDelayMs(300);
    SpiRead(WHO_AM_I);
    SpiWrite(CTRL_REG1, lis_init[1]);
    SpiWrite(INT1_THS, lis_init[2]);
    SpiWrite(INT1_DURATION, lis_init[3]);
    SpiWrite(INT1_CFG, lis_init[4]);
    SpiWrite(INT1_SOURCE , lis_init[5]);
    SpiWrite(CTRL_REG3 , lis_init[6]);

    TimeDelayMs(500);

}

//=====================================================================================


void SpiRead(uint8_t lis_reg )
{
    uint8_t buff;
    GPIOA_ResetBits(GPIO_Pin_12);
    DelayUs(5);
    SPI0_MasterSendByte(lis_reg | LIS3DH_READ_FLAG);
    buff = SPI0_MasterRecvByte();
    DelayUs(5);
    GPIOA_SetBits(GPIO_Pin_12);
    PRINT("spi receive %x\n",buff);
    TimeDelayMs(5);
}
//======================================================================================

void SpiWrite(uint8_t lis_reg, uint8_t lis_mode){
    uint8_t mask = 0x00;
    GPIOA_ResetBits(GPIO_Pin_12);
    DelayUs(5);
    SPI0_MasterSendByte(mask | lis_reg);
    SPI0_MasterSendByte(lis_mode);
    DelayUs(5);
    GPIOA_SetBits(GPIO_Pin_12);
    TimeDelayMs(5);
}
//========================================================================================

void SpiMultiRead()
{
    uint8_t buff[6];
    int16_t x,y,z;

    GPIOA_ResetBits(GPIO_Pin_12);
    DelayUs(5);
    SPI0_MasterSendByte(OUT_X_H | LIS3DH_READ_FLAG);
    buff[0] = SPI0_MasterRecvByte();
    SPI0_MasterSendByte(OUT_X_L | LIS3DH_READ_FLAG);
    buff[1] = SPI0_MasterRecvByte();
    x = (int16_t)(buff[0]<<8 | buff[1]);
    DelayUs(5);
    GPIOA_SetBits(GPIO_Pin_12);

    GPIOA_ResetBits(GPIO_Pin_12);
    DelayUs(5);
    SPI0_MasterSendByte(OUT_Y_H | LIS3DH_READ_FLAG);
    buff[2] = SPI0_MasterRecvByte();
    SPI0_MasterSendByte(OUT_Y_L | LIS3DH_READ_FLAG);
    buff[3] = SPI0_MasterRecvByte();
    y = (int16_t)(buff[2]<<8 | buff[3]);
    DelayUs(5);
    GPIOA_SetBits(GPIO_Pin_12);


    GPIOA_ResetBits(GPIO_Pin_12);
    DelayUs(5);
    SPI0_MasterSendByte(OUT_Z_H | LIS3DH_READ_FLAG);
    buff[4] = SPI0_MasterRecvByte();
    SPI0_MasterSendByte(OUT_Z_L | LIS3DH_READ_FLAG);
    buff[5] = SPI0_MasterRecvByte();
    z = (int16_t)(buff[4]<<8 | buff[5]);
    DelayUs(5);
    GPIOA_SetBits(GPIO_Pin_12);


    PRINT("X- %d, ", x / 16);  PRINT("Y- %d, ", y / 16);   PRINT("Z- %d \n", z / 16);
}

//====================================================================================================


