/************************************************************************
 *
 * Copyright (c) 2024 TakeMe2Space as represented by the
 * TakeMe2Space. All Rights Reserved.
 *
 ************************************************************************/


/*
 * sunsense.c
 * 
 * This file provides higher-level functionality for interacting with the TM2S
 * SunSensor device (Model: TM2S-SS1) over I2C. It includes initialization of the sensor
 * and methods to retrieve visible light and infrared light lux readings.
 */


#include "sunsense.h"

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
    if (!is_i2c_device_open(SS_I2C_ADDR))
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
    /* Combine MSB and LSB to get the 16-bit lux value */
    return ((data[1] << 8) | data[0]);
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
    /* Combine MSB and LSB to get the 16-bit lux value */
    return ((data[1] << 8) | data[0]);
}
