#pragma once

#include <stdint.h>
#include <stddef.h>

#include "gfx_texture.h"

typedef struct {

    const char *charset;

    size_t num_characters;

    uint8_t char_width;

    uint8_t char_height;

    uint8_t char_spacing;

    uint8_t line_spacing;

    gfx_texture_t *texture;

} gfx_font_t;

int gfx_font_get_char_index(gfx_font_t *font, char c);