#pragma once

#include "piezo_buzzer/piezo_buzzer.h"
#include "sfx_renderer/sfx_renderer.h"
#include "gfx_renderer/gfx_renderer.h"
#include "pca9685/pca9685.h"
#include "pcd8544/pcd8544.h"
#include "io_manager/io_manager.h"
#include "resources.h"

// Handles to the hardware peripherals.
extern piezo_buzzer_handle_t piezo_handle;
extern pca9685_handle_t pca9685_handle;
extern pcd8544_handle_t pcd8544_handle;

// Handle to hardware abstractions.
extern sfx_renderer_t sfx_renderer;
extern gfx_renderer_t gfx_renderer;
extern io_manager_t io_manager;

// Global fonts and textures.
extern gfx_font_t font;

void application_main();