#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include "tablero.h"
#include "piezas.h"

typedef struct{
    Tablero tablero;
    Pieza pieza;
}Tetris;

//
// Los datos relacionados a tetris ahora existen en una mochila independiente al contexto;
//
extern Tetris* tetris;

Tetris* inicializar_tetris();
void limpiar_tetris();

//
// no es necesario separar dibujar y logica en dos funciones separadas
// se separan para mantener legibilidad en el codigo
//
void loop_dibujar_tetris();
void loop_logica_tetris();

#endif
