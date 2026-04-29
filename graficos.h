#ifndef GRAFICOS_H_INCLUDED
#define GRAFICOS_H_INCLUDED
#include <stdint.h>

#define CANTIDAD_COLORES_SPRITE 4

//FUENTE PARA LA PANTALLA SPLASH
// innecesariamente grande
extern uint8_t M_letraT[16][16];
extern uint8_t M_letraE[16][16];
extern uint8_t M_letraR[16][16];
extern uint8_t M_letraI[16][16];
extern uint8_t M_letraS[16][16];

//FUENTE NORMAL 8x8
extern uint8_t fuente[36][8][8];

//MACROS LETRAS 0-25: A-Z, 26-35: 0-9
#define L_A 0
#define L_B 1
#define L_C 2
#define L_D 3
#define L_E 4
#define L_F 5
#define L_G 6
#define L_H 7
#define L_I 8
#define L_J 9
#define L_K 10
#define L_L 11
#define L_M 12
#define L_N 13
#define L_O 14
#define L_P 15
#define L_Q 16
#define L_R 17
#define L_S 18
#define L_T 19
#define L_U 20
#define L_V 21
#define L_W 22
#define L_X 23
#define L_Y 24
#define L_Z 25
#define L_0 26
#define L_1 27
#define L_2 28
#define L_3 29
#define L_4 30
#define L_5 31
#define L_6 32
#define L_7 33
#define L_8 34
#define L_9 35

//Sprite 16x16 con paleta 4 colores
typedef struct{
    uint8_t (*mapa)[16];
    uint8_t colores[CANTIDAD_COLORES_SPRITE];
}car16;


//FUENTE SPLASH EN FORMATO SPRITE
extern car16 C_letraT;
extern car16 C_letraE;
extern car16 C_letraR;
extern car16 C_letraI;
extern car16 C_letraS;

void rotar_paletas_c16(car16**, int);
//car16* cargar_letra(car16* dato, uint8_t* mapa[16][16], uint8_t col[4]);

#endif // GRAFICOS_H_INCLUDED
