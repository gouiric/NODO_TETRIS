#include "dibujo.h"
#include "GBT/gbt_graficos.h"
#include "mEstados.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Pantalla* pantalla = NULL;

Pantalla* inicializar_helper_dibujo(int ancho, int alto, int escala_v){
    pantalla = malloc(sizeof(Pantalla));
    if(pantalla != NULL){
        fprintf(stderr, "Error al solicitar memoria para pantalla");
        return NULL;
    }
    pantalla->ancho = ancho;
    pantalla->alto = alto;
    pantalla-> escala_v = escala_v;

    return pantalla;
}

void dibujar_rect(int x, int y, int w, int h, uint8_t col){
    for(int i = x; i <= x + w; i++){
        for(int j = y; j <= y + h; j++){
            gbt_dibujar_pixel(i, j, col);
        }
    }
}

void limpiar(uint8_t col){
    gbt_borrar_backbuffer(col);
}

int porc_a_pixel(float porc, int tam){
    return (int)round((porc / 100.0f) * tam);
}

void dibujar_spr_porc(car16 *spr, int sprSzX, int sprSzY, float porcX, float porcY, int escala){
    int offX = porc_a_pixel(porcX, pantalla->ancho);
    int offY = porc_a_pixel(porcY, pantalla->alto);
    int col;
    for(int x = offX; x < offX + (sprSzX * escala); x ++){
        for(int y = offY; y < offY + (sprSzY * escala); y++){
            int srcX = (x-offX) / escala;
            int srcY = (y-offY) / escala;
            if(srcX < sprSzX && srcY < sprSzY){
                col = spr->mapa[srcY][srcX];
                if(col!=0){
                    gbt_dibujar_pixel(x, y, spr->colores[col]);
                }
            }

        }
    }
}

void limpiar_helper_pantalla(){
    free(pantalla);
}
