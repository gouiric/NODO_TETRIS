#include "tetris.h"
#include <stdlib.h>
#include "GBT/gbt_entrada.h"
#include "tablero.h"
#include "mEstados.h"
#include <stdio.h>

Tetris* tetris = NULL;

Tetris* inicializar_tetris(){
    tetris = malloc(sizeof(Tetris));
    if(!tetris){
        return NULL;
    }

    //
    // Añadir verificacion al malloc
    //
    inicialiar_tablero(&tetris->tablero);

    return tetris;
}

void loop_dibujar_tetris()
{
    limpiar(0);
    dibujar_tablero(&tetris->tablero, 34, 4);
}

void loop_logica_tetris()
{
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    if(tecla == GBTK_ESCAPE){
        printf("Volver a pantalla inicial\n");
        cambiar_contexto(PANTALLA_SPLASH);
    }

}

void limpiar_tetris()
{
    destruir_tablero(&tetris->tablero);
    free(tetris);
}
