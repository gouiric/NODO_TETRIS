#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED
#include <stdint.h>

#define CANTIDAD_COLORES_SPRITE 4

extern uint8_t M_letraT[16][16];
extern uint8_t M_letraE[16][16];
extern uint8_t M_letraR[16][16];
extern uint8_t M_letraI[16][16];
extern uint8_t M_letraS[16][16];

typedef struct{
    uint8_t (*mapa)[16];
    uint8_t colores[CANTIDAD_COLORES_SPRITE];
}car16;

extern car16 C_letraT;
extern car16 C_letraE;
extern car16 C_letraR;
extern car16 C_letraI;
extern car16 C_letraS;

void rotar_paletas_c16(car16**, int);
//car16* cargar_letra(car16* dato, uint8_t* mapa[16][16], uint8_t col[4]);

#endif // GRAFICOS_H_INCLUDED
