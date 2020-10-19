#include "gfx_renderer.h"
#include "gfx_texture.h"

#include <stdlib.h>

static void gfx_renderer_set_pixel(gfx_renderer_t *renderer, uint8_t x, uint8_t y, uint8_t color) {
    renderer->set_pixel_function(renderer->function_data, x, y, color);
}

void gfx_renderer_draw_line(gfx_renderer_t *renderer, uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, uint8_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int error = (dx > dy ? dx : -dy) / 2;

    while (1) {

        gfx_renderer_set_pixel(renderer, x0, y0, color);

        if (x0 == x1 && y0 == y1) {
            break;
        }

        int current_error = error;

        if (current_error > -dx) {
            error -= dy;
            x0 += sx;
        }
        if (current_error < dy) {
            error += dx;
            y0 += sy;
        }
    }
}

static void eight_way_symmetric_plot(gfx_renderer_t *renderer, int center_x, int center_y, int offset_x, int offset_y, uint8_t color)
{
    gfx_renderer_set_pixel(renderer, center_x + offset_x, center_y + offset_y, color);
    gfx_renderer_set_pixel(renderer, center_x + offset_x, center_y - offset_y, color);
    gfx_renderer_set_pixel(renderer, center_x - offset_x, center_y - offset_y, color);
    gfx_renderer_set_pixel(renderer, center_x - offset_x, center_y + offset_y, color);
    gfx_renderer_set_pixel(renderer, center_x + offset_y, center_y + offset_x, color);
    gfx_renderer_set_pixel(renderer, center_x + offset_y, center_y - offset_x, color);
    gfx_renderer_set_pixel(renderer, center_x - offset_y, center_y - offset_x, color);
    gfx_renderer_set_pixel(renderer, center_x - offset_y, center_y + offset_x, color);
}

void gfx_renderer_draw_circle(gfx_renderer_t *renderer, uint8_t center_x, uint8_t center_y, uint8_t radius, uint8_t color)
{
    int offset_x = 0;
    int offset_y = radius;
    int d = 3 - (2 * radius);

    eight_way_symmetric_plot(renderer, center_x, center_y, offset_x, offset_y, color);

    while (offset_x <= offset_y) {
        if (d <= 0) {
            d = d + (4 * offset_x) + 6;
        } else {
            d = d + (4 * offset_x) - (4 * offset_y) + 10;
            offset_y--;
        }
        offset_x++;
        eight_way_symmetric_plot(renderer, center_x, center_y, offset_x, offset_y, color);
    }
}

void gfx_renderer_draw_rect(gfx_renderer_t *renderer, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color)
{
    gfx_renderer_draw_line(renderer, x, y, x + width - 1, y, color);
    gfx_renderer_draw_line(renderer, x + width - 1, y, x + width - 1, y + height - 1, color);
    gfx_renderer_draw_line(renderer, x + width - 1, y + height - 1, x, y + height - 1, color);
    gfx_renderer_draw_line(renderer, x, y + height - 1, x, y, color);
}

void gfx_renderer_fill_rect(gfx_renderer_t *renderer, uint8_t x, uint8_t y, uint8_t width, uint8_t height, uint8_t color)
{
    for (uint8_t xx = x; xx < x + width; xx++) {
        for (uint8_t yy = y; yy < y + height; yy++) {
            gfx_renderer_set_pixel(renderer, xx, yy, color);
        }
    }
}

void gfx_renderer_draw_texture(gfx_renderer_t *renderer, gfx_texture_t *texture, uint8_t x, uint8_t y)
{
    gfx_renderer_draw_sub_texture(renderer, texture, 0, 0, texture->width, texture->height, x, y, true);
}

void gfx_renderer_draw_sub_texture(gfx_renderer_t *renderer, gfx_texture_t *texture, uint8_t texture_x, uint8_t texture_y, uint8_t width, uint8_t height, uint8_t screen_x, uint8_t screen_y, bool opaque)
{
    for (uint16_t y = 0; y < height; y++) {
        for (uint16_t x = 0; x < width; x++)  {
            uint8_t color = gfx_texture_get_color(texture, texture_x + x, texture_y + y);
            if (opaque || color) {
                gfx_renderer_set_pixel(renderer, screen_x + x, screen_y + y, color);
            }
        }
    }
}

void gfx_renderer_draw_text(gfx_renderer_t *renderer, gfx_font_t *font, uint8_t x, uint8_t y, const char *text)
{
    int offset_x = x;
    int offset_y = y;

    while (*text) {

        if (*text == '\n') {
            offset_x = 0;
            offset_y += font->char_height + font->line_spacing;

        } else {

            int index = gfx_font_get_char_index(font, *text);

            if (index != -1) {
                uint8_t texture_offset_x = index * font->char_width;
                gfx_renderer_draw_sub_texture(renderer, font->texture, texture_offset_x, 0, font->char_width,
                                              font->char_height, offset_x, offset_y, false);
                offset_x += font->char_width + font->char_spacing;
            }
        }

        text++;
    }
}

void gfx_renderer_update(gfx_renderer_t *renderer)
{
    renderer->update_display_function(renderer->function_data);
}