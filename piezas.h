#ifndef PIEZAS_H_INCLUDED
#define PIEZAS_H_INCLUDED

#include <stdint.h>


#include <GBT/gbt.h>

#define ORDEN_PIEZA 4



/**
 La estructura toma como datos un "x" de nacimiento, un "y" de nacimiento, un color determinado y una matriz de 4x4
**/

typedef struct
{
    int x;
    int y;
    uint8_t color;
    uint8_t matriz[4][4];
}Pieza;

///Inicialamos la pieza
void cargar_pieza(Pieza *p, int tipo_pieza);

///Dibujamos la pieza
void dibujar_pieza(Pieza* p, uint16_t x_tablero, uint16_t y_tablero);

void sentido_horario(uint8_t mat_destino[][ORDEN_PIEZA], uint8_t mat_origen[][ORDEN_PIEZA]);

void sentido_antihorario(uint8_t mat_destino[][ORDEN_PIEZA], uint8_t mat_origen[][ORDEN_PIEZA]);


#endif // PIEZAS_H_INCLUDED
