#include "blink.h"
#include <stdint.h>
#include <stdbool.h>
#include "CONFIG.h"
#include "timedelay.h"
#include "lis3dhspi.h"
#include "ble_mod.h"

#define count_blink    (uint8_t)(3)

volatile uint8_t count = 0;
uint32_t time = 0;
volatile bool flag_interrupt = false;
volatile bool flag_lis = false;

extern ble_mod;
//uint8_t buffer[2];

typedef enum
{
    LOW,
    HIGH,
}GPIOMode;

//=================================================================
void DigitalWrite(uint32_t gpio, GPIOMode mode)
{
    switch(mode)
        {
            case LOW:
                GPIOB_ResetBits(gpio);
                break;

            case HIGH:
                GPIOB_SetBits(gpio);
                break;

            default:
                break;
        }
}

//============================================================
void gpio_blink()
{
    if (count <= count_blink)
    {
        LowPower_Idle();
        DigitalWrite(LED1, HIGH);
        DigitalWrite(LED2, LOW);
        TimeDelayMs(100);
        DigitalWrite(LED1, LOW);
        DigitalWrite(LED2, HIGH);
        TimeDelayMs(100);

        count++;

    }
    else
    {
        DigitalWrite(LED1, LOW);
        DigitalWrite(LED2, LOW);
    }

    if(millis() - time >= 3000)
    {
        time = millis();
        DigitalWrite(LED1, HIGH);
        TimeDelayMs(50);
        DigitalWrite(LED1, LOW);
        SpiMultiRead();          //ЧТЕНИЕ ДАННЫХ ПО ОСЯМ X, Y, Z

    }

    if (flag_lis)
    {

        flag_lis = false;
        PFIC_EnableIRQ(GPIO_A_IRQn);

    }

    if (flag_interrupt)
    {
        flag_interrupt = false;
        SpiRead(WHO_AM_I);
        TimeDelayMs(50);
        ble_mod = BLE_BEGIN;
        PFIC_EnableIRQ(GPIO_B_IRQn);

    }

}
//===============================================================






__INTERRUPT
__HIGH_CODE
void GPIOB_IRQHandler(void)
{
    if(GPIOB_ReadITFlagBit(BUTTON))
    {
        //count = 0;
        flag_interrupt = true;
        GPIOB_ClearITFlagBit(BUTTON);
        PFIC_DisableIRQ(GPIO_B_IRQn);
    }
}



__INTERRUPT
__HIGH_CODE
void GPIOA_IRQHandler(void)
{
    if(GPIOA_ReadITFlagBit(LIS_INT1))
    {

        flag_lis = true;
        count = 0;
        GPIOA_ClearITFlagBit(LIS_INT1);
        PFIC_DisableIRQ(GPIO_A_IRQn);

    }
}
