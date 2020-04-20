#include "io_manager.h"

#include <stm32l4xx_hal.h>
#include <stdint.h>
#include <stdbool.h>

void io_manager_update(io_manager_t *io_manager, uint32_t elapsed_ticks)
{
    // Read button states and set button brightness if changed.
    for (int i = 0; i < IO_MANAGER_BUTTON_COUNT; i++) {

        led_button_t *led_button = &io_manager->led_buttons[i];

        // Read the current button state.
        led_button->current_state = (HAL_GPIO_ReadPin(led_button->button_port, led_button->button_pin) == GPIO_PIN_RESET);

        // LED blinking calculation.
        if (led_button->blinking_period > 0) {
            led_button->blinking_elapsed += elapsed_ticks;

            if (led_button->blinking_elapsed > led_button->blinking_period) {
                led_button->blinking_elapsed -= led_button->blinking_period;
            }

            if (led_button->blinking_elapsed < led_button->blinking_on_time) {
                led_button->requested_brightness = led_button->backup_brightness;
            } else {
                led_button->requested_brightness = 0.0f;
            }

        // With no blinking the requested brightness is the backup brightness.
        } else {
            led_button->requested_brightness = led_button->backup_brightness;
        }

        if (led_button->current_brightness != led_button->requested_brightness) {
            pca9685_set_channel_duty_cycle(io_manager->pca9685_handle, led_button->led_channel,
                                           led_button->requested_brightness, true);
            led_button->current_brightness = led_button->requested_brightness;
        }
    }

    // Set new display background LEDs if changed.
    for (int i = 0; i < IO_MANAGER_DISPLAY_LED_COUNT; i++) {
        if (io_manager->display_leds[i].brightness_changed) {
            pca9685_set_channel_duty_cycle(io_manager->pca9685_handle, io_manager->display_leds[i].led_channel,
                                           io_manager->display_leds[i].current_brightness, true);
            io_manager->display_leds[i].brightness_changed = false;
        }
    }
}

bool io_manager_get_button_state(io_manager_t *io_manager, uint8_t button_index)
{
    return io_manager->led_buttons[button_index].current_state;
}

void io_manager_set_button_brightness(io_manager_t *io_manager, uint8_t button_index, float brightness)
{
    if (io_manager->led_buttons[button_index].backup_brightness != brightness) {
        io_manager->led_buttons[button_index].blinking_period = 0;
        io_manager->led_buttons[button_index].blinking_on_time = 0;
        io_manager->led_buttons[button_index].backup_brightness = brightness;
    }
}

void io_manager_set_button_brightness_blinking(io_manager_t *io_manager, uint8_t button_index, float brightness, uint16_t blinking_period, uint16_t blinking_on_time)
{
    io_manager->led_buttons[button_index].backup_brightness = brightness;
    io_manager->led_buttons[button_index].blinking_period = blinking_period;
    io_manager->led_buttons[button_index].blinking_on_time = blinking_on_time;
    io_manager->led_buttons[button_index].blinking_elapsed = 0;
}

void io_manager_set_display_brightness(io_manager_t *io_manager, float brightness)
{
    if (io_manager->display_leds[0].current_brightness != brightness) {
        for (int i = 0; i < IO_MANAGER_DISPLAY_LED_COUNT; i++) {
            io_manager->display_leds[i].current_brightness = brightness;
            io_manager->display_leds[i].brightness_changed = true;
        }
    }
}