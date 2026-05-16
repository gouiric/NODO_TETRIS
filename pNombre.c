#include "pNombre.h"
#include "dibujo.h"
#include "pNombre.h"
#include "graficos.h"
#include "GBT/gbt_entrada.h"
#include "mEstados.h"
#include <math.h>
#include <stdio.h>

void dibujar_pantalla_nombre(){
    //Texto fijo
    limpiar(9);
    //
    // REEMPLAZAR POR UNA FUNCION MEJOR
    // VINO LA FUNCION MEJOR
    dibujar_texto("escribe tu nombre", 10, 10, 2 * pantalla->escala_v, 0);
    if(contexto->tamanioNombre > 0)
    {
        dibujar_texto(contexto->nombreActual, CENTRADO, 40, 3, 0);
    }


}

void loop_pantalla_nombre(){
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    if(tecla == GBTK_ESCAPE){
        printf("Esto hay que sacarlo\n");
        cambiar_contexto(PANTALLA_SPLASH);
    }else if(tecla == GBTK_RETROCESO)
    {
            if(contexto->tamanioNombre > 0){
                contexto->nombreActual[contexto->tamanioNombre] = '\0';
                contexto->tamanioNombre -= 1;
                }
    }else if(tecla != GBTK_DESCONOCIDA){
        if(tecla >= GBTK_a && tecla <= GBTK_z){
            char letra = tecla - GBTK_a + 'a';
            printf("char:%c\n",letra);
            contexto->nombreActual[contexto->tamanioNombre] = letra;
            contexto->tamanioNombre++;
        }else if(tecla == GBTK_ENTER && contexto->tamanioNombre > 0){
            contexto->nombreActual[contexto->tamanioNombre] = '\0';
            printf("Nombre: %s\n",contexto->nombreActual);
            cambiar_contexto(PANTALLA_MENU);
            printf("Pasando a menu\n");
        }

    }
}
