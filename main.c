#include <stdio.h>
#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include "mEstados.h"
#include <stdbool.h>
#include "dibujo.h"
#include "opciones.h"
#include <time.h>

#define CANT_COLOR 30
tGBT_ColorRGB color[30] = {
    {0xFF, 0xFF, 0xFF},     //0-blanco
    {0x00, 0x00, 0x00},     //1-negro
    {0xFA, 0xFA, 0xFA},     //2-Casi blanco
    {0xAA, 0xAA, 0xAA},     //3-Gris
    {0x00, 0x00, 0x52},     //4-Azul marino(Fondo1)
    {0x10, 0x0F, 0x5B},     //5-Azul medianoche(Fondo1 acento)
    {0x3D, 0x11, 0x3D},     //6-Lila medianoche(Fondo2)
    {0x27, 0x10, 0x4C},     //7-Amatista oscura(Fondo2 acento)
    {0x60, 0xD7, 0xD7},     //8-Pieza I(Sombra)
    {0x6A, 0xEC, 0xEC},     //9-Pieza I(Base)
    {0xAE, 0xE9, 0xE2},     //10-Pieza I(Highlight)
    {0x19, 0x19, 0xD5},     //11-Pieza J(Sombra)
    {0x1C, 0x1C, 0xEA},     //12-Pieza J(Base)
    {0x87, 0x81, 0xE1},     //13-Pieza J(Highlight)
    {0x7E, 0x51, 0x22},     //14-Pieza L(Sombra)
    {0xD7, 0x7E, 0x1F},     //15-Pieza L(Base)
    {0xEB, 0xBF, 0x8F},     //16-Pieza L(Highlight)
    {0x8F, 0x89, 0x24},     //17-Pieza O(Sombra)
    {0xE5, 0xDA, 0x0F},     //18-Pieza O(Base)
    {0xD7, 0xD2, 0x6C},     //19-Pieza O(Highlight)
    {0x33, 0x8F, 0x24},     //20-Pieza S(Sombra)
    {0x2D, 0xE6, 0x10},     //21-Pieza S(Base)
    {0x7B, 0xD8, 0x6D},     //22-Pieza S(Highlight)
    {0x8F, 0x24, 0x24},     //23-Pieza Z(Sombra)
    {0xE6, 0x10, 0x10},     //24-Pieza Z(Base)
    {0xD8, 0x6D, 0x6D},     //25-Pieza Z(Highlight)
    {0x6A, 0x2C, 0x8C},     //26-Pieza T(Sombra)
    {0x9C, 0x1F, 0xE0},     //27-Pieza T(Base)
    {0xB3, 0x74, 0xD5},     //28-Pieza T(Highlight)
    {0xFF, 0xFF, 0xFF}      //29-Transparente
};

int main(int argc, char* argv[])
{
    cargar_crear_archivo(ARCHIVO_OP);
    int ESCALA_VENTANA = 2;
    int ESCALA_V = 1;
    //Permitir al usuario elegir modo de video
    if(argc > 1){
        for(int i = 1; i < argc; i++)
            {
                if(argv[i][0] == '-'){
                    if(argv[i][1] == 'v' || argv[i][1] == 'V'){
                        config_actual.resolucion_elegida = 1;
                    }else if(argv[i][1] == 'c' || argv[i][1] == 'C'){
                        config_actual.resolucion_elegida = 0;
                    }else if(argv[i][1] > '0' && argv[i][1] <= '9'){
                        config_actual.escala_ventana = argv[i][1] - '0';
                    }else{
                        printf("Opcion %s desconocida\n",argv[i]);
                        printf("Modo de uso Ventana.exe <argumentos>\n");
                        printf("Argumentos:\n");
                        printf(" -v Resolucion logica VGA (640x480)\n");
                        printf(" -c Resolucion logica CGA (320x200)\n");
                        printf(" -N Escala de resolucion en N pixeles. Ej -2\n");
                    }
                }
            }
        guardar_configuraciones(ARCHIVO_OP);
    }

    int ANCHO_VENTANA = obtener_ancho_actual();
    int ALTO_VENTANA = obtener_alto_actual();
    ESCALA_V = (ANCHO_VENTANA == 640) ? 2: 1;
    ESCALA_VENTANA = obtener_escala_actual();

    //
    // inicializacion sistema GBT
    //
    if(gbt_iniciar() != 0){
        fprintf(stderr, "Error al iniciar GBT: %s", gbt_obtener_log());
        return -1;
    }
    char nombreVentana[128];
    sprintf(nombreVentana,"Tetris_NODO");
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

    semilla_fondo(time(NULL));
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
