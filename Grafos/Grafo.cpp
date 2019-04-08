#include "Grafo.h"
#include <stdio.h>
#include <iostream>

using namespace std;

Grafo::Grafo()
{
    cout << "\nA graph has been created\n";

    ListaNo = NULL;
    nAresta = 0;
    grau = 0;
    direcionado = false;
    pondNo = false;
    pondAresta = false;

}

Grafo::Grafo(bool dir)
{
    ListaNo = NULL;
    nAresta = 0;
    grau = 0;
    direcionado = dir;
    pondNo = false;
    pondAresta = false;
}


void Grafo::teste(){
    printf("\nOPA");
}

Grafo::~Grafo()
{
    delete ListaNo;
    printf("\nThe graph was destructed\n");
}
