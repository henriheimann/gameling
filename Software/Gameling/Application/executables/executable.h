#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef void (*executable_init_function)();
typedef void (*executable_update_function)(uint32_t elapsed_ticks);
typedef void (*executable_deinit_function)();

typedef struct {

    executable_init_function init_function;

    executable_update_function update_function;

    executable_deinit_function deinit_function;

} executable_t;