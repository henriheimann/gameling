#include "gfx_font.h"

int gfx_font_get_char_index(gfx_font_t *font, char c)
{
    int index = 0;
    const char *char_ptr = font->charset;

    while (*char_ptr) {
        if (*char_ptr == c) {
            return index;
        } else {
            char_ptr++;
            index++;
        }
    }

    return -1;
}