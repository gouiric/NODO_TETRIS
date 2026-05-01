#include "tetris.h"
#include <stdlib.h>
#include "GBT/gbt_entrada.h"
#include "tablero.h"
#include "mEstados.h"
#include <stdio.h>



Tetris* tetris = NULL;

Tetris* inicializar_tetris(bool modo_dx){

    tetris = malloc(sizeof(Tetris));
    if(!tetris){
        return NULL;
    }

    inicialiar_tablero(&tetris->tablero);

    if(!tetris->tablero.matriz)
    {
        free(tetris);
        return NULL;
    }

    srand(time(NULL));
    tetris->modo_dx = modo_dx;
    tetris->tipo_pieza = tetris->modo_dx ? rand()%11 : rand()%7;
    cargar_pieza(&tetris->pieza, tetris->tipo_pieza);
    tetris->puntos = 0;
    tetris->contador_frames = 0;
    tetris->velocidad_ms = 1000;
    tetris->cant_piezas = 0;
    tetris->umbral_frames = 30;
    tetris->cont_fijacion = 0;
    tetris->contacto = false;

    return tetris;
}

void loop_dibujar_tetris()
{
    limpiar(0);
    dibujar_tablero(&tetris->tablero, (320 - (TABLERO_COLS * TAMANIO_BLOQUE)) / 2, 4);
    dibujar_pieza(&tetris->pieza, (320 - (TABLERO_COLS * TAMANIO_BLOQUE)) / 2, 4, tetris->modo_dx);
}

void loop_logica_tetris()
{
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    if(tecla == GBTK_ESCAPE)
    {
        printf("Volver a pantalla inicial\n");
        cambiar_contexto(PANTALLA_SPLASH);
        return;
    }
    if(tecla == GBTK_x)
    {
        rotar_pieza_activa(SENTIDO_HORARIO);
    }
    if(tecla == GBTK_z)
    {
        rotar_pieza_activa(SENTIDO_ANTIHORARIO);
    }

    mover_pieza(tecla);

    bool pieza_anclada = procesar_caida();

    if(pieza_anclada)
    {
        procesar_impacto();
    }

    if(perder())
    {
       cambiar_contexto(PANTALLA_SPLASH);
       return;
    }

}

void limpiar_tetris()
{
    if(!tetris)
        return;
    destruir_tablero(&tetris->tablero,TABLERO_FILAS);
    free(tetris);
    tetris = NULL;
}


void rotar_pieza_activa(uint8_t sentido)
{
    //Pieza aux que va estar rotada
    Pieza pieza_rotar = tetris->pieza;

    if(sentido == SENTIDO_HORARIO)
    {
        sentido_horario(pieza_rotar.matriz, tetris->pieza.matriz); //Esta funcion vive en pieza.h
    }
    else
    {
        sentido_antihorario(pieza_rotar.matriz, tetris->pieza.matriz); //Esta funcion vive en pieza.h
    }

    //si la pieza aux rotada no choca con nada entonces se la copiamos a nuestra pieza tetris
    if(!colision(&tetris->tablero,&pieza_rotar,pieza_rotar.x,pieza_rotar.y, tetris->modo_dx))
    {
        if(tetris->contacto) //Verificamos si hay o no contacto para saber si tenemos que resetear el cont_fijacion
        {
            tetris->cont_fijacion = 0;
        }
        for(int y = 0; y < ORDEN_PIEZA; y++)
        {
            for(int x = 0; x < ORDEN_PIEZA; x++)
            {
                tetris->pieza.matriz[y][x] = pieza_rotar.matriz[y][x];
            }
        }
    }

}

void mover_pieza(eGBT_Tecla tecla)
{
    int x = 0;
    int y = 0;

    if(tecla == GBTK_DERECHA)
        x = 1;
    else if(tecla == GBTK_IZQUIERDA)
        x = -1;
    else if(tecla == GBTK_ABAJO)
        y = 1;

    if(x != 0 || y != 0)
    {
        //En caso que no haya colision, le actualizamos las posiciones a nuestra pieza
        if(!colision(&tetris->tablero, &tetris->pieza, tetris->pieza.x +x, tetris->pieza.y + y,tetris->modo_dx))
        {
            tetris->pieza.x += x;
            tetris->pieza.y += y;
             //Este if verifica si bajamos la pieza manualmente o cae por si sola
            if(y == 1)
            {
                tetris->puntos += 1;
            }

            if(tetris->contacto)
            {
                tetris->cont_fijacion = 0;
            }
        }
    }
}
// Fucion que quizas se puede limpiar un poquito mas
bool procesar_caida()
{
    //Bandera para saber si la pieza se anclo al tablero o si sigue cayendo
    bool pieza_anclada = false;

    //Si no hay colicion, entonces estamos en el caso de que la pieza esta haciendo caida libre
    if(!colision(&tetris->tablero, &tetris->pieza, tetris->pieza.x , tetris->pieza.y +1,tetris->modo_dx))
    {
        tetris->contacto = false;
        tetris->contador_frames++;

        //Actualizamos sus frames
        if(tetris->contador_frames >= (uint32_t)tetris->umbral_frames)
        {
            tetris->pieza.y++;
            tetris->contador_frames = 0;
        }
    }
    //Caso que la pieza choco con el fondo del tablero o una pieza ya colocada
    else
    {
        tetris->contacto = true;
        tetris->cont_fijacion ++;

        if(tetris->cont_fijacion >= (uint32_t)tetris->umbral_frames * 0.5)
        {
            anclar_pieza(&tetris->tablero, &tetris->pieza, tetris->modo_dx);
            pieza_anclada = true;
        }
    }
    return pieza_anclada;
}

void calculo_puntos(int lineas_borradas)
{
    uint32_t puntos = 0;
    float multiplicador;

    if(lineas_borradas > 0)
    {
        switch(lineas_borradas)
        {
            case 1: puntos = 100; break;
            case 2: puntos = 300; break;
            case 3: puntos = 500; break;
            default: puntos =800; break;
        }
        multiplicador = 1000/tetris->velocidad_ms;
        tetris->puntos += (uint32_t)(puntos * multiplicador);
    }
}

void obtener_nueva_pieza()
{
    int nueva_pieza;

    do{
        nueva_pieza = tetris->modo_dx ? rand() % 11 :  rand()%7;
    }while(tetris->tipo_pieza == nueva_pieza);

    tetris->tipo_pieza = nueva_pieza;

    cargar_pieza(&tetris->pieza, tetris->tipo_pieza);
    //a
}

void actualizar_datos_tetris()
{
    tetris->cant_piezas++;

    if(tetris->cant_piezas % 10 == 0)
    {
        tetris->velocidad_ms *= 0.97;
        tetris->umbral_frames *= 0.97;
    }

    tetris->contador_frames = 0;
    tetris->cont_fijacion = 0;
    tetris->contacto = false;

}

bool perder()
{
    if(colision(&tetris->tablero,&tetris->pieza,tetris->pieza.x,tetris->pieza.y,tetris->modo_dx))
    {
        printf("Perdiste\n");
        return true;
    }
    return false;
}

void procesar_impacto()
{
    int lineas_borradas = limpiar_filas(&tetris->tablero);

    calculo_puntos(lineas_borradas);

    actualizar_datos_tetris();

    obtener_nueva_pieza();

    printf("\n==== INFO ====\n");
    printf("Lineas borradas: %d\n",lineas_borradas);
    printf("Puntaje Total: %d\n", tetris->puntos);
    printf("Piezas Caidas: %d\n", tetris->cant_piezas);
    printf("Velocidad: %.1f ms\n", tetris->velocidad_ms);
    printf("Tolerancia: %.1f ms\n", tetris->velocidad_ms * 0.5f);
    printf("=====================\n");
}
