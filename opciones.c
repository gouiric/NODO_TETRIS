#include "opciones.h"
#include "GBT/gbt_entrada.h"
#include "stdio.h"
#include "GBT/gbt.h"
#include "GBT/gbt_graficos.h"
#include "dibujo.h"
#include <string.h>

static char* paletas[] = {"CLASICA", "GAMEBOY", "NEON"};
static char* velocidades[] = {"1000 ms","500 ms","250 ms"};
static char* resoluciones[] = {"320x240","640x480"};

static const float valores_velocidades[] = {1000, 500, 250};
static const int resoluciones_ancho[] = {320, 640};
static const int resoluciones_alto[] = {200, 480};

static void modificar_valor_horizontal(int direccion);

Configuracion config_actual;

//Variable cuyo proposito es determinar en que opcion estamos parados
//0 - Velocidad; 1 - Resolucion; 2 - Paleta; 3 - Salir; 4 - Guardar
static int opcion_selec = 0;

bool guardar_configuraciones(const char* nombre_archivo)
{
    FILE* pf = fopen(nombre_archivo,"wb");

    if(!pf)
    {
        printf("Error al abrir el archivo\n");
        return false;
    }
    fwrite(&config_actual,sizeof(config_actual),1,pf);

    fclose(pf);

    return true;
}

bool cargar_crear_archivo(const char* nombre_archivo)
{
    FILE* pf = fopen(nombre_archivo,"rb");

    if(!pf)
    {
        printf("El archivo no exite.. Creando....\n");
        config_actual.paleta_elegida = 0;
        config_actual.resolucion_elegida = 0;
        config_actual.velocidad_elegida = 0;
        config_actual.escala_ventana = 2;

        return guardar_configuraciones(nombre_archivo);
    }

    printf("El archivo existe, leyendo datos....\n");
    fread(&config_actual,sizeof(Configuracion),1,pf);
    fclose(pf);

    return true;
}


void dibujar_opciones()
{
    limpiar(0);

    dibujar_fondo();

    dibujar_texto("Menu Opciones",28,2,2*pantalla->escala_v,11);

    dibujar_texto("Velocidad de la pieza",5,30,pantalla->escala_v,11);
    dibujar_texto(*(velocidades + config_actual.velocidad_elegida),60,30,pantalla->escala_v,(opcion_selec == 0) ? 14:11);

    dibujar_texto("Resolucion de pantalla",5,45,pantalla->escala_v,11);
    dibujar_texto(*(resoluciones + config_actual.resolucion_elegida),60,45,pantalla->escala_v,(opcion_selec == 1) ? 14:11);

    dibujar_texto("Paletas de colores",5,60,pantalla->escala_v,11);
    dibujar_texto(*(paletas + config_actual.paleta_elegida),60,60,pantalla->escala_v,(opcion_selec == 2) ? 14:11);

    dibujar_texto("SALIR",5,90,pantalla->escala_v,(opcion_selec == 3) ? 14:11);
    dibujar_texto("GUARDAR CAMBIOS",70,90,pantalla->escala_v,(opcion_selec == 4) ? 14:11);



}

void loop_opciones()
{
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    ///Navegacion Vertical

    if(tecla == GBTK_ARRIBA)
    {
        opcion_selec = (opcion_selec - 1 + 5)%5;
    }
    else if(tecla == GBTK_ABAJO)
    {
        opcion_selec = (opcion_selec + 1 + 5)%5;
    }

    ///Navegacion Horizontal

    else if(tecla == GBTK_DERECHA)
    {
        modificar_valor_horizontal(DERECHA);
    }
    else if(tecla == GBTK_IZQUIERDA)
    {
        modificar_valor_horizontal(IZQUIERDA);
    }

    else if(tecla == GBTK_ENTER)
    {
        if(opcion_selec == 3)
        {
            cambiar_contexto(PANTALLA_MENU);
        }
        else if(opcion_selec == 4)
        {
            guardar_configuraciones(ARCHIVO_OP);
            aplicar_cambios_graficos();
            cambiar_contexto(PANTALLA_MENU);
        }
    }
}

void modificar_valor_horizontal(int direccion)
{
    if(opcion_selec == 0)
    {
        config_actual.velocidad_elegida = (config_actual.velocidad_elegida + direccion + 3)%3;
    }
    else if(opcion_selec == 1)
    {
        config_actual.resolucion_elegida = (config_actual.resolucion_elegida + direccion + 2) %2;
    }
    else if(opcion_selec == 2)
    {
        config_actual.paleta_elegida = (config_actual.paleta_elegida + direccion + 3)%3;
    }
}

//Apartir de estas funciones puedo compartir los datos con las partes del programa que lo requieran
float obtener_velocidad_actual_ms()
{
    return *(valores_velocidades + config_actual.velocidad_elegida);
}
int obtener_ancho_actual()
{
    return *(resoluciones_ancho + config_actual.resolucion_elegida);
}
int obtener_alto_actual()
{
    return *(resoluciones_alto + config_actual.resolucion_elegida);
}
int obtener_escala_actual(){
    return config_actual.escala_ventana;
}
////////////////////////////////////////////////7
//Por el momento es aux

extern tGBT_ColorRGB color[16];

void aplicar_cambios_graficos()
{
    limpiar_helper_pantalla();
    gbt_destruir_ventana();

    int ancho = obtener_ancho_actual();
    int alto = obtener_alto_actual();

    int escala = (ancho == 640) ? 2:1;

    gbt_crear_ventana("Soy un cambio", ancho, alto, config_actual.escala_ventana);
    gbt_aplicar_paleta(color, 16, GBT_FORMATO_888);
    inicializar_helper_dibujo(ancho, alto,escala);
}
