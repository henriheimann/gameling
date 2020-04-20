#include "gfx_texture.h"

#include <assert.h>
#include <stdlib.h>

typedef enum {
    PCX_COMPRESSION_NONE = 0,
    PCX_COMPRESSION_RLE = 1
} pcx_compression_t;

typedef struct __packed {

    uint8_t identification;

    uint8_t version;

    uint8_t compression;

    uint8_t bits_per_pixel;

    uint16_t min_x, min_y, max_x, max_y;

    uint16_t horizontal_dpi;

    uint16_t vertical_dpi;

    uint8_t color_map[48];

    uint8_t reserved;

    uint8_t number_of_planes;

    uint16_t bytes_per_row;

    uint16_t palette_information;

    uint16_t screen_width;

    uint16_t screen_height;

    uint8_t padding[54];

} pcx_header_t;

bool gfx_texture_load_pcx(gfx_texture_t *texture, const uint8_t *pcx_data, size_t pcx_data_size)
{
    const pcx_header_t *header = (pcx_header_t*)pcx_data;

    // Verify correct PCX file identification.
    if (header->identification != 0x0a) {
        return false;
    }

    // Verify supported number of colors.
    unsigned number_of_colors = (1u << (unsigned)(header->bits_per_pixel * header->number_of_planes));
    if (number_of_colors != 2) {
        return false;
    }

    // Verify origin in the upper left corner.
    if (header->min_x != 0 || header->min_y != 0) {
        return false;
    }

    texture->type = GFX_TEXTURE_TYPE_1BIT;
    texture->width = (header->bytes_per_row * 8) / header->bits_per_pixel;
    texture->height = header->max_y + 1;
    texture->data_size = texture->width * texture->height / 8;
    texture->data = malloc(texture->data_size);

    // Check for bad alloc.
    if (texture->data == NULL) {
        return false;
    }

    uint8_t *texture_data_ptr = texture->data;
    size_t texture_space_remaining = texture->data_size;

    const uint8_t *pcx_data_ptr = (pcx_data + sizeof(pcx_header_t));
    size_t pcx_data_remaining = pcx_data_size - sizeof(pcx_header_t);

    while (pcx_data_remaining) {

        unsigned run_length = 1;

        // If the file is RL encoded and this is RLE byte.
        if (header->compression == PCX_COMPRESSION_RLE && ((*pcx_data_ptr & 0b11000000u) == 0b11000000u)) {
            run_length = *pcx_data_ptr & 0b00111111u;

            // Move to next byte but return if no data is left.
            pcx_data_ptr++;
            pcx_data_remaining--;
            if (pcx_data_remaining == 0) {
                return false;
            }
        }

        uint8_t value = *pcx_data_ptr;
        pcx_data_ptr++;
        pcx_data_remaining--;

        for (unsigned i = 0; i < run_length; i++) {

            // Make sure space is left to store the next data byte.
            if (texture_space_remaining == 0) {
                return false;
            }

            *texture_data_ptr = value;
            texture_data_ptr++;
            texture_space_remaining--;
        }
    }

    return true;
}

uint8_t gfx_texture_get_color(gfx_texture_t *texture, uint16_t x, uint16_t y)
{
    assert(x < texture->width);
    assert(y < texture->height);
    assert(texture->type == GFX_TEXTURE_TYPE_1BIT);

    unsigned bit = 7 - (x % 8);
    unsigned index = x / 8 + y * (texture->width / 8);

    return ((unsigned)texture->data[index] >> bit) & 0x1u ? 0 : 1;
}
