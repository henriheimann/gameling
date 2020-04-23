#pragma once

#include "piezo_buzzer/piezo_buzzer.h"
#include "sfx_renderer/sfx_renderer.h"
#include "gfx_renderer/gfx_renderer.h"
#include "pca9685/pca9685.h"
#include "pcd8544/pcd8544.h"
#include "io_manager/io_manager.h"
#include "resources.h"
#include "executables/executable.h"

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

/**
 * Application main called by the STM32Cube init code.
 */
void application_main();

/**
 * Forces a change of the current executable.
 * @param executable The new executable to run.
 */
void application_switch_executable(executable_t *executable);
