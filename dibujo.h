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
void limpiar(uint8_t col);

int porc_a_pixel(float porc, int tam);

void dibujar_spr_porc(car16* spr, int sprSzX, int sprSzY, float porcX, float porcY, int escala);

void limpiar_helper_pantalla();

#endif // DIBUJO_H_INCLUDED
