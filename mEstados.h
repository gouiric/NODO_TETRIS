#ifndef MESTADOS_H_INCLUDED
#define MESTADOS_H_INCLUDED
#include <stdbool.h>
#include "dibujo.h"

typedef enum{
    PANTALLA_SPLASH
}eEstadoJuego;

typedef struct{
    void (*dibujar_escena)();
    void (*loop_escena)();
    int contador;
}Escena;

typedef struct{
    eEstadoJuego estadoActual;
    bool corriendo;
    Escena escenaSplash;
    Escena *escenaActual;
}Context;

Context* inicializar_contexto();

extern Context* contexto;

void correr();

#endif // MESTADOS_H_INCLUDED
