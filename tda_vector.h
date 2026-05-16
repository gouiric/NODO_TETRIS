#ifndef TDA_VECTOR_H_INCLUDED
#define TDA_VECTOR_H_INCLUDED

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#define CAP_INI 7
#define FACT_INCREMENTO 1.5

#define TODO_OK 0
#define SIN_MEMORIA 1




typedef struct
{
    int *vec;
    size_t ce;
    size_t cap;
}Vector;


bool VectorCrear(Vector* v);

int VectorCargarAlFinal(Vector* v, int elemt);

void VectorMezclarDatos(Vector* v);

void VectorVaciar(Vector* v);

void VectorDestruir(Vector* v);

#endif // TDA_VECTOR_H_INCLUDED
