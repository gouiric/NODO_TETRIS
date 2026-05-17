#ifndef SONIDO_H_INCLUDED
#define SONIDO_H_INCLUDED

void audio_init();
void audio_select_loop(const char*);
void audio_switch_loop();
void audio_stop_loop();
void audio_play_cue(const char*);
void audio_clean();

#endif
