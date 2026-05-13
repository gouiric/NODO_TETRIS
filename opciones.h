#ifndef OPCIONES_H_INCLUDED
#define OPCIONES_H_INCLUDED

#include "dibujo.h"
#include "mEstados.h"

#define IZQUIERDA -1
#define DERECHA 1


typedef struct
{
    int resolucion_elegida;
    int velocidad_elegida;
    int paleta_elegida;
}Configuracion;


bool guardar_configuraciones(const char* nombre_archivo);
bool cargar_crear_archivo(const char* nombre_archivo);

extern Configuracion config_actual;

void dibujar_opciones();
void loop_opciones();

float obtener_velocidad_actual_ms();
int obtener_ancho_actual();
int obtener_alto_actual();

///Por el momento es medio auxiliar
void aplicar_cambios_graficos();


#endif // OPCIONES_H_INCLUDED
