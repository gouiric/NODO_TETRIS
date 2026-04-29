
//maincito
//Rivero
//prueba

#include <stdio.h>
#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include "mEstados.h"
#include <stdbool.h>
#include "dibujo.h"

#define ESCALA_VENTANA 2

#define CANT_COLOR 16
tGBT_ColorRGB color[16] = {
    {0x00, 0x00, 0x00}, //0  - negro
    {0x00, 0x00, 0xAA}, //1  - azul
    {0x00, 0xAA, 0x00}, //2  - verde
    {0x00, 0xAA, 0xAA}, //3  - cian
    {0xAA, 0x00, 0x00}, //4  - rojo
    {0xAA, 0x00, 0xAA}, //5  - magenta
    {0xAA, 0x55, 0x00}, //6  - marrón
    {0xAA, 0xAA, 0xAA}, //7  - gris claro
    {0x55, 0x55, 0x55}, //8  - gris oscuro
    {0x55, 0x55, 0xFF}, //9  - azul claro
    {0x55, 0xFF, 0x55}, //10 - verde claro
    {0x55, 0xFF, 0xFF}, //11 - cian claro
    {0xFF, 0x55, 0x55}, //12 - rojo claro
    {0xFF, 0x55, 0xFF}, //13 - magenta claro
    {0xFF, 0xFF, 0x55}, //14 - amarillo
    {0xFF, 0xFF, 0xFF}  //15 - blanco (transparente)
};

int main(int argc, char* argv[])
{
    int ANCHO_VENTANA = 320;
    int ALTO_VENTANA = 200;
    int ESCALA_V = 1;
    //Permitir al usuario elegir modo de video
    if(argc > 1){
        if(argv[1][0] == '-'){
            switch(argv[1][1]){
                case 'v':
                    ANCHO_VENTANA = 640;
                    ALTO_VENTANA = 480;
                    ESCALA_V = 2;
                    printf("Modo VGA\n");
                    break;
                case 'c':
                    ANCHO_VENTANA = 320;
                    ALTO_VENTANA = 200;
                    ESCALA_V = 1;
                    printf("Modo CGA\n");
                    break;
                default:
                    printf("Argumento desconocido.\n");
                case 'h':
                    printf("Modo de uso.\n-v\tModo VGA\n-c\tModo CGA\n");
                    return 1;
                    break;
            }
        }
    }

    //
    // inicializacion sistema GBT
    //
    if(gbt_iniciar() != 0){
        fprintf(stderr, "Error al iniciar GBT: %s", gbt_obtener_log());
        return -1;
    }
    char nombreVentana[128];
    if(gbt_crear_ventana(nombreVentana, ANCHO_VENTANA, ALTO_VENTANA, ESCALA_VENTANA) != 0){
        fprintf(stderr, "Error al crear ventana: %s", gbt_obtener_log());
        return -1;
    }
    if(gbt_aplicar_paleta(color, CANT_COLOR, GBT_FORMATO_888) != 0){
        fprintf(stderr, "Error al aplicar paleta %s\n", gbt_obtener_log());
        return -1;
    }   //Paleta inicial

    //
    // entorno juego
    //
    if(inicializar_contexto() == NULL){
        printf("Error al crear contexto\n");
        return -1;
    }
    if(inicializar_helper_dibujo(ANCHO_VENTANA, ALTO_VENTANA, ESCALA_V) == NULL){
        printf("Error al crear memoria para funciones de pantalla\n");
        return -1;
    }

    //bucle principal
    while(contexto->corriendo == true){

        correr();

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    //Funciones de cierre
    limpiar_contexto();
    limpiar_helper_pantalla();
    gbt_destruir_ventana();
    gbt_cerrar();

    return 0;
}
