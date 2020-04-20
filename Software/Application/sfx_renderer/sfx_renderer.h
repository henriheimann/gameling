#pragma once

#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

/**
 * Enumeration defining the playable notes.
 * SFX_RENDERER_PAUSE is used to define pauses.
 * SFX_RENDERER_NOTES_COUNT defines the number of playable notes, excluding the pause.
 */
typedef enum {
    SFX_RENDERER_NOTE_A0,
    SFX_RENDERER_NOTE_BB0,
    SFX_RENDERER_NOTE_B0,
    SFX_RENDERER_NOTE_C1,
    SFX_RENDERER_NOTE_DB1,
    SFX_RENDERER_NOTE_D1,
    SFX_RENDERER_NOTE_EB1,
    SFX_RENDERER_NOTE_E1,
    SFX_RENDERER_NOTE_F1,
    SFX_RENDERER_NOTE_GB1,
    SFX_RENDERER_NOTE_G1,
    SFX_RENDERER_NOTE_AB1,
    SFX_RENDERER_NOTE_A1,
    SFX_RENDERER_NOTE_BB1,
    SFX_RENDERER_NOTE_B1,
    SFX_RENDERER_NOTE_C2,
    SFX_RENDERER_NOTE_DB2,
    SFX_RENDERER_NOTE_D2,
    SFX_RENDERER_NOTE_EB2,
    SFX_RENDERER_NOTE_E2,
    SFX_RENDERER_NOTE_F2,
    SFX_RENDERER_NOTE_GB2,
    SFX_RENDERER_NOTE_G2,
    SFX_RENDERER_NOTE_AB2,
    SFX_RENDERER_NOTE_A2,
    SFX_RENDERER_NOTE_BB2,
    SFX_RENDERER_NOTE_B2,
    SFX_RENDERER_NOTE_C3,
    SFX_RENDERER_NOTE_DB3,
    SFX_RENDERER_NOTE_D3,
    SFX_RENDERER_NOTE_EB3,
    SFX_RENDERER_NOTE_E3,
    SFX_RENDERER_NOTE_F3,
    SFX_RENDERER_NOTE_GB3,
    SFX_RENDERER_NOTE_G3,
    SFX_RENDERER_NOTE_AB3,
    SFX_RENDERER_NOTE_A3,
    SFX_RENDERER_NOTE_BB3,
    SFX_RENDERER_NOTE_B3,
    SFX_RENDERER_NOTE_C4,
    SFX_RENDERER_NOTE_DB4,
    SFX_RENDERER_NOTE_D4,
    SFX_RENDERER_NOTE_EB4,
    SFX_RENDERER_NOTE_E4,
    SFX_RENDERER_NOTE_F4,
    SFX_RENDERER_NOTE_GB4,
    SFX_RENDERER_NOTE_G4,
    SFX_RENDERER_NOTE_AB4,
    SFX_RENDERER_NOTE_A4,
    SFX_RENDERER_NOTE_BB4,
    SFX_RENDERER_NOTE_B4,
    SFX_RENDERER_NOTE_C5,
    SFX_RENDERER_NOTE_DB5,
    SFX_RENDERER_NOTE_D5,
    SFX_RENDERER_NOTE_EB5,
    SFX_RENDERER_NOTE_E5,
    SFX_RENDERER_NOTE_F5,
    SFX_RENDERER_NOTE_GB5,
    SFX_RENDERER_NOTE_G5,
    SFX_RENDERER_NOTE_AB5,
    SFX_RENDERER_NOTE_A5,
    SFX_RENDERER_NOTE_BB5,
    SFX_RENDERER_NOTE_B5,
    SFX_RENDERER_NOTE_C6,
    SFX_RENDERER_NOTE_DB6,
    SFX_RENDERER_NOTE_D6,
    SFX_RENDERER_NOTE_EB6,
    SFX_RENDERER_NOTE_E6,
    SFX_RENDERER_NOTE_F6,
    SFX_RENDERER_NOTE_GB6,
    SFX_RENDERER_NOTE_G6,
    SFX_RENDERER_NOTE_AB6,
    SFX_RENDERER_NOTE_A6,
    SFX_RENDERER_NOTE_BB6,
    SFX_RENDERER_NOTE_B6,
    SFX_RENDERER_NOTE_C7,
    SFX_RENDERER_NOTE_DB7,
    SFX_RENDERER_NOTE_D7,
    SFX_RENDERER_NOTE_EB7,
    SFX_RENDERER_NOTE_E7,
    SFX_RENDERER_NOTE_F7,
    SFX_RENDERER_NOTE_GB7,
    SFX_RENDERER_NOTE_G7,
    SFX_RENDERER_NOTE_AB7,
    SFX_RENDERER_NOTE_A7,
    SFX_RENDERER_NOTE_BB7,
    SFX_RENDERER_NOTE_B7,
    SFX_RENDERER_NOTE_C8,
    SFX_RENDERER_NOTES_COUNT,
    SFX_RENDERER_PAUSE
} sfx_renderer_note_t;

/**
 * Structure for a single segment of a song.
 */
typedef struct {

    /**
     * The note to play during this segment.
     */
    sfx_renderer_note_t note;

    /**
     * The duration of this segment in milliseconds.
     */
    uint16_t duration;

} sfx_renderer_segment_t;

/**
 * Structure for a song.
 */
typedef struct {

    /**
     * The number of segments of this song.
     */
    size_t num_segments;

    /**
     * Pointer to the segments of this song.
     */
    sfx_renderer_segment_t *segments;

} sfx_renderer_song_t;

typedef void (*sfx_renderer_start_sound_function_t)(void *data, float frequency);
typedef void (*sfx_renderer_stop_sound_function_t)(void *data);

/**
 * Structure defining a music player.
 */
typedef struct {

    /**
     * True if a song is currently being played.
     */
    bool playing;

    /**
     * True if the current song is looped after completion.
     */
    bool looping;

    /**
     * The song currently being played.
     */
    sfx_renderer_song_t *current_song;

    /**
     * The index to the currently played segment.
     */
    size_t current_segment;

    /**
     * The number of ticks into the currently played segment.
     */
    uint16_t current_segment_ticks;

    /**
     * Function data required for the start and stop sound functions.
     */
    void *function_data;

    /**
     * The function to start playing a sound at a given frequency.
     */
    sfx_renderer_start_sound_function_t start_sound_function;

    /**
     * The function to stop playing any sound.
     */
    sfx_renderer_stop_sound_function_t stop_sound_function;

} sfx_renderer_t;

/**
 * Immediately starts playing the given song on the output defined by the SFX renderer.
 * @param sfx_renderer The  SFX render to let the song play.
 * @param song The song to player.
 * @param looped True if the song should be looped.
 */
void sfx_renderer_play_song(sfx_renderer_t *sfx_renderer, sfx_renderer_song_t *song, bool looped);

/**
 * Immediately starts playing a note for a specified duration.
 * @param sfx_renderer The  SFX render to let the sound play.
 * @param note The note to play.
 * @param duration The duration of the sound.
 */
void sfx_renderer_play_note(sfx_renderer_t *sfx_renderer, sfx_renderer_note_t note, uint16_t duration);

/**
 * Immediately stops the playback of the given SFX renderer.
 * @param sfx_renderer The SFX render to stop the playback of.
 */
void sfx_renderer_stop(sfx_renderer_t *sfx_renderer);

/**
 * Executes a the given number of ticks for the given SFX renderer.
 * @param sfx_renderer The SFX renderer to tick.
 * @param elapsed_ticks The number of ticks in milliseconds elapsed since the last update.
 */
void sfx_renderer_update(sfx_renderer_t *sfx_renderer, uint32_t elapsed_ticks);