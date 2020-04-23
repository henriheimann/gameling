#include "exec_intro.h"
#include "game_reaction.h"

#include <gfx_renderer/gfx_texture.h>
#include <resources.h>
#include <gfx_renderer/gfx_renderer.h>
#include <application.h>

static gfx_texture_t logo_texture;

static uint32_t total_elapsed_ticks;

static void init_function()
{
    gfx_texture_load_pcx(&logo_texture, logo_pcx, sizeof(logo_pcx));
    sfx_renderer_play_note(&sfx_renderer, SFX_RENDERER_NOTE_E4, 1000);
}

static void update_function(uint32_t elapsed_ticks)
{
    total_elapsed_ticks += elapsed_ticks;

    gfx_renderer_draw_texture(&gfx_renderer, &logo_texture, 12, 17);

    if (total_elapsed_ticks > 1000) {
        application_switch_executable(&game_reaction);
    }
}

static void deinit_function()
{
    gfx_texture_destroy(&logo_texture);
}

executable_t exec_intro = {
    .init_function = init_function,
    .update_function = update_function,
    .deinit_function = deinit_function
};