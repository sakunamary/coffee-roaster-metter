#ifndef __LIB_LIBI2C_H
#define __LIB_LIBI2C_H

#include <driver/i2c.h>
#include <esp_err.h>
#include <stddef.h>

typedef struct i2c_7bit i2c_7bit_t;
typedef i2c_7bit_t* i2c_7bit_handle_t;

// Issue a general call reset (to all connected devices which support the command) on the given I2C port.
void i2c_7bit_general_call_reset(i2c_port_t port);

// Register a I2C device on the given I2C port.
void i2c_7bit_init(i2c_port_t port, uint8_t addr, i2c_7bit_handle_t* out_dev);

// Release the given handle.
void i2c_7bit_destroy(i2c_7bit_handle_t dev);

// Read a register `count` bytes to a register over I2C.
esp_err_t i2c_7bit_reg_read(i2c_7bit_handle_t dev, uint8_t reg, size_t count, uint8_t* data);

// Write `count` bytes to a register over I2C.
esp_err_t i2c_7bit_reg_write(i2c_7bit_handle_t dev, uint8_t reg, size_t count, const uint8_t* data);

#endif
