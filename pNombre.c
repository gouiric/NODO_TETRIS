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
    //
    dibujar_spr_mono_porc(&fuente[L_E][0][0], 8, 8, 10, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_S][0][0], 8, 8, 15, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_C][0][0], 8, 8, 20, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_R][0][0], 8, 8, 25, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_I][0][0], 8, 8, 30, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_B][0][0], 8, 8, 35, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_E][0][0], 8, 8, 40, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_T][0][0], 8, 8, 45, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_U][0][0], 8, 8, 50, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_N][0][0], 8, 8, 55, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_O][0][0], 8, 8, 60, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_M][0][0], 8, 8, 65, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_B][0][0], 8, 8, 70, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_R][0][0], 8, 8, 75, 10, 2 * pantalla->escala_v, 0);
    dibujar_spr_mono_porc(&fuente[L_E][0][0], 8, 8, 80, 10, 2 * pantalla->escala_v, 0);


}

void loop_pantalla_nombre(){
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    if(tecla == GBTK_ESCAPE){
        contexto->corriendo = false;
    }else if(tecla != GBTK_DESCONOCIDA){
        if(tecla >= GBTK_a && tecla <=GBTK_z){
            char letra = tecla - GBTK_a + 'a';
            printf("char:%c\n",letra);
            contexto->nombreActual[contexto->tamanioNombre] = letra;
            contexto->tamanioNombre++;
        }else if(tecla == GBTK_ENTER){
            contexto->nombreActual[contexto->tamanioNombre] = '\0';
            printf("Nombre: %s\n",contexto->nombreActual);
        }

    }
}
