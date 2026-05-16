#include "pMenu.h"
#include "dibujo.h"
#include "mEstados.h"
#include <stdio.h>
#include "GBT_v2026.1C.01/include/GBT/gbt_entrada.h"
#include "graficos.h"

#define CANTIDAD_ELEMENTOS_MENU 4

int pos_puntero = 0;


void loopDibujoMenu(){
    limpiar(0);

    //
    // Bucle para dibujar fondo de ladrillos
    for(int i = 0; i < pantalla->tilesX; i++){
        for(int j = 0; j < pantalla->tilesY; j++){
            int tip = (i+j)%2;

            int ladrilloX;
            if((j%2)==0)
                ladrilloX = i / 2;
            else
                ladrilloX = (i + 1) / 2;

            int ruido =(ladrilloX * 73856093) ^ (j * 19349663);

            if((ruido%8) == 0)
                dibujar_spr_mono_porc(*ladri[tip], 6, 6, i * pantalla->pasoX, j * pantalla->pasoY, 3, 10, 2);
            else
                dibujar_spr_mono_porc(*ladri[tip], 6, 6, i * pantalla->pasoX, j * pantalla->pasoY, 3, 1, 9);
        }
    }
    char text[50];
    sprintf(text, "Bienvenido %s", contexto->nombreActual);
    dibujar_texto(text, 9, 11, 2, 8);
    dibujar_texto(text, 10, 10, 2, 7);

    //Menu
    char tMenu[CANTIDAD_ELEMENTOS_MENU][20] = {"JUGAR","DELUXE" , "OPCIONES", "SALIR"};
    for(int i = 0; i < CANTIDAD_ELEMENTOS_MENU; i++)
    {
        char linea[20];
        if(i==pos_puntero)
            sprintf(linea, "> %s", tMenu[i]);
        else
            sprintf(linea, "  %s", tMenu[i]);

        dibujar_texto(linea, CENTRADO + 1, 46 + (i * 10), 2, 8);
        dibujar_texto(linea, CENTRADO, 45 + (i * 10), 2, 7);
    }

    dibujar_texto("®NODO 2026", 0, 95, 1, 7);
}

void loopLogicaMenu(){
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    if(tecla == GBTK_ARRIBA)
    {
        pos_puntero -= 1;
        if(pos_puntero < 0)
            pos_puntero = CANTIDAD_ELEMENTOS_MENU-1;
    }else if(tecla == GBTK_ABAJO)
    {
        pos_puntero += 1;
        if(pos_puntero > CANTIDAD_ELEMENTOS_MENU-1)
            pos_puntero = 0;
    }else if(tecla == GBTK_ENTER)
    {
        switch(pos_puntero)
        {
            case 0:
                cambiar_contexto(PANTALLA_TETRIS);
                break;
            case 1:
                cambiar_contexto(PANTALLA_DELUXE);
                break;
            case 2:
                cambiar_contexto(PANTALLA_OPCIONES);
                break;
            case 3:
                contexto->corriendo = false;
                break;
        }
    }
}
