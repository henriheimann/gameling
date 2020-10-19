#include "exec_menu.h"
#include "game_reaction.h"

#include <gfx_renderer/gfx_texture.h>
#include <resources.h>
#include <application.h>

#define AVAILABLE_GAMES_COUNT       2

static struct
{
    gfx_texture_t texture;
    executable_t *executable;
}
available_games[AVAILABLE_GAMES_COUNT] =
{
    {
        .executable = &game_reaction
    },
    {
        .executable = &game_reaction
    }
};

static size_t current_game_index = 0;

static void switch_game(size_t new_game_index)
{
    uint16_t current_texture_width = available_games[current_game_index].texture.width;
    uint16_t current_texture_height = available_games[current_game_index].texture.height;
    uint16_t current_texture_x = 42 - current_texture_width / 2;
    uint16_t current_texture_y = 18 - current_texture_height / 2;

    gfx_renderer_fill_rect(&gfx_renderer, current_texture_x, current_texture_y, current_texture_width,
            current_texture_height, PCD8544_COLOR_WHITE);

    current_game_index = new_game_index;

    current_texture_width = available_games[current_game_index].texture.width;
    current_texture_height = available_games[current_game_index].texture.height;
    current_texture_x = 42 - current_texture_width / 2;
    current_texture_y = 18 - current_texture_height / 2;

    gfx_renderer_draw_texture(&gfx_renderer, &available_games[current_game_index].texture, current_texture_x,
            current_texture_y);
}

static void init_function()
{
    gfx_texture_load_pcx(&available_games[0].texture, thewall_pcx, sizeof(thewall_pcx));
    gfx_texture_load_pcx(&available_games[1].texture, placeholder_pcx, sizeof(placeholder_pcx));

    gfx_renderer_fill_rect(&gfx_renderer, 0, 0, 84, 48, PCD8544_COLOR_WHITE);

    io_manager_set_button_brightness(&io_manager, 0, 0.1f);
    io_manager_set_button_brightness(&io_manager, 1, 0.1f);
    io_manager_set_button_brightness(&io_manager, 2, 0.1f);

    gfx_renderer_draw_rect(&gfx_renderer, 0, 37, 16, 11, PCD8544_COLOR_BLACK);
    gfx_renderer_draw_rect(&gfx_renderer, 68, 37, 16, 11, PCD8544_COLOR_BLACK);
    gfx_renderer_draw_text(&gfx_renderer, &font, 5, 39, "<");
    gfx_renderer_draw_text(&gfx_renderer, &font, 74, 39, ">");

    current_game_index = 0;

    uint16_t current_texture_width = available_games[current_game_index].texture.width;
    uint16_t current_texture_height = available_games[current_game_index].texture.height;
    uint16_t current_texture_x = 42 - current_texture_width / 2;
    uint16_t current_texture_y = 18 - current_texture_height / 2;

    gfx_renderer_draw_texture(&gfx_renderer, &available_games[current_game_index].texture, current_texture_x,
                              current_texture_y);
}

static uint32_t blink_time_elapsed = 0;
static int state = 0;

static void update_function(uint32_t elapsed_ticks)
{
    blink_time_elapsed += elapsed_ticks;

    if (blink_time_elapsed > 400) {
        if (state == 0) {
            gfx_renderer_draw_rect(&gfx_renderer, 25, 37, 35, 11, PCD8544_COLOR_BLACK);
            gfx_renderer_draw_text(&gfx_renderer, &font, 28, 39, "START");

            state = 1;

        } else if (state == 1) {
            gfx_renderer_fill_rect(&gfx_renderer, 25, 37, 35, 11, PCD8544_COLOR_WHITE);

            state = 0;
        }
        blink_time_elapsed -= 400;
    }

    if (io_manager_get_button_clicked(&io_manager, 0)) {
        if (current_game_index == 0) {
            switch_game(AVAILABLE_GAMES_COUNT - 1);
        } else {
            switch_game(current_game_index - 1);
        }
    }

    if (io_manager_get_button_clicked(&io_manager, 2)) {
        if (current_game_index == AVAILABLE_GAMES_COUNT - 1) {
            switch_game(0);
        } else {
            switch_game(current_game_index + 1);
        }
    }
}

static void deinit_function()
{
    for (size_t game_index = 0; game_index < AVAILABLE_GAMES_COUNT; game_index++) {
        gfx_texture_destroy(&available_games[game_index].texture);
    }
}

executable_t exec_menu = {
        .init_function = init_function,
        .update_function = update_function,
        .deinit_function = deinit_function
};