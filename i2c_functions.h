/************************************************************************
 *
 * Copyright (c) 2024 TakeMe2Space as represented by the
 * All Rights Reserved.
 *
 ************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <i2c/smbus.h>
#include <fcntl.h>

#ifndef I2C_FUNCTIONS_H
#define I2C_FUNCTIONS_H

/* 
 * Macro defining the number of bytes to read for block operations.
 * Default value is set to 2.
 */


#define BYTES_TO_READ 2

void _reset_sunsensor_fd();
void _open_i2c_fd();

bool is_i2c_device_open(uint8_t sensor_addr);

void read_sunsensor_byte_data(uint8_t sensor_reg, uint8_t *sensor_data);
bool read_sunsensor_block_data(uint8_t sensor_reg, uint8_t *sensor_data);

bool write_sunsensor_word(uint8_t sensor_reg, uint16_t *sensor_data);

#endif /* I2C_FUNCTIONS */