#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <GBT/gbt.h>
#include "piezas.h"
#include "dibujo.h"

#define TABLERO_FILAS 20
#define TABLERO_COLS 12
#define TAMANIO_BLOQUE 9

typedef struct
{
    uint8_t** matriz;
}Tablero;


void inicialiar_tablero(Tablero* t);
void dibujar_tablero(Tablero* t, uint16_t offsetX, uint16_t offsetY);
int limpiar_filas(Tablero* t);
bool colision(Tablero* t, Pieza* p, int ox, int oy);
void anclar_pieza(Tablero* t, Pieza* p);
void destruir_tablero(Tablero* t, int filas);


#endif // TABLERO_H_INCLUDED
