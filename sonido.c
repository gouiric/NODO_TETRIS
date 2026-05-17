#include "sonido.h"
#include <stdio.h>
#include "miniaudio.h"

static ma_engine engine;
static ma_sound bgMusic;
static int engineActive = 0;
static int musicLoaded = 0;
static int musicIsPaused = 0;

void audio_init(){
    if(ma_engine_init(NULL, &engine) == MA_SUCCESS){
        engineActive = 1;
    }else{
        printf("Fallo al iniciar motor de sonido!\nEjecucion continua con normalidad...\n");
    }
}

void audio_select_loop(const char* filename){
    if(!engineActive)
        return;

    if(musicLoaded){
        ma_sound_stop(&bgMusic);
        ma_sound_uninit(&bgMusic);
        musicLoaded = 0;
    }

    ma_result result = ma_sound_init_from_file(&engine, filename, MA_SOUND_FLAG_STREAM, NULL, NULL, &bgMusic);

    if(result == MA_SUCCESS){
        ma_sound_set_looping(&bgMusic, MA_TRUE);
        ma_sound_start(&bgMusic);
        musicLoaded = 1;
    }else{
        printf("No se carga el loop de sonido\nContinuando en silencio...\n");
    }
}

void audio_switch_loop(){
    if(!engineActive || !musicLoaded) return;

    if(musicIsPaused)
    {
        ma_sound_start(&bgMusic);
        musicIsPaused = 0;
    }else if(!musicIsPaused)
    {
        ma_sound_stop(&bgMusic);
        musicIsPaused = 1;
    }
}

void audio_stop_loop(){
    if(!engineActive || !musicLoaded || musicIsPaused) return;

    ma_sound_stop(&bgMusic);
    musicIsPaused = 1;
}

void audio_play_cue(const char* filename){
    if(!engineActive)
        return;

    ma_engine_play_sound(&engine, filename, NULL);
}

void audio_clean(){
    if(musicLoaded) ma_sound_uninit(&bgMusic);
    if(engineActive) ma_engine_uninit(&engine);
}
