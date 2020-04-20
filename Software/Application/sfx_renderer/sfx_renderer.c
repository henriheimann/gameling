#include "sfx_renderer.h"

static const float frequencies[SFX_RENDERER_NOTES_COUNT] = {
        // A0 - B0
        27.5000f, 29.1352f, 30.8677f,
        // C1 - B1
        32.7032f, 34.6478f, 36.7081f, 38.8909f, 41.2034f, 43.6535f,
        46.2493f, 48.9994f, 51.9131f, 55.0000f, 58.2704f, 61.7354f,
        // C2 - B2
        65.4064f, 69.2957f, 73.4162f, 77.7817f, 82.4069f, 87.4069f,
        92.4986f, 97.9989f, 103.826f, 110.000f, 116.541f, 123.471f,
        // C3 - B3
        130.813f, 138.591f, 146.832f, 155.563f, 164.832f, 174.614f,
        183.997f, 195.998f, 207.652f, 220.000f, 233.082f, 246.942f,
        // C4 - B4
        261.626f, 277.183f, 293.665f, 311.127f, 329.228f, 349.228f,
        369.994f, 391.995f, 415.305f, 440.000f, 466.164f, 493.883f,
        // C5 - B5
        523.251f, 554.365f, 587.330f, 622.254f, 659.255f, 698.456f,
        739.989f, 783.991f, 830.609f, 880.000f, 932.328f, 987.767f,
        // C6 - B6
        1046.50f, 1108.73f, 1174.66f, 1244.51f, 1318.51f, 1396.91f,
        1479.98f, 1567.98f, 1661.22f, 1760.00f, 1864.66f, 1975.53f,
        // C7 - B7
        2093.00f, 2217.46f, 2349.32f, 2489.02f, 2637.02f, 2793.83f,
        2959.96f, 3135.96f, 3322.44f, 3520.00f, 3729.31f, 3951.07f,
        // C8
        4186.01f
};

void sfx_renderer_play_next_segment(sfx_renderer_t *sfx_renderer)
{
    sfx_renderer_note_t note = sfx_renderer->current_song->segments[sfx_renderer->current_segment].note;

    if (note == SFX_RENDERER_PAUSE) {
        sfx_renderer->stop_sound_function(sfx_renderer->function_data);
    } else if (note < SFX_RENDERER_NOTES_COUNT) {
        sfx_renderer->start_sound_function(sfx_renderer->function_data, frequencies[note]);
    }
}

void sfx_renderer_play_song(sfx_renderer_t *sfx_renderer, sfx_renderer_song_t *song, bool looped)
{
    sfx_renderer->playing = true;
    sfx_renderer->looping = looped;

    sfx_renderer->current_song = song;
    sfx_renderer->current_segment = 0;
    sfx_renderer->current_segment_ticks = 0;
}

void sfx_renderer_play_note(sfx_renderer_t *sfx_renderer, sfx_renderer_note_t note, uint16_t duration)
{
    static sfx_renderer_segment_t segment;
    segment.note = note;
    segment.duration = duration;

    static sfx_renderer_song_t song;
    song.segments = &segment;
    song.num_segments = 1;

    sfx_renderer_play_song(sfx_renderer, &song, false);
}

void sfx_renderer_stop(sfx_renderer_t *sfx_renderer)
{
    sfx_renderer->playing = false;
    sfx_renderer->looping = false;

    sfx_renderer->current_song = NULL;
    sfx_renderer->current_segment = 0;
    sfx_renderer->current_segment_ticks = 0;

    sfx_renderer->stop_sound_function(sfx_renderer->function_data);
}

void sfx_renderer_update(sfx_renderer_t *sfx_renderer, uint32_t elapsed_ticks)
{
    if (sfx_renderer->playing) {

        sfx_renderer->current_segment_ticks += elapsed_ticks;

        // If the current segment was completed we need to play the next segment.
        sfx_renderer_segment_t segment = sfx_renderer->current_song->segments[sfx_renderer->current_segment];
        if (sfx_renderer->current_segment_ticks > segment.duration) {

            // Reset the segment ticks and increment the current segment index.
            sfx_renderer->current_segment_ticks = 0;
            sfx_renderer->current_segment++;

            // If the song was completed either stop the playback and return or loop back to the first segment.
            if (sfx_renderer->current_segment > sfx_renderer->current_song->num_segments) {
                if (!sfx_renderer->looping) {
                    sfx_renderer_stop(sfx_renderer);
                    return;
                } else {
                    sfx_renderer->current_segment = 0;
                }
            }

            // Play the new current segment.
            sfx_renderer_play_next_segment(sfx_renderer);
        }
    }
}