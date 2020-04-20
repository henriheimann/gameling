#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <pca9685/pca9685.h>

/**
 * The number of LED buttons connected.
 */
#define IO_MANAGER_BUTTON_COUNT 12

/**
 * Structure defining an LED button.
 */
typedef struct {

    /**
	 * The port of the button pin.
	 */
    GPIO_TypeDef *button_port;

    /**
     * The button pin.
     */
    uint16_t button_pin;

    /**
     * The button's LED channel.
     */
    uint8_t led_channel;

    /**
     * The requested LED brightness.
     */
    float requested_brightness;

    /**
     * Backup of the requested LED brightness for LED blinking.
     */
    float backup_brightness;

    /**
     * The current LED brightness.
     */
    float current_brightness;

    /**
     * The duration of a blinking cycle or 0 for no blinking.
     */
    uint16_t blinking_period;

    /**
     * The on time during a blinking cycle.
     */
    uint16_t blinking_on_time;

    /**
     * The number of milliseconds elapsed during the blinking cycle.
     */
    uint16_t blinking_elapsed;

    /**
     * The current button push state.
     */
    bool current_state;

} led_button_t;

/**
 * The number of display background LEDs.
 */
#define IO_MANAGER_DISPLAY_LED_COUNT 4

/**
 * Structure defining a display background LED.
 */
typedef struct {

    /**
     * The button's LED channel.
     */
    uint8_t led_channel;

    /**
     * The current LED brightness.
     */
    float current_brightness;

    /**
     * Set to true if the brightness of the LED changed.
     */
    bool brightness_changed;

} display_led_t;

/**
 * Structure describing an input and output manager.
 */
typedef struct {

    /**
     * Handle to the PCA9685 driver managing the LEDs.
     */
    pca9685_handle_t *pca9685_handle;

    /**
     * Current states and information about the LED buttons.
     */
    led_button_t led_buttons[IO_MANAGER_BUTTON_COUNT];

    /**
     * Current states and information about the display LEDs.
     */
    display_led_t display_leds[IO_MANAGER_DISPLAY_LED_COUNT];

} io_manager_t;

/**
 * Executes an update for the LED buttons and other LEDs connected, which checks the current state and updates changed
 * brightnesses.
 * @param io_manager The IO manager managing the LEDs and buttons.
 * @param elapsed_ticks The number of ticks in milliseconds elapsed since the last update.
 */
void io_manager_update(io_manager_t *io_manager, uint32_t elapsed_ticks);

/**
 * Returns the current state of the button with the given index.
 * @param io_manager The IO manager managing the buttons.
 * @param button_index The index of the button to return the state of.
 * @return True when pressed, false otherwise.
 */
bool io_manager_get_button_state(io_manager_t *io_manager, uint8_t button_index);

/**
 * Sets the brightness for the LED of the button with the given index.
 * @param io_manager The IO manager managing the LEDs.
 * @param button_index The index of the button to set the LED's brightness of.
 * @param brightness The brightness to set.
 */
void io_manager_set_button_brightness(io_manager_t *io_manager, uint8_t button_index, float brightness);

void io_manager_set_button_brightness_blinking(io_manager_t *io_manager, uint8_t button_index, float brightness, uint16_t blinking_period, uint16_t blinking_on_time);

/**
 * Sets the display background brightness of the four associated LEDs.
 * @param io_manager The IO manager managing the LEDs.
 * @param brightness The brightness to set.
 */
void io_manager_set_display_brightness(io_manager_t *io_manager, float brightness);