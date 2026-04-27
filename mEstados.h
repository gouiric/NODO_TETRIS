#ifndef MESTADOS_H_INCLUDED
#define MESTADOS_H_INCLUDED
#include <stdbool.h>
#include "dibujo.h"

#define TAMANIO_NOMBRE 128

typedef enum{
    PANTALLA_SPLASH,
    PANTALLA_NOMBRE,
    PANTALLA_MENU
}eEstadoJuego;

//
// Punteros a funcion genericos mas dato generico para animaciones (contador de frames)
//
typedef struct{
    void (*dibujar_escena)();
    void (*loop_escena)();
    int contador;
}Escena;

//  Maquina de estados
//  Contiene todos los estados posibles mas el estado actual
typedef struct{
    eEstadoJuego estadoActual;
    bool corriendo;
    Escena escenaSplash;
    Escena escenaNombre;
    Escena *escenaActual;
    char nombreActual[TAMANIO_NOMBRE]; //nose si esto deberia ir aca
    int tamanioNombre;
}Context;

Context* inicializar_contexto();

extern Context* contexto;

//Llamada por el bucle principal
//le encarga a los estados correr su propio bucle de video y logica
void correr();

void cambiar_contexto(eEstadoJuego);

void limpiar_contexto();

#endif // MESTADOS_H_INCLUDED
