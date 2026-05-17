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

//Paletas de colores
#define CANT_COLOR 30
tGBT_ColorRGB colorDefault[CANT_COLOR] = {
    {0xFF, 0xFF, 0xFF},     //0-blanco
    {0x00, 0x00, 0x00},     //1-negro
    {0xFA, 0xFA, 0xFA},     //2-Casi blanco
    {0xAA, 0xAA, 0xAA},     //3-Gris
    {0x00, 0x00, 0x52},     //4-Azul marino(Fondo1)
    {0x10, 0x0F, 0x5B},     //5-Azul medianoche(Fondo1 acento)
    {0x3D, 0x11, 0x3D},     //6-Lila medianoche(Fondo2)
    {0x27, 0x10, 0x4C},     //7-Amatista oscura(Fondo2 acento)
    {0x4A, 0x5A, 0x47},     //8-Pieza I(Sombra)
    {0x43, 0x54, 0x3D},     //9-Pieza I(Base)
    {0x3B, 0x4D, 0x33},     //10-Pieza I(Highlight)
    {0x43, 0x54, 0x3d},     //11-Pieza J(Sombra)
    {0x3B, 0x4D, 0x33},     //12-Pieza J(Base)
    {0x2B, 0x40, 0x1E},     //13-Pieza J(Highlight)
    {0x3B, 0x4D, 0x33},     //14-Pieza L(Sombra)
    {0x2B, 0x40, 0x1E},     //15-Pieza L(Base)
    {0x3E, 0x51, 0x32},     //16-Pieza L(Highlight)
    {0x43, 0x54, 0x3D},     //17-Pieza O(Sombra)
    {0x3B, 0x4D, 0x33},     //18-Pieza O(Base)
    {0x2B, 0x40, 0x1E},     //19-Pieza O(Highlight)
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

tGBT_ColorRGB colorGameboy[CANT_COLOR] = {
    {0xFF, 0xFF, 0xFF},     //0-blanco
    {0x00, 0x00, 0x00},     //1-negro
    {0xFA, 0xFA, 0xFA},     //2-Casi blanco
    {0xAA, 0xAA, 0xAA},     //3-Gris
    {0x34, 0x3F, 0x11},     //4-Verde LCD Lavado(Fondo1)
    {0x32, 0x40, 0x28},     //5-Azul medianoche(Fondo1 acento)
    {0x64, 0x6F, 0x41},     //6-Lila medianoche(Fondo2)
    {0x52, 0x60, 0x38},     //7-Amatista oscura(Fondo2 acento)
    {0x1F, 0x6E, 0x12},     //8-Pieza I(Sombra)
    {0x1F, 0x6E, 0x12},     //9-Pieza I(Base)
    {0xFA, 0xFA, 0xFA},     //10-Pieza I(Highlight)
    {0x20, 0x20, 0x20},     //11-Pieza J(Sombra)
    {0x8A, 0x8A, 0x8A},     //12-Pieza J(Base)
    {0xFA, 0xFA, 0xFA},     //13-Pieza J(Highlight)
    {0x1F, 0x6E, 0x12},     //14-Pieza L(Sombra)
    {0x1F, 0x6E, 0x12},     //15-Pieza L(Base)
    {0xFA, 0xFA, 0xFA},     //16-Pieza L(Highlight)
    {0x10, 0x10, 0x10},     //17-Pieza O(Sombra)
    {0x8A, 0x8A, 0x8A},     //18-Pieza O(Base)
    {0xFA, 0xFA, 0xFA},     //19-Pieza O(Highlight)
    {0x1F, 0x6E, 0x12},     //20-Pieza S(Sombra)
    {0x1F, 0x6E, 0x12},     //21-Pieza S(Base)
    {0xFA, 0xFA, 0xFA},     //22-Pieza S(Highlight)
    {0x00, 0x00, 0x00},     //23-Pieza Z(Sombra)
    {0x8A, 0x8A, 0x8A},     //24-Pieza Z(Base)
    {0xFA, 0xFA, 0xFA},     //25-Pieza Z(Highlight)
    {0x1F, 0x6E, 0x12},     //26-Pieza T(Sombra)
    {0x1F, 0x6E, 0x12},     //27-Pieza T(Base)
    {0xFA, 0xFA, 0xFA},     //28-Pieza T(Highlight)
    {0xFF, 0xFF, 0xFF}      //29-Transparente
};

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

void aplicar_cambios_graficos()
{
    limpiar_helper_pantalla();
    gbt_destruir_ventana();

    int ancho = obtener_ancho_actual();
    int alto = obtener_alto_actual();

    int escala = (ancho == 640) ? 2:1;

    //Aca deberiamos checkear que la memoria dinamica se genere correctamente
    gbt_crear_ventana("Soy un cambio", ancho, alto, config_actual.escala_ventana);
    aplicar_paleta();
    inicializar_helper_dibujo(ancho, alto,escala);
}

void aplicar_paleta(){
    if(config_actual.paleta_elegida == 0)
        gbt_aplicar_paleta(colorDefault, CANT_COLOR, GBT_FORMATO_888);
    if(config_actual.paleta_elegida == 1)
        gbt_aplicar_paleta(colorGameboy, CANT_COLOR, GBT_FORMATO_888);
}
