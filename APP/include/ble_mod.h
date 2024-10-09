/*
 * ble_mod.h
 *
 *  Created on: Sep 24, 2024
 *      Author: v.tsaregorodtsev
 */

#ifndef INCLUDE_BLE_MOD_H_
#define INCLUDE_BLE_MOD_H_

enum BleMode
{   IDLE = 1,
    BEACON,
    SERVICE,
    BLE_BEGIN,
    BLE_END
};


void ble_mode_init();

#endif /* INCLUDE_BLE_MOD_H_ */
