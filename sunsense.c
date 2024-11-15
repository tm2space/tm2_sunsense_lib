/************************************************************************
 *
 * Copyright (c) 2024 TakeMe2Space as represented by the
 * All Rights Reserved.
 *
 ************************************************************************/


/*
 * sunsense.c
 * 
 * This file provides higher-level functionality for interacting with the TM2S
 * SunSensor device over I2C. It includes initialization of the sensor
 * and methods to retrieve visible light and infrared light lux readings.
 */


#include "sunsense.h"

uint8_t Vis_MSB;
uint8_t Vis_LSB;
uint16_t vis_lux;

uint8_t IR_MSB;
uint8_t IR_LSB;
uint16_t ir_lux;

/*
 * Function: Init_SunSensor
 * ------------------------
 * Initializes the SunSensor by performing the following steps:
 * 1. Checks if the I2C device is open and accessible.
 * 2. Verifies the device ID by reading from the appropriate register.
 * 3. Configures the sensor with predefined settings.
 *
 * Returns:
 *  - true if the initialization is successful.
 *  - false if there is an error in accessing or configuring the sensor.
 */
bool Init_SunSensor()
{
    uint8_t data;

    /* Check if the I2C device is open and accessible */
    if (is_i2c_device_open(SS_I2C_ADDR) == false)
        return false;

    /* Verify the device ID */
    read_sunsensor_byte_data(DEV_ID_REG, &data);
    if (data != SS_DEV_ID)
        return false;

    /* Configure the sensor with constant configuration settings */
    if (write_sunsensor_word(CONF_0, (uint16_t *)CONF_CONST) == false)
        return false;

    return true;
}

/*
 * Function: GetSunSensorVis_Lux
 * -----------------------------
 * Retrieves the visible light lux value from the SunSensor by:
 * 1. Reading a block of data starting from the ALS_DATA_REG register.
 * 2. Combining the most significant byte (MSB) and least significant
 *    byte (LSB) to form the 16-bit lux value.
 *
 * Returns:
 *  - The visible light lux value as a 16-bit unsigned integer.
 */
uint16_t GetSunSensorVis_Lux()
{
    uint8_t data[2];

    /* Read the visible light data block */
    read_sunsensor_block_data(ALS_DATA_REG, data);

    /* Split the data into MSB and LSB */
    Vis_LSB = data[0];
    Vis_MSB = data[1];

    /* Combine MSB and LSB to get the 16-bit lux value */
    vis_lux = ((Vis_MSB << 8) | Vis_LSB);

    return vis_lux;
}

/*
 * Function: GetSunSensorIR_Lux
 * ----------------------------
 * Retrieves the infrared light lux value from the SunSensor by:
 * 1. Reading a block of data starting from the IR_DATA_REG register.
 * 2. Combining the most significant byte (MSB) and least significant
 *    byte (LSB) to form the 16-bit lux value.
 *
 * Returns:
 *  - The infrared light lux value as a 16-bit unsigned integer.
 */
uint16_t GetSunSensorIR_Lux()
{
    uint8_t data[2];

    /* Read the infrared light data block */
    read_sunsensor_block_data(IR_DATA_REG, data);

    /* Split the data into MSB and LSB */
    IR_LSB = data[0];
    IR_MSB = data[1];

    /* Combine MSB and LSB to get the 16-bit lux value */
    ir_lux = (IR_MSB << 8) | IR_LSB;

    return ir_lux;
}
