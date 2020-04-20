#pragma once

#include <stm32l4xx_hal.h>
#include <stdbool.h>

/**
 * Structure defining a handle describing a piezo buzzer.
 */
typedef struct {

	/**
	 * The handle to the timer creating the PWM output for the buzzer.
	 */
	TIM_HandleTypeDef *timer_handle;

	/**
	 * The channel of the timer driver the PWM output.
	 */
	uint32_t timer_channel;

	/**
	 * True if the channel is a negative channel.
	 */
	bool is_n_channel;

	/**
	 * The timers base frequency used for calculations of period and duty cycle.
	 */
	float timer_frequency;

} piezo_buzzer_handle_t;

/**
 * Starts PWM generation for a piezo buzzer described by the given handle with frequency.
 * @param handle Handle to a piezo buzzer.
 * @param frequency The frequency to play.
 * @return True on success, false if frequency is not playable.
 */
bool piezo_buzzer_start(piezo_buzzer_handle_t *handle, float frequency);

/**
 * Stops the PWM generation for a piezo buzzer.
 * @param handle Handle to a piezo buzzer.
 */
void piezo_buzzer_stop(piezo_buzzer_handle_t *handle);
