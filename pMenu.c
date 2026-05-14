#include "pMenu.h"
#include "dibujo.h"
#include "mEstados.h"
#include <stdio.h>
#include "GBT_v2026.1C.01/include/GBT/gbt_entrada.h"


void loopDibujoMenu(){
    limpiar(0);
    char text[50];
    sprintf(text, "Bienvenido %s", contexto->nombreActual);
    dibujar_texto(text, 10, 10, 2, 1);

}

void loopLogicaMenu(){
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    if(tecla == GBTK_t){
        printf("Pasando a escena Tetris\n");    //Temporal
        cambiar_contexto(PANTALLA_TETRIS);
    }
    else if(tecla == GBTK_d)
    {
        printf("Pasando a escena deluxe\n");
        cambiar_contexto(PANTALLA_DELUXE);
    }
    else if(tecla == GBTK_n)
    {
        printf("Pasando a escena nombre\n");
        cambiar_contexto(PANTALLA_NOMBRE);
    }
    else if(tecla == GBTK_o)
    {
        printf("Pasando a escena opciones\n");
        cambiar_contexto(PANTALLA_OPCIONES);
    }
}
