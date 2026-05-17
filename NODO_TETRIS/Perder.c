#include "Perder.h"
#include "GBT/gbt_entrada.h"
#include "dibujo.h"
#include "graficos.h"
#include "tetris.h"


void loop_dibujar_perder()
{
    dibujar_texto("PERDISTE",35,40,2*pantalla->escala_v,14);
}

void loop_logica_perder()
{
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    if(tecla == GBTK_ESCAPE)
    {
        cambiar_contexto(PANTALLA_MENU);
    }
    else if(tecla == GBTK_ENTER)
    {
        if(contexto->modo_tetris)
        {
            cambiar_contexto(PANTALLA_DELUXE);
        }
        else
        {
            cambiar_contexto(PANTALLA_TETRIS);
        }
        return;
    }
}
