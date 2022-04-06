#ifndef __LIB_LIBESP_H
#define __LIB_LIBESP_H

#include <stdint.h>

// DANGER: `micros` should be small to avoid WDT triggers.
void util_wait_micros(int64_t micros);

void util_wait_for_keypress();

void util_log_idf_version();

void util_print_stack_remaining();

#endif