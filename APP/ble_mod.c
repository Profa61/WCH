/*
 * ble_mod.c
 *
 *  Created on: Sep 24, 2024
 *      Author: v.tsaregorodtsev
 */
#include "CONFIG.h"
#include "blink.h"
#include "ble_mod.h"
#include "broadcaster.h"
#include "peripheral.h"
#include <stdint.h>
#include <stdbool.h>
#include "timedelay.h"




enum BleMode  ble_mod;
uint8  advertising_enable = FALSE;

//============================================================
void ble_mode_init()
{
    static uint8_t initial_adv_event_type;
    static bool ble_state = false;



    switch(ble_mod)
    {
    case IDLE:
        break;


    case BLE_BEGIN:
        PRINT("BLE_BEGIN\n");
        if (ble_state)
        {
            ble_mod = SERVICE;
        }
        else
        {
            ble_mod = BEACON;
        }
        advertising_enable = FALSE;
        GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8), &advertising_enable);
        return;


    case BEACON:
        PRINT("BEACON\n");
       initial_adv_event_type = GAP_ADTYPE_ADV_NONCONN_IND;
        ble_mod = BLE_END;
        ble_state = true;
        return;


    case SERVICE:
        PRINT("SERVICE\n");
        initial_adv_event_type = GAP_ADTYPE_ADV_IND;
        ble_mod = BLE_END;
        ble_state = false;
        return;


    case BLE_END:
        PRINT("BLE_END\n");
        GAPRole_SetParameter(GAPROLE_ADV_EVENT_TYPE, sizeof(uint8_t), &initial_adv_event_type);
        advertising_enable = TRUE;
        GAPRole_SetParameter(GAPROLE_ADVERT_ENABLED, sizeof(uint8), &advertising_enable);
        ble_mod = IDLE;
        break;

    }
}

//===============================================================



