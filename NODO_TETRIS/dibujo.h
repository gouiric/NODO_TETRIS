#ifndef DIBUJO_H_INCLUDED
#define DIBUJO_H_INCLUDED
#include <stdint.h>
#include "graficos.h"

#define ESPACIO -1
#define CENTRADO -1000


typedef struct{
    int ancho;
    int alto;
    int escala_v;
    int tab_offsetX;
    int tab_offsetY;
    int mino_tamanio;
    int tam_tabX;
    int tam_tabY;
    int tilesX;
    int tilesY;
    float pasoX;
    float pasoY;
    double time;
}Pantalla;

Pantalla* inicializar_helper_dibujo(int ancho, int alto, int escala_v);

extern Pantalla* pantalla;

void semilla_fondo(double);

void dibujar_rect(int x, int y, int w, int h, uint8_t col);
void limpiar(uint8_t col);
void dibujar_fondo();

int porc_a_pixel(float porc, int tam);

//Toma un objeto del tipo car16 y lo dibuja en una ubicacion en porcentaje de la pantalla
void dibujar_spr_porc(car16* spr, int sprSzX, int sprSzY, float porcX, float porcY, int escala);
//toma un bitmap monocromatico y lo dibuja en una ubicacion de porcentaje de la pantalla
//MODIFICACION ahora toma un color de fondo, ya no es monocromatico(?)
void dibujar_spr_mono_porc(uint8_t *spr, int sprSzX, int sprSzY, float porcX, float porcY, int escala, int col, int colBG);

void dibujar_mino(uint8_t tab_x, uint8_t tab_y, uint8_t col);

//  experimental
// toma un string y lo dibuja en pantalla en base a una fuente y llamando a dibujar_spr_mono_porc
// [1]puntero a string, [2]tamaño string, [3]Posición inicial X en porcentaje, [4]Posición inicial Y en porcentaje
// [4]Escala de sprites, [5]Color letras
void dibujar_texto(char* texto, float porcXI, float porcYI, int escala, int col);

void dibujar_filtro_pausa(uint8_t col);

void limpiar_helper_pantalla();

#endif // DIBUJO_H_INCLUDED
