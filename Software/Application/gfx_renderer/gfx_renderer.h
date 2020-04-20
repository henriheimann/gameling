#pragma once

#include "gfx_texture.h"
#include "gfx_font.h"

#include <stdint.h>

typedef void (*gfx_renderer_set_pixel_function_t)(void *data, uint8_t x, uint8_t y, uint8_t color);
typedef void (*gfx_renderer_update_display_function)(void *data);

typedef struct {

    /**
     * Function data required by the set pixel and update display functions.
     */
    void *function_data;

    /**
     * The function used to set a specific pixel on the display.
     */
	gfx_renderer_set_pixel_function_t set_pixel_function;

	/**
	 * The function used to update the display to the actual updated pixels.
	 */
    gfx_renderer_update_display_function update_display_function;

} gfx_renderer_t;

void gfx_renderer_draw_line(gfx_renderer_t *renderer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color);

void gfx_renderer_draw_circle(gfx_renderer_t *renderer, uint8_t center_x, uint8_t center_y, uint8_t radius, uint8_t color);

void gfx_renderer_draw_rect(gfx_renderer_t *renderer, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);

void gfx_renderer_fill_rect(gfx_renderer_t *renderer, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color);

void gfx_renderer_draw_texture(gfx_renderer_t *renderer, gfx_texture_t *texture, uint8_t x, uint8_t y);

void gfx_renderer_draw_sub_texture(gfx_renderer_t *renderer, gfx_texture_t *texture, uint8_t texture_x, uint8_t texture_y, uint8_t width, uint8_t height, uint8_t screen_x, uint8_t screen_y, bool opaque);

void gfx_renderer_draw_text(gfx_renderer_t *renderer, gfx_font_t *font, uint8_t x, uint8_t y, const char *text);

/**
 * Executes an update for the given GFX render.
 * @param gfx_renderer The GFX renderer to update.
 */
void gfx_renderer_update(gfx_renderer_t *gfx_renderer);