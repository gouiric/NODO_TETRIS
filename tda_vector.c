#include "tda_vector.h"

static bool AumentarCapacidad(Vector*);
static void Intercambiar(int*, int*);

bool VectorCrear(Vector* v)
{
    v->ce = 0;
    v->cap = 0;

    v->vec = malloc(CAP_INI * sizeof(int));

    if(!v->vec)
    {
        return false;
    }

    v->cap = CAP_INI;
    return true;

}

bool AumentarCapacidad(Vector* v)
{
    size_t n_cap = FACT_INCREMENTO * v->cap;

    int* v_aux = realloc(v->vec, n_cap * sizeof(int));

    if(!v_aux)
    {
        return false;
    }

    v->vec = v_aux;
    v->cap = n_cap;

    return true;
}

int VectorCargarAlFinal(Vector* v, int elemt)
{
    if(v->ce == v->cap)
    {
        if(!AumentarCapacidad(v))
        {
            return SIN_MEMORIA;
        }
    }
    int* ppos = v->vec + v->ce;
    *ppos = elemt;

    v->ce++;

    return TODO_OK;
}

void Intercambiar(int* a, int* b)
{
    int valor_inter = *a;
    *a = *b;
    *b = valor_inter;
}

void VectorMezclarDatos(Vector* v)
{
    int* pini = v->vec;
    int* pact = v->vec + v->ce - 1;
    int* pdesp;
    int desp;

    while(pini < pact)
    {
        desp = rand()%(pact - pini + 1);
        pdesp = pini + desp;

        Intercambiar(pdesp, pact);
        pact--;
    }
}
///Tengo mis dudas jajajaja
void VectorVaciar(Vector* v)
{
    v->ce = 0;
}

void VectorDestruir(Vector* v)
{
    free(v->vec);
    v->ce = 0;
    v->cap = 0;
    v->vec = NULL;
}
