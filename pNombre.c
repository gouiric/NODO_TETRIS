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
    int largo = (int)round((8.0*pantalla->escala_v/pantalla->ancho)*100);
    if(contexto->tamanioNombre > 0)
    {
        dibujar_texto(contexto->nombreActual, 50 - (largo * contexto->tamanioNombre), 40, 3, 0);
    }


}

///Por el momento solo toma nombres en minuscula, y por el momento no se acepta espacios
void loop_pantalla_nombre(){
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();
    char* pchar = contexto->nombreActual + contexto->tamanioNombre;
    char letra;

    if(tecla == GBTK_ESCAPE){
        printf("Esto hay que sacarlo\n");
        cambiar_contexto(PANTALLA_SPLASH);
    }
    if( contexto->tamanioNombre < 10)
    {
        if(tecla >= GBTK_a && tecla <= GBTK_z)
        {
            letra = tecla - GBTK_a + 'a';
            *pchar = letra;
            pchar++;
            contexto->tamanioNombre++;
        }
        if(tecla >= GBTK_0 && tecla <= GBTK_9)
        {
            letra = tecla - GBTK_0 + '0';
            *pchar = letra;
            pchar++;
            contexto->tamanioNombre++;
        }
    }
    if(tecla == GBTK_RETROCESO && contexto->tamanioNombre > 0)
    {
        pchar--;
        contexto->tamanioNombre--;
    }
    if(tecla == GBTK_ENTER && contexto->tamanioNombre > 0)
    {
        cambiar_contexto(PANTALLA_MENU);
        return;
    }
    *pchar = '\0';
}
