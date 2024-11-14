/************************************************************************
 *
 * Copyright (c) 2024 TakeMe2Space as represented by the
 * All Rights Reserved.
 *
 ************************************************************************/

#include "i2c_functions.h"

#ifndef SUNSENSE_H
#define SUNSENSE_H

#define SS_I2C_ADDR 0x29
#define SS_DEV_ID 0x01

#define CONF_CONST 28736

#define CONF_0 0
#define CONF_1 1

#define ALS_DATA_REG 0x10

#define IR_DATA_REG 0x12

#define DEV_ID_REG 0x14

// Function Prototypes

bool Init_SunSensor();
uint16_t GetSunSensorVis_Lux();
uint16_t GetSunSensorIR_Lux();

#endif /* SUNSENSE_H */