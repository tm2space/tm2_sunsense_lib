/************************************************************************
 *
 * Copyright (c) 2024 TakeMe2Space as represented by the
 * All Rights Reserved.
 *
 ************************************************************************/

#include "i2c_functions.h"

const char I2C_BUS_STR[12] = "/dev/i2c-1\0";

int32_t sunsensor_fd = 0;

void _reset_sunsensor_fd()
{
    sunsensor_fd = 0;
}

void _open_i2c_fd()
{
    if ((sunsensor_fd = open(I2C_BUS_STR, O_RDWR)) < 0)

    {
        printf("failed to open sunsensor fd [%s].\n", I2C_BUS_STR);
        sunsensor_fd = 0;
    }
}

bool is_i2c_device_open(uint8_t sensor_addr)
{

    _reset_sunsensor_fd(sunsensor_fd);
    _open_i2c_fd(sunsensor_fd);

    if (sunsensor_fd > 0)
    {
        if (ioctl(sunsensor_fd, I2C_SLAVE, sensor_addr) == -1)
            return false;
    }

    return true;
}

void read_sunsensor_byte_data(uint8_t sensor_reg, uint8_t *sensor_data)
{
    if (sunsensor_fd > 0)
        sensor_data = (uint8_t *)i2c_smbus_read_byte_data(sunsensor_fd, sensor_reg);
}

bool read_sunsensor_block_data(uint8_t sensor_reg, uint8_t *sensor_data)
{

    if (sunsensor_fd > 0)
    {
        if (i2c_smbus_write_byte(sunsensor_fd, sensor_reg) <= 0)
        {
            return false;
        }

        if (i2c_smbus_read_i2c_block_data(sunsensor_fd, sensor_reg, BYTES_TO_READ, (unsigned char *)sensor_data) != BYTES_TO_READ)
        {
            printf("Error SunSensor: I2C read register error\n");
            return false;
        }
    }

    return true;
}

bool write_sunsensor_word(uint8_t sensor_reg, uint16_t *sensor_data)
{
    if (sunsensor_fd > 0)
    {

        if (i2c_smbus_write_word_data(sunsensor_fd, sensor_reg, *sensor_data) < 0)

        {
            printf("Error SunSensor: write register error\n");
            return false;
        }
    }

    return true;
}
