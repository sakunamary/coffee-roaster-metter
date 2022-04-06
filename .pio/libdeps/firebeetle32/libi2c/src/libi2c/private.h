#ifndef __LIB__LIBI2C_PRIVATE_H
#define __LIB__LIBI2C_PRIVATE_H

#include <driver/i2c.h>

#include "libi2c.h"

struct i2c_7bit {
    i2c_port_t port;
    uint8_t addr;
};

#endif
