#include "tablero.h"
#include <stdlib.h>
#include <stdio.h>



///Creamos nuestra matriz tablero
void inicialiar_tablero(Tablero* t)
{
    t->matriz = malloc(TABLERO_FILAS * sizeof(uint8_t*));

    if(!t->matriz)
    {
        printf("Error, no hay memoria disponible para la matriz\n");
        return;
    }

    uint8_t** ultimo = t->matriz + TABLERO_FILAS - 1;

    for(uint8_t** i = t->matriz; i <= ultimo; i++ )
    {
        *i = calloc(TABLERO_COLS, sizeof(uint8_t));

        if(!*i)
        {
            destruir_tablero(t, i - t->matriz);
            return;
        }
    }
}

///Dibujamos el trablero en pantalla
void dibujar_tablero(Tablero* t, uint16_t offsetX, uint16_t offsetY)
{
    for(int y = 0; y < TABLERO_FILAS; y++)
    {
        for(int x= 0; x < TABLERO_COLS; x++)
        {
            ///Si para una posicion de fila y columna no hay un cero, entonces dibujamos el color de la pieza
            if(t->matriz[y][x] != 0)
            {

                dibujar_rect(offsetX + (x *TAMANIO_BLOQUE), offsetY + (y * TAMANIO_BLOQUE),TAMANIO_BLOQUE -1 , TAMANIO_BLOQUE -1, t->matriz[y][x]);

            }
            ///Si no, entonces le pasamos como color un gris claro (fijarse la paleta de colores en el main por las dudas)
            else
            {
                dibujar_rect(offsetX + (x * TAMANIO_BLOQUE), offsetY + (y * TAMANIO_BLOQUE),TAMANIO_BLOQUE -4, TAMANIO_BLOQUE-4, 8);

            }

        }
    }
}

///Funcion auxiliar para verificar si se completo una fila o no

bool FilaCompleta(uint8_t* plec)
{
    for(uint8_t* i = plec; i < plec + TABLERO_COLS; i++)
    {
        if(*i == 0)
        {
            return false;
        }
    }
    return true;
}

///Funcion encargada de limpiar las filas, por el momento es void, quizas mas adelante nos interesa que sea booleana o entero

int limpiar_filas(Tablero* t)
{
    uint8_t** pinicio = t->matriz;
    uint8_t** plectura = t->matriz + (TABLERO_FILAS -1);
    uint8_t** pescritura = t->matriz + (TABLERO_FILAS - 1);
    int lineas_borradas = 0;

    while(plectura >= pinicio)
    {
        if(!FilaCompleta(*plectura))
        {
            if(pescritura != plectura)
            {
                uint8_t *temp = *pescritura;
                *pescritura = *plectura;
                *plectura = temp;
            }
            pescritura--;
        }
        else
        {
            lineas_borradas++;
        }
        plectura--;
    }

    while(pescritura >= pinicio)
    {
        memset(*pescritura,0,TABLERO_COLS);
        pescritura--;
    }
    return lineas_borradas;
}

///Funcion encargada de verificar si hay colicion por parte de una pieza
bool colision(Tablero* t, Pieza* p, int ox, int oy, bool modo_dx)
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if(p->matriz[y][x] != 0)
            {
                ///La variable tab_x y tab_y, almacenan una posicion, toma la posicion ox (representa la posicion que se movio)
                /// ox + x; oy + y; lo que estamos haciendo es mover esa pieza, trasladamos esa pieza y vemos si hay o no colicion
                int tab_x = ox + x;
                int tab_y = oy + y;

                if(modo_dx)
                {
                    tab_x = (tab_x % TABLERO_COLS + TABLERO_COLS) % TABLERO_COLS;
                }
                else if(tab_x < 0 || tab_x >= TABLERO_COLS)
                    return true;

                if(tab_y >= TABLERO_FILAS)
                    return true;
                ///Es te if, verifica si la pieza en la posicion [tab_y][tab_x] existe una pieza ya cargada en el tablero
                ///En caso de que existe, entonces quiere decir que la pieza colisiono con la pieza que estaba en el tablero
                if(tab_y >= 0 && t->matriz[tab_y][tab_x] != 0)
                    return true;
            }
        }
    }
    return false;
}

///Funcion encargada de anclar la pieza con la matriz del tablero

void anclar_pieza(Tablero* t, Pieza* p, bool modo_dx)
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if(p->matriz[y][x] != 0)
            {
                ///tab_x y tab_y son las posiciones para el tablero, toma la posicion de la pieza tanto en x como en y
                int tab_x = p->x + x;
                int tab_y = p->y + y;

                if(modo_dx)
                {
                    tab_x = (tab_x % TABLERO_COLS + TABLERO_COLS)%TABLERO_COLS;
                }

                if(tab_y >= 0 && tab_y < TABLERO_FILAS && tab_x >= 0 && tab_x < TABLERO_COLS)
                {
                    ///Copiamos el color de la pieza en la matriz, o sea se almacena un numero de la paleta de colores
                    t->matriz[tab_y][tab_x] = p->color;
                }
            }
        }
    }
}

void destruir_tablero(Tablero* t, int filas)
{
    if(filas <= 0)
    {
        free(t->matriz);
        t->matriz = NULL;
        return;
    }

    uint8_t** ultimo = t->matriz + filas - 1;

    for(uint8_t** i = t->matriz; i <= ultimo; i++)
    {
        free(*i);
    }

    free(t->matriz);
    t->matriz = NULL;
}
