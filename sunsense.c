/************************************************************************
 *
 * Copyright (c) 2024 TakeMe2Space as represented by the
 * All Rights Reserved.
 *
 ************************************************************************/

#include "sunsense.h"

uint8_t Vis_MSB;
uint8_t Vis_LSB;
uint16_t vis_lux;

uint8_t IR_MSB;
uint8_t IR_LSB;
uint16_t ir_lux;

bool Init_SunSensor()
{
    uint8_t data;

    if (is_i2c_device_open(SS_I2C_ADDR) == false)
        return false;

    read_sunsensor_byte_data(DEV_ID_REG, &data);
    if (data != SS_DEV_ID)
        return false;

    if (write_sunsensor_word(CONF_0, (uint16_t *)CONF_CONST) == false)
        return false;

    return true;
}

uint16_t GetSunSensorVis_Lux()
{

    uint8_t data[2];

    read_sunsensor_block_data(ALS_DATA_REG, data);

    Vis_LSB = data[0];
    Vis_MSB = data[1];

    vis_lux = ((Vis_MSB << 8) | Vis_LSB);

    return vis_lux;
}

uint16_t GetSunSensorIR_Lux()
{

    uint8_t data[2];

    read_sunsensor_block_data(IR_DATA_REG, data);

    IR_LSB = data[0];
    IR_MSB = data[1];

    ir_lux = (IR_MSB << 8) | IR_LSB;

    return ir_lux;
}