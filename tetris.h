#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include "tablero.h"
#include "piezas.h"
#include <time.h>

#define SENTIDO_ANTIHORARIO 0
#define SENTIDO_HORARIO 1

typedef struct{
    Tablero tablero;
    Pieza pieza;
    uint8_t tipo_pieza;
    uint32_t contador_frames;
    uint32_t puntos;
    uint32_t cant_piezas;
    float velocidad_ms;
    float umbral_frames;
    uint32_t cont_fijacion;
    bool contacto;
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

//
void rotar_pieza_activa(uint8_t sentido);
void mover_pieza(eGBT_Tecla tecla);
bool procesar_caida();
void calculo_puntos(int lineas_borradas);
void obtener_nueva_pieza();
void actualizar_datos_tetris();
bool perder();
void procesar_impacto();

#endif
