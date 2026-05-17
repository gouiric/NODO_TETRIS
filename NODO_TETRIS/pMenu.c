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

    dibujar_fondo();

    char text[50];
    sprintf(text, "Bienvenido %s", contexto->nombreActual);
    dibujar_texto(text, 10.5, 10.5, 2, 1);
    dibujar_texto(text, 10, 10, 2, 2);
    /*
    dibujar_texto("ABCDEFGHIJKLMNOPQRSTUVWXYZ",0, 20,1,0);
    dibujar_texto("0123456789", 0, 26, 1, 0);
    dibujar_texto("abcdefghijklmnopqrstuvwxyz", 0, 32, 1, 0);
    */
    //Menu
    char tMenu[CANTIDAD_ELEMENTOS_MENU][20] = {"JUGAR","DELUXE" , "OPCIONES", "SALIR"};
    for(int i = 0; i < CANTIDAD_ELEMENTOS_MENU; i++)
    {
        char linea[20];
        if(i==pos_puntero)
            sprintf(linea, "> %s", tMenu[i]);
        else
            sprintf(linea, "  %s", tMenu[i]);

        dibujar_texto(linea, CENTRADO + 0.5f, 46 + (i * 10), 2, 1);
        dibujar_texto(linea, CENTRADO, 45 + (i * 10), 2, 2);
    }

    dibujar_texto("®NODO 2026", 0, 95, 1, 2);
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
