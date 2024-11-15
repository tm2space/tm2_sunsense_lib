/************************************************************************
 *
 * Copyright (c) 2024 TakeMe2Space as represented by the
 * All Rights Reserved.
 *
 ************************************************************************/

/*
 * sunsensor_i2c.c
 * 
 * This file provides an interface to communicate with a SunSensor device
 * over the I2C protocol. It includes functions to handle basic I2C
 * operations such as opening/closing the device file, checking device
 * connectivity, reading from and writing to registers, and block data
 * transfers.
 */

#include "i2c_functions.h"

/* 
 * Constant for I2C bus device file. 
 * "/dev/i2c-1" is typically used for I2C communications on most Linux platforms.
 */
const char I2C_BUS_STR[12] = "/dev/i2c-1\0";

/* 
 * Global file descriptor for the I2C device. 
 * Initialized to 0 to indicate it is not open.
 */
int32_t sunsensor_fd = 0;

/*
 * Function: _reset_sunsensor_fd
 * -----------------------------
 * Resets the global file descriptor for the SunSensor to 0.
 * This indicates that the I2C device file is closed or uninitialized.
 */
void _reset_sunsensor_fd()
{
    sunsensor_fd = 0;
}

/*
 * Function: _open_i2c_fd
 * ----------------------
 * Opens the I2C device file and assigns the file descriptor to `sunsensor_fd`.
 * If the file cannot be opened, it prints an error message and resets the descriptor.
 */
void _open_i2c_fd()
{
    if ((sunsensor_fd = open(I2C_BUS_STR, O_RDWR)) < 0)
    {
        printf("failed to open sunsensor fd [%s].\n", I2C_BUS_STR);
        sunsensor_fd = 0;
    }
}

/*
 * Function: is_i2c_device_open
 * ----------------------------
 * Checks if the SunSensor device is accessible by performing the following steps:
 * 1. Resets the file descriptor.
 * 2. Opens the I2C device file.
 * 3. Uses ioctl to set the slave address for communication.
 *
 * Parameters:
 *  - sensor_addr: I2C address of the SunSensor.
 *
 * Returns:
 *  - true if the device is accessible.
 *  - false if there is an error in accessing the device.
 */
bool is_i2c_device_open(uint8_t sensor_addr)
{
    _reset_sunsensor_fd();
    _open_i2c_fd();

    if (sunsensor_fd > 0)
    {
        if (ioctl(sunsensor_fd, I2C_SLAVE, sensor_addr) == -1)
            return false;
    }

    return true;
}

/*
 * Function: read_sunsensor_byte_data
 * ----------------------------------
 * Reads a single byte of data from a specific register of the SunSensor.
 *
 * Parameters:
 *  - sensor_reg: Register address to read from.
 *  - sensor_data: Pointer to store the byte read from the register.
 *
 * Note:
 *  - Ensure `sunsensor_fd` is valid before calling this function.
 */
void read_sunsensor_byte_data(uint8_t sensor_reg, uint8_t *sensor_data)
{
    if (sunsensor_fd > 0)
        sensor_data = (uint8_t *)i2c_smbus_read_byte_data(sunsensor_fd, sensor_reg);
}

/*
 * Function: read_sunsensor_block_data
 * -----------------------------------
 * Reads a block of data from the SunSensor starting from a specified register.
 *
 * Parameters:
 *  - sensor_reg: Starting register address to read from.
 *  - sensor_data: Pointer to store the block of data.
 *
 * Returns:
 *  - true if the block data was successfully read.
 *  - false if there was an error during the operation.
 *
 */
bool read_sunsensor_block_data(uint8_t sensor_reg, uint8_t *sensor_data)
{
    if (sunsensor_fd <= 0)
    {
        return false;
    }
    if (i2c_smbus_write_byte(sunsensor_fd, sensor_reg) <= 0)
    {
        return false;
    }

    if (i2c_smbus_read_i2c_block_data(sunsensor_fd, sensor_reg, BYTES_TO_READ, (unsigned char *)sensor_data) != BYTES_TO_READ)
    {
        printf("Error SunSensor: I2C read register error\n");
        return false;
    }
    return true;
}

/*
 * Function: write_sunsensor_word
 * ------------------------------
 * Writes a 16-bit word to a specific register of the SunSensor.
 *
 * Parameters:
 *  - sensor_reg: Register address to write to.
 *  - sensor_data: Pointer to the 16-bit data to be written.
 *
 * Returns:
 *  - true if the word was successfully written.
 *  - false if there was an error during the operation.
 */
bool write_sunsensor_word(uint8_t sensor_reg, uint16_t *sensor_data)
{
    if (sunsensor_fd <= 0)
    {
        return false;
    }
    if (i2c_smbus_write_word_data(sunsensor_fd, sensor_reg, *sensor_data) < 0)
    {
        printf("Error SunSensor: write register error\n");
        return false;
    }

    return true;
}
