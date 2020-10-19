#include "executables/exec_intro.h"
#include "application.h"

#include "i2c.h"
#include "spi.h"
#include "tim.h"

piezo_buzzer_handle_t piezo_handle = {
		.timer_handle = &htim1,
		.timer_channel = TIM_CHANNEL_3,
		.is_n_channel = true,
		.timer_frequency = 500000
};

pca9685_handle_t pca9685_handle = {
		.i2c_handle = &hi2c1,
		.device_address = PCA9865_I2C_DEFAULT_DEVICE_ADDRESS,
		.inverted = true
};

pcd8544_handle_t pcd8544_handle = {
        .spi_handle = &hspi1,
        .nsce_port = NOKIA5110_NSCE_GPIO_Port,
        .nsce_pin = NOKIA5110_NSCE_Pin,
        .dnc_port = NOKIA5110_DNC_GPIO_Port,
        .dnc_pin = NOKIA5110_DNC_Pin,
        .nrst_port = NOKIA5110_NRST_GPIO_Port,
        .nrst_pin = NOKIA5110_NRST_Pin,
};

sfx_renderer_t sfx_renderer = {
        .start_sound_function = (sfx_renderer_start_sound_function_t)piezo_buzzer_start,
        .stop_sound_function = (sfx_renderer_stop_sound_function_t)piezo_buzzer_stop,
        .function_data = &piezo_handle
};

gfx_renderer_t gfx_renderer = {
        .set_pixel_function = (gfx_renderer_set_pixel_function_t)pcd8544_set_pixel,
        .update_display_function = (gfx_renderer_update_display_function)pcd8544_update,
        .function_data = &pcd8544_handle
};

io_manager_t io_manager = {
        .pca9685_handle = &pca9685_handle,
        .led_buttons = {
                { BUTTON_1_GPIO_Port, BUTTON_1_Pin, 4, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_2_GPIO_Port, BUTTON_2_Pin, 7, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_3_GPIO_Port, BUTTON_3_Pin, 10, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_4_GPIO_Port, BUTTON_4_Pin, 3, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_5_GPIO_Port, BUTTON_5_Pin, 0, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_6_GPIO_Port, BUTTON_6_Pin, 11, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_7_GPIO_Port, BUTTON_7_Pin, 2, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_8_GPIO_Port, BUTTON_8_Pin, 14, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_9_GPIO_Port, BUTTON_9_Pin, 12, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_10_GPIO_Port, BUTTON_10_Pin, 1, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_11_GPIO_Port, BUTTON_11_Pin, 15, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
                { BUTTON_12_GPIO_Port, BUTTON_12_Pin, 13, 0.0f, 0.0f, 1.0f, 0, 0, 0, false },
        },
        .display_leds = {
                { 6, 0.0f, true },
                { 5, 0.0f, true },
                { 9, 0.0f, true },
                { 8, 0.0f, true },
        }
};

static gfx_texture_t font_texture;
gfx_font_t font = {
        .charset = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.!-? <>:",
        .char_width = 5,
        .char_height = 7,
        .line_spacing = 1,
        .char_spacing = 1,
        .texture = &font_texture,
};

static executable_t *current_executable = NULL;

static void load_global_data()
{
    // Load global textures
    gfx_texture_load_pcx(&font_texture, font_pcx, sizeof(font_pcx));
}

void application_main()
{
    // Initialise peripherals
	pca9685_init(&pca9685_handle);
    pcd8544_init(&pcd8544_handle);

    // Load global data
    load_global_data();

    // Start the with intro executable
    application_switch_executable(&exec_intro);

    uint32_t last_tick = HAL_GetTick();
    uint32_t current_tick;

	while (1) {

        current_tick = HAL_GetTick();
	    uint32_t elapsed_ticks = (current_tick - last_tick);

		if (elapsed_ticks > 0) {
            last_tick = current_tick;

            // Perform updates for all systems
            sfx_renderer_update(&sfx_renderer, elapsed_ticks);
            io_manager_update(&io_manager, elapsed_ticks);
            gfx_renderer_update(&gfx_renderer);

            // Call current executable update function
            if (current_executable != NULL) {
                current_executable->update_function(elapsed_ticks);
            }
		}
	}
}

void application_switch_executable(executable_t *executable)
{
    if (current_executable != executable) {

        // Deinit old executable if there was one.
        if (current_executable != NULL) {
            current_executable->deinit_function();
        }

        current_executable = executable;

        current_executable->init_function();
    }
}