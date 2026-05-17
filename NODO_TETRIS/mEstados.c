#include "mEstados.h"
#include <stdlib.h>
#include <stdbool.h>
#include "GBT/gbt_entrada.h"
#include "dibujo.h"
#include "splash.h"
#include <stdio.h>
#include <string.h>
#include "pNombre.h"
#include "tetris.h"
#include "graficos.h"
#include "opciones.h"
#include "pMenu.h"
#include "Perder.h"
#include "Pausa.h"
#include <time.h>

Context* contexto = NULL;

Context* inicializar_contexto(){
    contexto = malloc(sizeof(Context));
    if(contexto == NULL){
        fprintf(stderr, "Error al solicitar memoria para contexto\n");
        return NULL;
    }
    cargar_combinaciones_minos();

    //Cargamos los archivos
    //cargar_crear_archivo(ARCHIVO_OP);

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

    //Relacion a pantalla opciones
    contexto->escenaOpciones.dibujar_escena = dibujar_opciones;
    contexto->escenaOpciones.loop_escena = loop_opciones;

    //Relacionado a pantalla menu
    contexto->escenaMenu.dibujar_escena = loopDibujoMenu;
    contexto->escenaMenu.loop_escena = loopLogicaMenu;

    //Relacionado a pantalla perdiste
    contexto->escenaPerdiste.dibujar_escena = loop_dibujar_perder;
    contexto->escenaPerdiste.loop_escena = loop_logica_perder;

    //Relacionado a pantalla pausa
    contexto->escenaPausa.dibujar_escena = loop_dibujar_pausa;
    contexto->escenaPausa.loop_escena = loop_logica_pausa;

    return contexto;
}

void correr(){
    gbt_procesar_entrada();
    contexto->escenaActual->loop_escena();
    contexto->escenaActual->dibujar_escena();
}

void cambiar_contexto(eEstadoJuego siguienteEstado){
    if((contexto->estadoActual == PANTALLA_TETRIS || contexto->estadoActual == PANTALLA_DELUXE) && siguienteEstado != PANTALLA_PAUSA){
        limpiar_tetris();
    }
    if(contexto->escenaActual == PANTALLA_PAUSA && (siguienteEstado != PANTALLA_TETRIS && siguienteEstado != PANTALLA_DELUXE))
    {
        limpiar_tetris();
    }
    semilla_fondo(time(NULL));
    if(siguienteEstado != contexto->estadoActual){
        contexto->estadoActual = siguienteEstado;
        switch(siguienteEstado){
            case PANTALLA_PAUSA:
                contexto->escenaActual = &contexto->escenaPausa;
                break;
            case PANTALLA_PERDER:
                contexto->escenaActual = &contexto->escenaPerdiste;
                break;
            case PANTALLA_OPCIONES:
                contexto->escenaActual = &contexto->escenaOpciones;
                break;
            case PANTALLA_SPLASH:
                printf("El juego no deberia volver al splash pero xd\n");
                contexto->escenaActual = &contexto->escenaSplash;
                break;
            case PANTALLA_NOMBRE:
                contexto->escenaActual = &contexto->escenaNombre;
                break;
            case PANTALLA_MENU:
                contexto->escenaActual = &contexto->escenaMenu;
                break;
            case PANTALLA_TETRIS:
                if(!tetris)
                {
                    if(!inicializar_tetris(false))
                    {
                        printf("Error al iniciar mochila tetris\n");
                        contexto->corriendo = false;
                    }
                }
                contexto->escenaActual = &contexto->escenaTetris;
                break;
            case PANTALLA_DELUXE:
                if(!tetris)
                {
                    if(!inicializar_tetris(true))
                    {
                        printf("Error al inicializar el tetris\n");
                        contexto->corriendo = false;
                    }
                }
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
