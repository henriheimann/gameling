#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef enum {
    GFX_TEXTURE_TYPE_1BIT
} gfx_texture_type_t;

typedef struct {

    uint16_t width;

    uint16_t height;

    gfx_texture_type_t type;

    uint8_t *data;

    size_t data_size;

} gfx_texture_t;

bool gfx_texture_load_pcx(gfx_texture_t *texture, const uint8_t *pcx_data, size_t pcx_data_size);

uint8_t gfx_texture_get_color(gfx_texture_t *texture, uint16_t x, uint16_t y);