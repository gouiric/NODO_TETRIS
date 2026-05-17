#include "tetris.h"
#include <stdlib.h>
#include "GBT/gbt_entrada.h"
#include "dibujo.h"
#include "graficos.h"
#include "piezas.h"
#include "tablero.h"
#include "mEstados.h"
#include "opciones.h"
#include <stdio.h>

int framesTecla = 0;
int framesAbajo = 0;
eGBT_Tecla ultimaTecla;

Tetris* tetris = NULL;

Tetris* inicializar_tetris(bool modo_dx){

    tetris = malloc(sizeof(Tetris));
    if(!tetris){
        return NULL;
    }

    inicialiar_tablero(&tetris->tablero);

    if(!tetris->tablero.matriz)
    {
        free(tetris);
        return NULL;
    }

    ///Verificar la condicion de null y como eso afecta al tablero
    VectorCrear(&tetris->bolsa);


    //aca porque si
    cargar_combinaciones_minos();

    tetris->modo_dx = modo_dx;
    rellenar_mezclar_bolsa();
    tetris->tipo_pieza = *(tetris->bolsa.vec + tetris->indice_bolsa);
    tetris->indice_bolsa++;
    int variante = rand() % 4;
    int textura = (variante * 7) + (tetris->tipo_pieza % 7);
    cargar_pieza(&tetris->pieza, tetris->tipo_pieza, textura+1);
    tetris->puntos = 0;
    tetris->contador_frames = 0;
    tetris->velocidad_ms = obtener_velocidad_actual_ms();
    tetris->cant_piezas = 0;
    tetris->umbral_frames = 30 * (tetris->velocidad_ms / 1000);
    tetris->cont_fijacion = 0;
    tetris->contacto = false;
    tetris->en_pausa = false;

    return tetris;
}

void loop_dibujar_tetris()
{
    limpiar(7);
    dibujar_fondo();
    dibujar_rect(pantalla->tab_offsetX, pantalla->tab_offsetY, pantalla->tam_tabX-1, pantalla->tam_tabY-1, 1);
    dibujar_tablero(&tetris->tablero, (320 - (TABLERO_COLS * TAMANIO_BLOQUE)) / 2, 4);
    dibujar_pieza(&tetris->pieza, (320 - (TABLERO_COLS * TAMANIO_BLOQUE)) / 2, 4, tetris->modo_dx);

    //Dibujar puntos
    int origen_cuadroX = pantalla->tab_offsetX + pantalla->tam_tabX + 10;
    dibujar_rect( origen_cuadroX, pantalla->tab_offsetY, 60, 25, 1);
    dibujar_texto("puntos", 69, 11, 1, 0);
    char points[12];
    sprintf(points, "%d", tetris->puntos);
    dibujar_texto(points, 69, 15, 1, 0);

    if(tetris->en_pausa)
    {
        dibujar_filtro_pausa(8);
        //Esto lo podemos volar o hacer mas lindo

        //Lo que intente hacer es darle un recuadro al texto "en pausa"
        //Intento calcular el centro de pantalla y determino un ancho y un alto para esa caja
        //Una de las funciones dibujar_rect me sirve para darle un borde
        //Se podria hacer mejor, o directamente pasarle los datos harcodeados
        //Y nos ahorramos en cuentas
        int centro_x = pantalla->tab_offsetX + (pantalla->tam_tabX / 2);
        int centro_y = pantalla->tab_offsetY + (pantalla->tam_tabY / 2);

        int ancho_caja = 300;
        int alto_caja = 150;

        int caja_x = centro_x - (ancho_caja / 2);
        int caja_y = centro_y - (alto_caja / 2);
        dibujar_rect(caja_x , caja_y , ancho_caja +2, alto_caja + 2, 4);
        dibujar_rect(caja_x+1, caja_y +1, ancho_caja, alto_caja, 0);

        //Un contador de frames que me va a servir para darle el efecto de aparecer y desaparecer al texto

        //No se porque tiene que ser static esta variable, pero si no es static no funca
        static int frames_contador = 0;
        frames_contador++;

        if((frames_contador / 30) % 2 == 0)
        {
            dibujar_texto("EN PAUSA",35,40,2*pantalla->escala_v,14);
        }

        if(frames_contador >= 60)
        {
            frames_contador = 0;
        }

        ///inclusive quizas no hace falta darle ese recuadro, lo podriamos sacar. Por el momento existe para que se note mejor el texto
    }
}

void loop_logica_tetris()
{
    eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

    if(tecla == GBTK_ESCAPE)
    {
        //printf("Volver a pantalla inicial\n");    Ahora vuelve al menu
        cambiar_contexto(PANTALLA_MENU);
        return;
    }
    if(tecla == GBTK_s)
    {
        if(guardar_partida("partida.bin"))
        {
            cambiar_contexto(PANTALLA_SPLASH);
            return;
        }
    }
    if(tecla == GBTK_p)
    {
        tetris->en_pausa = !tetris->en_pausa;
        printf("Tecla P apretada\n");
    }
    if(tetris->en_pausa)
    {
        printf("Estoy en pausa\n");
        return;
    }
    if(tecla == GBTK_s)
    {
        if(guardar_partida("partida.bin"))
        {
            cambiar_contexto(PANTALLA_SPLASH);
            return;
        }
    }
    if(tecla == GBTK_p)
    {
        tetris->en_pausa = !tetris->en_pausa;
        printf("Tecla P apretada\n");
    }
    if(tetris->en_pausa)
    {
        printf("Estoy en pausa\n");
        return;
    }
    if(tecla == GBTK_x)
    {
        rotar_pieza_activa(SENTIDO_HORARIO);
    }
    if(tecla == GBTK_z)
    {
        rotar_pieza_activa(SENTIDO_ANTIHORARIO);
    }

    mover_pieza(tecla);

    bool pieza_anclada = procesar_caida();

    if(pieza_anclada)
    {
        procesar_impacto();
    }

    if(perder())
    {
       cambiar_contexto(PANTALLA_MENU);
       return;
    }

}

void limpiar_tetris()
{
    if(!tetris)
        return;
    VectorDestruir(&tetris->bolsa);
    destruir_tablero(&tetris->tablero,TABLERO_FILAS);
    free(tetris);
    tetris = NULL;
}


void rotar_pieza_activa(uint8_t sentido)
{
    //Pieza aux que va estar rotada
    Pieza pieza_rotar = tetris->pieza;

    if(sentido == SENTIDO_HORARIO)
    {
        sentido_horario(pieza_rotar.matriz, tetris->pieza.matriz); //Esta funcion vive en pieza.h
    }
    else
    {
        sentido_antihorario(pieza_rotar.matriz, tetris->pieza.matriz); //Esta funcion vive en pieza.h
    }

    //si la pieza aux rotada no choca con nada entonces se la copiamos a nuestra pieza tetris
    if(!colision(&tetris->tablero,&pieza_rotar,pieza_rotar.x,pieza_rotar.y, tetris->modo_dx))
    {
        if(tetris->contacto) //Verificamos si hay o no contacto para saber si tenemos que resetear el cont_fijacion
        {
            tetris->cont_fijacion = 0;
        }
        for(int y = 0; y < ORDEN_PIEZA; y++)
        {
            for(int x = 0; x < ORDEN_PIEZA; x++)
            {
                tetris->pieza.matriz[y][x] = pieza_rotar.matriz[y][x];
            }
        }
    }

}

void mover_pieza(eGBT_Tecla tecla)
{
    int x = 0;
    int y = 0;

    if(gbt_tecla_sostenida(GBTK_DERECHA))
    {
        if(ultimaTecla != GBTK_DERECHA){
            ultimaTecla = GBTK_DERECHA;
            framesTecla = 0;
        }
        if(framesTecla == 0)
            x=1;
        framesTecla++;
        if(framesTecla>9)
            framesTecla=0;
    }else if(gbt_tecla_sostenida(GBTK_IZQUIERDA))
    {
        if(ultimaTecla != GBTK_IZQUIERDA){
            ultimaTecla = GBTK_IZQUIERDA;
            framesTecla = 0;
        }
        if(framesTecla == 0)
            x=-1;
        framesTecla++;
        if(framesTecla>9)
            framesTecla=0;
    }else
        framesTecla = 0;

    if(gbt_tecla_sostenida(GBTK_ABAJO))
    {
        if(framesAbajo==0)
            y=1;
        framesAbajo++;
        if(framesAbajo>9)
            framesAbajo=0;
    }

    if(x != 0 || y != 0)
    {
        //En caso que no haya colision, le actualizamos las posiciones a nuestra pieza
        if(!colision(&tetris->tablero, &tetris->pieza, tetris->pieza.x +x, tetris->pieza.y + y,tetris->modo_dx))
        {
            tetris->pieza.x += x;
            tetris->pieza.y += y;
             //Este if verifica si bajamos la pieza manualmente o cae por si sola
            if(y == 1)
            {
                tetris->puntos += 1;
            }

            if(tetris->contacto)
            {
                tetris->cont_fijacion = 0;
            }
        }
    }
}
// Fucion que quizas se puede limpiar un poquito mas
bool procesar_caida()
{
    //Bandera para saber si la pieza se anclo al tablero o si sigue cayendo
    bool pieza_anclada = false;

    //Si no hay colicion, entonces estamos en el caso de que la pieza esta haciendo caida libre
    if(!colision(&tetris->tablero, &tetris->pieza, tetris->pieza.x , tetris->pieza.y +1,tetris->modo_dx))
    {
        tetris->contacto = false;
        tetris->contador_frames++;

        //Actualizamos sus frames
        if(tetris->contador_frames >= (uint32_t)tetris->umbral_frames)
        {
            tetris->pieza.y++;
            tetris->contador_frames = 0;
        }
    }
    //Caso que la pieza choco con el fondo del tablero o una pieza ya colocada
    else
    {
        tetris->contacto = true;
        tetris->cont_fijacion ++;

        if(tetris->cont_fijacion >= (uint32_t)tetris->umbral_frames * 0.5)
        {
            anclar_pieza(&tetris->tablero, &tetris->pieza, tetris->modo_dx);
            pieza_anclada = true;
        }
    }
    return pieza_anclada;
}

void calculo_puntos(int lineas_borradas)
{
    uint32_t puntos = 0;
    float multiplicador;

    if(lineas_borradas > 0)
    {
        switch(lineas_borradas)
        {
            case 1: puntos = 100; break;
            case 2: puntos = 300; break;
            case 3: puntos = 500; break;
            default: puntos =800; break;
        }
        multiplicador = 1000/tetris->velocidad_ms;
        tetris->puntos += (uint32_t)(puntos * multiplicador);
    }
}

void obtener_nueva_pieza()
{
    if(tetris->indice_bolsa >= tetris->bolsa.ce)
    {
        VectorVaciar(&tetris->bolsa);
        rellenar_mezclar_bolsa();
    }

    tetris->tipo_pieza = *(tetris->bolsa.vec + tetris->indice_bolsa);
    tetris->indice_bolsa++;

    int variante = rand() % 4;
    int textura = (variante * 7) + (tetris->tipo_pieza % 7);

    cargar_pieza(&tetris->pieza, tetris->tipo_pieza, textura + 1);
    //a
}

void actualizar_datos_tetris()
{
    tetris->cant_piezas++;

    if(tetris->cant_piezas % 10 == 0)
    {
        tetris->velocidad_ms *= 0.97;
        tetris->umbral_frames *= 0.97;
    }

    tetris->contador_frames = 0;
    tetris->cont_fijacion = 0;
    tetris->contacto = false;

}

bool perder()
{
    if(colision(&tetris->tablero,&tetris->pieza,tetris->pieza.x,tetris->pieza.y,tetris->modo_dx))
    {
        printf("Perdiste\n");
        return true;
    }
    return false;
}

void procesar_impacto()
{
    int lineas_borradas = limpiar_filas(&tetris->tablero);

    calculo_puntos(lineas_borradas);

    actualizar_datos_tetris();

    obtener_nueva_pieza();

    printf("\n==== INFO ====\n");
    printf("Lineas borradas: %d\n",lineas_borradas);
    printf("Puntaje Total: %d\n", tetris->puntos);
    printf("Piezas Caidas: %d\n", tetris->cant_piezas);
    printf("Velocidad: %.1f ms\n", tetris->velocidad_ms);
    printf("Tolerancia: %.1f ms\n", tetris->velocidad_ms * 0.5f);
    printf("=====================\n");
}

//Pasar esta funcion a dibujar.h y .c
void dibujar_filtro_pausa(uint8_t col)
{
    for(int x = 0; x < pantalla->ancho; x++)
    {
        for(int y = 0; y < pantalla->alto; y++)
        {
            if((x + y) % 2 == 0)
            {
                gbt_dibujar_pixel(x,y,col);
            }
        }
    }

}

bool guardar_partida(const char* nombre_archivo)
{
    if(!tetris)
    {
        printf("Error: no tetris para guardar\n");
        return false;
    }
    FILE* pf = fopen(nombre_archivo,"wb");

    if(!pf)
    {
        printf("Error al crear el archivo\n");
        return false;
    }

    PartidaGuardada save;

    for(int y = 0; y < TABLERO_FILAS; y++)
    {
        for(int x = 0; x < TABLERO_COLS; x++)
        {
            save.matriz_tablero[y][x] = tetris->tablero.matriz[y][x];
        }
    }

    save.Pieza = tetris->pieza;
    save.cant_piezas = tetris->cant_piezas;
    save.tipo_pieza = tetris->tipo_pieza;
    save.puntos = tetris->puntos;
    save.velocidad_ms = tetris->velocidad_ms;
    save.modo_dx = tetris->modo_dx;

    fwrite(&save,sizeof(PartidaGuardada),1,pf);
    fclose(pf);

    printf("Partida guardada\n");
    return true;

}

bool cargar_partida(const char* nombre_archivo)
{
    FILE* pf = fopen(nombre_archivo,"rb");

    if(!pf)
    {
        printf("No existe el archivo\n");
        return false;
    }

    PartidaGuardada save;
    fread(&save,sizeof(PartidaGuardada),1,pf);
    fclose(pf);

    for(int y = 0; y < TABLERO_FILAS; y++)
    {
        for(int x = 0; x < TABLERO_COLS; x++)
        {
            tetris->tablero.matriz[y][x] = save.matriz_tablero[y][x];
        }
    }

    tetris->pieza = save.Pieza;
    tetris->tipo_pieza = save.tipo_pieza;
    tetris->puntos = save.puntos;
    tetris->cant_piezas = save.cant_piezas;
    tetris->velocidad_ms = save.velocidad_ms;
    tetris->modo_dx = save.modo_dx;
    tetris->en_pausa = true;
    tetris->contador_frames = 0;
    tetris->cont_fijacion = 0;
    tetris->contacto = false;

    tetris->umbral_frames = 30 * (tetris->velocidad_ms / 1000);

    printf("Partida restaurada\n");
    return true;
}


void rellenar_mezclar_bolsa()
{
    int cant_piezas = tetris->modo_dx ? 11 : 7;

    for(int i = 0; i < cant_piezas; i++)
    {
        VectorCargarAlFinal(&tetris->bolsa,i);
    }

    VectorMezclarDatos(&tetris->bolsa);

    tetris->indice_bolsa = 0;
}
