#ifndef DIBUJO_H_INCLUDED
#define DIBUJO_H_INCLUDED
#include <stdint.h>
#include "graficos.h"

typedef struct{
    int ancho;
    int alto;
    int escala_v;
}Pantalla;

Pantalla* inicializar_helper_dibujo(int ancho, int alto, int escala_v);

extern Pantalla* pantalla;

void dibujar_rect(int x, int y, int w, int h, uint8_t col);

//Basicamente es la funcion gbt_borrar_backbuffer pero mas corta
void limpiar(uint8_t col);

int porc_a_pixel(float porc, int tam);

//Toma un objeto del tipo car16(sprite 16x16) y lo dibuja en una ubicacion en porcentaje de la pantalla
void dibujar_spr_porc(car16* spr, int sprSzX, int sprSzY, float porcX, float porcY, int escala);
//toma un bitmap monocromatico y lo dibuja en una ubicacion de porcentaje de la pantalla
void dibujar_spr_mono_porc(uint8_t *spr, int sprSzX, int sprSzY, float porcX, float porcY, int escala, int col);


void limpiar_helper_pantalla();

#endif // DIBUJO_H_INCLUDED
