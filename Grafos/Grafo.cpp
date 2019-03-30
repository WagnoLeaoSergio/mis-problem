#include "Grafo.h"

Grafo::Grafo()
{
    ListaNo = new No();
    nAresta = 0;
    grau = 0;
    direcionado = false;
    pondNo = false;
    pondAresta = false;
}

Grafo::Grafo(bool dir)
{
    ListaNo = new No();
    nAresta = 0;
    grau = 0;
    direcionado = dir;
    pondNo = false;
    pondAresta = false;
}
