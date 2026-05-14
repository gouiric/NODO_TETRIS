#ifndef TETRIS_H_INCLUDED
#define TETRIS_H_INCLUDED

#include "tablero.h"
#include "piezas.h"
#include <time.h>

#define SENTIDO_ANTIHORARIO 0
#define SENTIDO_HORARIO 1

/*
            - Por el momento no hacemos un conteo historio de las lineas borradas (se puede agregar)
            - Por el momento el archivo no guarda tampoco ese dato
            - Por el momento el archivo tampoco guarda los datos de la pieza anterior y la siguiente
            - Por el momento el archivo no guarda ancho del tablero para el modo dx
            - Por el momento no hacemos un conteo de nivel y tampoco el archivo lo guarda (se puede agregar)
*/

typedef struct{
    Tablero tablero;
    Pieza pieza;
    uint8_t tipo_pieza;
    uint32_t contador_frames;
    uint32_t puntos;
    uint32_t cant_piezas;
    float velocidad_ms;
    float umbral_frames;
    uint32_t cont_fijacion;
    bool contacto;
    bool modo_dx;
    bool en_pausa;
}Tetris;

//Por el momento lo creo aca
typedef struct
{
    uint8_t matriz_tablero[TABLERO_FILAS][TABLERO_COLS];
    Pieza Pieza;
    float velocidad_ms;
    int cant_piezas;
    int puntos;
    int tipo_pieza;
    bool modo_dx;
}PartidaGuardada;


//
// Los datos relacionados a tetris ahora existen en una mochila independiente al contexto;
//
extern Tetris* tetris;

Tetris* inicializar_tetris(bool modo_dx);
void limpiar_tetris();

//
// no es necesario separar dibujar y logica en dos funciones separadas
// se separan para mantener legibilidad en el codigo
//
void loop_dibujar_tetris();
void loop_logica_tetris();

//
void rotar_pieza_activa(uint8_t sentido);
void mover_pieza(eGBT_Tecla tecla);
bool procesar_caida();
void calculo_puntos(int lineas_borradas);
void obtener_nueva_pieza();
void actualizar_datos_tetris();
bool perder();
void procesar_impacto();
void dibujar_filtro_pausa(uint8_t col);

///Logica para el archivo

bool guardar_partida(const char* nombre_archivo);
bool cargar_partida(const char* nombre_archivo);

#endif
