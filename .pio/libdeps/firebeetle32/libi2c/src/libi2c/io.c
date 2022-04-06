#include <driver/i2c.h>

#include "private.h"

#define ADDR_GENERAL_CALL_RESET 0x00
#define CMD_GENERAL_CALL_RESET 0x06

void i2c_7bit_general_call_reset(i2c_port_t port) {
    // Note that there is also a software reset method via the configuration
    // register, instead of via a general call.

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ADDR_GENERAL_CALL_RESET | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, CMD_GENERAL_CALL_RESET, true);
    i2c_master_stop(cmd);

    ESP_ERROR_CHECK(i2c_master_cmd_begin(port, cmd, 1000 / portTICK_RATE_MS));
    i2c_cmd_link_delete(cmd);
}

void i2c_7bit_init(i2c_port_t port, uint8_t addr, i2c_7bit_handle_t* out_dev) {
    assert(!(addr & 0x80));

    i2c_7bit_handle_t dev = malloc(sizeof(i2c_7bit_t));
    dev->addr = addr;
    dev->port = port;

    *out_dev = dev;
}

void i2c_7bit_destroy(i2c_7bit_handle_t dev) {
    free(dev);
}

esp_err_t i2c_7bit_reg_read(i2c_7bit_handle_t dev, uint8_t reg, size_t count, uint8_t* data) {
    assert(count);

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (((uint8_t) dev->addr) << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, ((uint8_t) reg), true);
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (((uint8_t) dev->addr) << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, count, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(dev->port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

esp_err_t i2c_7bit_reg_write(i2c_7bit_handle_t dev, uint8_t reg, size_t count, const uint8_t* data) {
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (((uint8_t) dev->addr) << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, ((uint8_t) reg), true);
    if (count) {
        i2c_master_write(cmd, data, count, true);
    }
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(dev->port, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}
