#include "piezas.h"
#include "tablero.h"


/// Los colores
const uint8_t COLORES_PIEZAS[7] = {3, 14, 2, 12, 13, 9, 1};

/// Las 7 matrices de las piezas

const uint8_t FORMA_I[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 1, 1},
    {0, 0, 0, 0},
    {0, 0, 0, 0}
};

const uint8_t FORMA_O[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

const uint8_t FORMA_T[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

const uint8_t FORMA_L[4][4] = {
    {0, 0, 0, 0},
    {0, 0, 1, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

const uint8_t FORMA_J[4][4] = {
    {0, 0, 0, 0},
    {1, 0, 0, 0},
    {1, 1, 1, 0},
    {0, 0, 0, 0}
};

const uint8_t FORMA_S[4][4] = {
    {0, 0, 0, 0},
    {0, 1, 1, 0},
    {1, 1, 0, 0},
    {0, 0, 0, 0}
};

const uint8_t FORMA_Z[4][4] = {
    {0, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 0, 0}
};

///Un viejo conocido ya...
extern void dibujarRectangulo(uint16_t x, uint16_t y, uint16_t ancho, uint16_t alto, uint8_t color);

///Toma como argumento pieza (estructura), y un tipo de pieza (0,1,2,3,4,5,6)
void cargar_pieza(Pieza *p, int tipo_pieza)
{
    p->x = 3;
    p->y = -1;
    p->color = COLORES_PIEZAS[tipo_pieza];

    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            switch(tipo_pieza)
            {
                case 0: p->matriz[y][x] = FORMA_I[y][x]; break;
                case 1: p->matriz[y][x] = FORMA_O[y][x]; break;
                case 2: p->matriz[y][x] = FORMA_T[y][x]; break;
                case 3: p->matriz[y][x] = FORMA_L[y][x]; break;
                case 4: p->matriz[y][x] = FORMA_J[y][x]; break;
                case 5: p->matriz[y][x] = FORMA_S[y][x]; break;
                case 6: p->matriz[y][x] = FORMA_Z[y][x]; break;
                default: p->matriz[y][x] = FORMA_I[y][x];break;
            }
        }
    }
}

void dibujar_pieza(Pieza* p, uint16_t x_tablero, uint16_t y_tablero)
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if(p->matriz[y][x] != 0)
            {
                if((p->y + y) >= 0)
                {
                    uint16_t pos_pantalla_x = x_tablero + ((p->x + x)*TAMANIO_BLOQUE);
                    uint16_t pos_pantalla_y = y_tablero + ((p->y + y)*TAMANIO_BLOQUE);
                    dibujarRectangulo(pos_pantalla_x,pos_pantalla_y,TAMANIO_BLOQUE - 1, TAMANIO_BLOQUE - 1, p->color);
                }
            }
        }
    }
}
