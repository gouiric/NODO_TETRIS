#include "splash.h"
#include "GBT/gbt_entrada.h"
#include "dibujo.h"
#include "mEstados.h"
#include <stdio.h>
#include "graficos.h"

void dibujar_splash(){
    limpiar(7);
    dibujar_fondo();
    //dibujar_rect(0, porc_a_pixel(60, pantalla->alto), pantalla->ancho, porc_a_pixel(40, pantalla->alto), 8);
    //dibujar logo
    int offV = 0;
    if(pantalla->escala_v == 2)
        offV = 5;
    dibujar_spr_porc(&C_letraT, 16, 16, 10, 10+offV, 3 * pantalla->escala_v);
    dibujar_spr_porc(&C_letraE, 16, 16, 24, 10+offV, 3 * pantalla->escala_v);
    dibujar_spr_porc(&C_letraT2, 16, 16, 38, 10+offV, 3* pantalla->escala_v);
    dibujar_spr_porc(&C_letraR, 16, 16, 52, 10+offV, 3 * pantalla->escala_v);
    dibujar_spr_porc(&C_letraI, 16, 16, 62, 11+offV, 3 * pantalla->escala_v);
    dibujar_spr_porc(&C_letraS, 16, 16, 72, 10+offV, 3 * pantalla->escala_v);

    dibujar_texto("Presiona cualquier tecla", CENTRADO, 75, 2, 3);
}

void loop_splash(){
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    if(tecla == GBTK_ESCAPE){
        contexto->corriendo = false;
    }else if(tecla != GBTK_DESCONOCIDA){
        printf("Pasando a eleccion de nombre\n");
        cambiar_contexto(PANTALLA_NOMBRE);
    }
    //Animacion titulo
    contexto->escenaActual->contador++;
    if(contexto->escenaActual->contador == 20){
        contexto->escenaActual->contador = 0;
        car16* letras[5] =  {&C_letraT, &C_letraE, &C_letraR, &C_letraI, &C_letraS}; //Solucion a lo bruto
        rotar_paletas_c16(letras, 5);
    }
}
