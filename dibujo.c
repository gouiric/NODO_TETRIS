#include "dibujo.h"
#include "GBT/gbt_graficos.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "graficos.h"

#define TAMANIO_MINO 4.0

Pantalla* pantalla = NULL;

Pantalla* inicializar_helper_dibujo(int ancho, int alto, int escala_v){
    pantalla = malloc(sizeof(Pantalla));
    if(pantalla == NULL){
        fprintf(stderr, "Error al solicitar memoria para pantalla\n");
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

void dibujar_spr_mono_porc(uint8_t *spr, int sprSzX, int sprSzY, float porcX, float porcY, int escala, int col, int colBG){
    int offX = porc_a_pixel(porcX, pantalla->ancho);
    int offY = porc_a_pixel(porcY, pantalla->alto);
    for(int x = offX; x < offX + (sprSzX * escala); x++){
        for(int y = offY; y < offY + (sprSzY * escala); y++){
            int srcX = (x-offX) / escala;
            int srcY = (y-offY) / escala;
            if(spr[(srcY * sprSzY) + srcX] == 1){
                gbt_dibujar_pixel(x, y, col);
            }else{
                gbt_dibujar_pixel(x,y, colBG);
            }
        }
    }
}

void dibujar_mino(uint8_t tab_x, uint8_t tab_y, uint8_t col)
{

    //Posicion del mino en pantalla
    int offset_x = pantalla->tab_offsetX + tab_x * pantalla->mino_tamanio;
    int offset_y = pantalla->tab_offsetY + tab_y * pantalla->mino_tamanio;

    int escala = 2 * pantalla->escala_v;

    for(int i = 0; i < TAMANIO_MINO; i++){
        for(int j = 0; j < TAMANIO_MINO; j++){
            int color = minosComb[col-1][j][i];
            int inicio_x = offset_x + j * escala;
            int inicio_y = offset_y + i * escala;
            for(int x = inicio_x; x < inicio_x + escala; x++){
                for(int y = inicio_y; y < inicio_y + escala; y++){
                    gbt_dibujar_pixel(x, y, color);
                }
            }
        }
    }
}


//
// FUNCION CON VALORES HARDCOEADOS
//
void dibujar_texto(char* texto, int largoTexto, float porcXI, float porcYI, int escala, int col)
{
    if(largoTexto == 0 || texto == NULL){
        printf("Texto vacio");
        dibujar_texto("texto vacio", 12, 1, 1, 1, 1);
        return;
    }
    int posX = (int)round((8.0*escala/pantalla->ancho)*100);
    //printf("posX:%d\n",posX);
    int actual;
    //int posY = (8*escala/pantalla->alto)*100;
    for(int i = 0; i < largoTexto; i++){
        if(texto[i] >= 'a' && texto[i] <= 'z')
            actual = texto[i] - 'a';
        else if(texto[i] >= '0' && texto[i] <= '9')
            actual = texto[i] - '0' + 26;
        dibujar_spr_mono_porc(&fuente[actual][0][0], 8, 8, porcXI + (i * posX), porcYI, escala, col, 16);
    }
}

void limpiar_helper_pantalla(){
    free(pantalla);
}
