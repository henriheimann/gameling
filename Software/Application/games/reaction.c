#include "reaction.h"
#include "application.h"

#include <stdio.h>

#define BUTTONS_TO_PRESS_COUNT 50

typedef enum {
    GAME_REACTION_STATE_START,
    GAME_REACTION_STATE_COUNTDOWN_3,
    GAME_REACTION_STATE_COUNTDOWN_2,
    GAME_REACTION_STATE_COUNTDOWN_1,
    GAME_REACTION_STATE_PLAYING,
    GAME_REACTION_STATE_FINAL_WALL,
    GAME_REACTION_STATE_SHOW_TIME
} game_reaction_state;

static game_reaction_state state;

static uint8_t button_indices[BUTTONS_TO_PRESS_COUNT] = {
        1,	8,	5,	1,	2,
        8,	7,	10,	9,	6,
        4,	0,	4,	6,	3,
        1,	8,	0,	6,	1,
        8,	0,	5,	4,	2,
        10,	0,	8,	5,	4,
        3,	1,	3,	5,	6,
        3,	0,	1,	0,	0,
        10,	7,	4,	2,	4,
        11,	7,	2,	6,	2
};

static uint16_t current_index = 0;

void game_init_function()
{
    io_manager_set_display_brightness(&io_manager, 0.3f);
}

void game_update_function(uint32_t elapsed_ticks)
{
    uint32_t total_ticks = HAL_GetTick();
    int tenth_of_seconds = (total_ticks / 100);
    int seconds = (tenth_of_seconds / 10);
    int minutes = (seconds / 60);

    seconds %= 60;
    tenth_of_seconds %= 10;

    char buffer[11];
    sprintf(buffer, "%02d:%02d.%01d", minutes, seconds, tenth_of_seconds);

    gfx_renderer_fill_rect(&gfx_renderer, 0, 0, 48, 7, 0);
    gfx_renderer_draw_text(&gfx_renderer, &font, 0, 0, buffer);

    io_manager_set_button_brightness(&io_manager, button_indices[current_index], 0.2f);

    if (io_manager_get_button_state(&io_manager, button_indices[current_index])) {
        io_manager_set_button_brightness(&io_manager, button_indices[current_index], 0.0f);
        current_index++;
        if (current_index == 50) {
            current_index = 0;
        }
    }
}