#include "Pausa.h"
#include "GBT/gbt_entrada.h"
#include "dibujo.h"
#include "graficos.h"


void loop_dibujar_pausa()
{
    dibujar_filtro_pausa(8);
    //Esto lo podemos volar o hacer mas lindo

    //Lo que intente hacer es darle un recuadro al texto "en pausa"
    //Intento calcular el centro de pantalla y determino un ancho y un alto para esa caja
    //Una de las funciones dibujar_rect me sirve para darle un borde
    //Se podria hacer mejor, o directamente pasarle los datos harcodeados
    //Y nos ahorramos en cuentas
    int centro_x = pantalla->tab_offsetX + (pantalla->tam_tabX / 2);
    int centro_y = pantalla->tab_offsetY + (pantalla->tam_tabY / 2);

    int ancho_caja = 300;
    int alto_caja = 150;

    int caja_x = centro_x - (ancho_caja / 2);
    int caja_y = centro_y - (alto_caja / 2);
    dibujar_rect(caja_x, caja_y, ancho_caja +2, alto_caja + 2, 4);
    dibujar_rect(caja_x+1, caja_y +1, ancho_caja, alto_caja, 0);

    //Un contador de frames que me va a servir para darle el efecto de aparecer y desaparecer al texto

    //No se porque tiene que ser static esta variable, pero si no es static no funca
    static int frames_contador = 0;
    frames_contador++;

    if((frames_contador / 30) % 2 == 0)
    {
        dibujar_texto("EN PAUSA",35,40,2*pantalla->escala_v,14);
    }

    if(frames_contador >= 60)
    {
        frames_contador = 0;
    }

    ///inclusive quizas no hace falta darle ese recuadro, lo podriamos sacar. Por el momento existe para que se note mejor el texto
}

void loop_logica_pausa()
{
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    if(tecla == GBTK_ESCAPE)
    {
        cambiar_contexto(PANTALLA_MENU);
        return;
    }
    else if(tecla == GBTK_p)
    {
        cambiar_contexto(PANTALLA_TETRIS);
        return;
    }
}
