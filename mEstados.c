#include "mEstados.h"
#include <stdlib.h>
#include <stdbool.h>
#include "GBT/gbt_entrada.h"
#include "splash.h"
#include <stdio.h>
#include <string.h>
#include "pNombre.h"
#include "tetris.h"

Context* contexto = NULL;

Context* inicializar_contexto(){
    contexto = malloc(sizeof(Context));
    if(contexto == NULL){
        fprintf(stderr, "Error al solicitar memoria para contexto\n");
        return NULL;
    }

    contexto->estadoActual = PANTALLA_SPLASH;
    contexto->corriendo = true;
    contexto->escenaActual = &contexto->escenaSplash;

    //Punteros a funcion de la pantalla splash
    contexto->escenaSplash.dibujar_escena = dibujar_splash;
    contexto->escenaSplash.loop_escena = loop_splash;
    contexto->escenaSplash.contador = 0;

    //Relacionado a pantalla nombre
    contexto->escenaNombre.dibujar_escena = dibujar_pantalla_nombre;
    contexto->escenaNombre.loop_escena = loop_pantalla_nombre;
    memset(contexto->nombreActual, 0, sizeof(char) * TAMANIO_NOMBRE);
    contexto->tamanioNombre = 0;

    //Relacionado a pantalla tetris
    contexto->escenaTetris.dibujar_escena = loop_dibujar_tetris;
    contexto->escenaTetris.loop_escena = loop_logica_tetris;

    return contexto;
}

void correr(){
    gbt_procesar_entrada();
    contexto->escenaActual->loop_escena();
    contexto->escenaActual->dibujar_escena();
}

void cambiar_contexto(eEstadoJuego siguienteEstado){
    if(contexto->estadoActual == PANTALLA_TETRIS){
        limpiar_tetris();
    }
    if(siguienteEstado != contexto->estadoActual){
        contexto->estadoActual = siguienteEstado;
        switch(siguienteEstado){
            case PANTALLA_SPLASH:
                printf("El juego no deberia volver al splash pero xd\n");
                contexto->escenaActual = &contexto->escenaSplash;
                break;
            case PANTALLA_NOMBRE:
                contexto->escenaActual = &contexto->escenaNombre;
                break;
            case PANTALLA_MENU:
                //contexto->escenaActual = ;
                break;
            case PANTALLA_TETRIS:
                if(!inicializar_tetris()){
                    printf("Error al iniciar mochila tetris\n");
                    contexto->corriendo = false;}
                contexto->escenaActual = &contexto->escenaTetris;
                break;
        }
    }
    else {
    printf("No se hizo cambio de estado");
    }
}

void limpiar_contexto(){
    free(contexto);
}
