#include "piezo_buzzer.h"

#include <assert.h>

bool piezo_buzzer_start(piezo_buzzer_handle_t *handle, float frequency)
{
	uint32_t autoreload = (uint32_t)(handle->timer_frequency / frequency);

	if (autoreload > 65535) {
		return false;
	}

	uint32_t compare = (uint32_t)(autoreload * 0.5f);

	__HAL_TIM_SET_AUTORELOAD(handle->timer_handle, autoreload);
	__HAL_TIM_SET_COMPARE(handle->timer_handle, handle->timer_channel, compare);

	if (handle->is_n_channel) {
		HAL_TIMEx_PWMN_Start(handle->timer_handle, handle->timer_channel);
	} else {
		HAL_TIM_PWM_Start(handle->timer_handle, handle->timer_channel);
	}

	return true;
}

void piezo_buzzer_stop(piezo_buzzer_handle_t *handle)
{
	if (handle->is_n_channel) {
		HAL_TIMEx_PWMN_Stop(handle->timer_handle, handle->timer_channel);
	} else {
		HAL_TIM_PWM_Stop(handle->timer_handle, handle->timer_channel);
	}
}
