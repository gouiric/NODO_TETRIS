#include "mEstados.h"
#include <stdlib.h>
#include <stdbool.h>
#include "GBT/gbt_entrada.h"
#include "splash.h"

Context* contexto = NULL;

Context* inicializar_contexto(){
    contexto = malloc(sizeof(Context));

    contexto->estadoActual = PANTALLA_SPLASH;
    contexto->corriendo = true;
    contexto->escenaActual = &contexto->escenaSplash;

    //Punteros a funcion de la pantalla splash
    contexto->escenaSplash.dibujar_escena = dibujar_splash;
    contexto->escenaSplash.loop_escena = loop_splash;

    return contexto;
}

void correr(){
    gbt_procesar_entrada();
    contexto->escenaActual->loop_escena();
    contexto->escenaActual->dibujar_escena();
}
