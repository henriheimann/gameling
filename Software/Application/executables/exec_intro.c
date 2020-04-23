#include "exec_intro.h"
#include "game_reaction.h"

#include <gfx_renderer/gfx_texture.h>
#include <resources.h>
#include <gfx_renderer/gfx_renderer.h>
#include <application.h>

static gfx_texture_t logo_texture;

static uint32_t total_elapsed_ticks;

static sfx_renderer_segment_t segments[] = {
        { SFX_RENDERER_NOTE_A2, 187 },
        { SFX_RENDERER_PAUSE, 63 },
        { SFX_RENDERER_NOTE_E3, 187 },
        { SFX_RENDERER_PAUSE, 63 },
        { SFX_RENDERER_NOTE_D3, 187 },
        { SFX_RENDERER_PAUSE, 63 },
        { SFX_RENDERER_NOTE_G3, 187 },
        { SFX_RENDERER_PAUSE, 63 },
        { SFX_RENDERER_NOTE_A3, 300 }
};

static sfx_renderer_song_t song = {
        .num_segments = 9,
        .segments = segments
};

static int state = 0;

static void init_function()
{
    gfx_texture_load_pcx(&logo_texture, logo_pcx, sizeof(logo_pcx));
    sfx_renderer_play_song(&sfx_renderer, &song, false);
}

static void update_function(uint32_t elapsed_ticks)
{
    total_elapsed_ticks += elapsed_ticks;

    if (state == 0 && total_elapsed_ticks > 100) {
        io_manager_set_button_brightness(&io_manager, 9, 0.05f);
        io_manager_set_button_brightness(&io_manager, 10, 0.05f);
        io_manager_set_button_brightness(&io_manager, 11, 0.05f);
        state = 1;
    }

    if (state == 1 && total_elapsed_ticks > 300) {
        io_manager_set_button_brightness(&io_manager, 6, 0.05f);
        io_manager_set_button_brightness(&io_manager, 7, 0.05f);
        io_manager_set_button_brightness(&io_manager, 8, 0.05f);
        state = 2;
    }

    if (state == 2 && total_elapsed_ticks > 500) {
        io_manager_set_button_brightness(&io_manager, 3, 0.05f);
        io_manager_set_button_brightness(&io_manager, 4, 0.05f);
        io_manager_set_button_brightness(&io_manager, 5, 0.05f);
        state = 3;
    }

    if (state == 3 && total_elapsed_ticks > 700) {
        io_manager_set_button_brightness(&io_manager, 0, 0.05f);
        io_manager_set_button_brightness(&io_manager, 1, 0.05f);
        io_manager_set_button_brightness(&io_manager, 2, 0.05f);
        state = 4;
    }

    if (state == 4 && total_elapsed_ticks > 900) {
        io_manager_set_display_brightness(&io_manager, 0.5f);
        io_manager_set_all_button_brightnesses(&io_manager, 0.2f);
        gfx_renderer_draw_texture(&gfx_renderer, &logo_texture, 12, 17);
        state = 5;
    }

    if (total_elapsed_ticks > 2000) {
        application_switch_executable(&game_reaction);
    }
}

static void deinit_function()
{
    gfx_texture_destroy(&logo_texture);
    io_manager_set_all_button_brightnesses(&io_manager, 0.0f);
}

executable_t exec_intro = {
    .init_function = init_function,
    .update_function = update_function,
    .deinit_function = deinit_function
};