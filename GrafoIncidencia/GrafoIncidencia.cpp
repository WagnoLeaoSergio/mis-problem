#include "GrafoIncidencia.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

GrafoIncidencia::GrafoIncidencia(int n)
{
    nNos = n;
    mat = new int[nNos*nNos];
    for(int i = 0; i < nNos*nNos; i++)
    {
        mat[i] = 0;
    }
    cout << "\nGrafo de Incidencia criado\n";
}

GrafoIncidencia::~GrafoIncidencia()
{
    delete mat;
    cout << "\nGrafo de Incidencia destruido\n";
}

void GrafoIncidencia::conectar(int n1, int n2)
{
    if((n1 <= 0 || n1 > nNos) || (n2 <= 0 || n2 > nNos))
        {
            cout << "\nERRO! VERTICES NAO EXISTEM NO GRAFO\n";
            return;
        }
    if(n1 == n2)
    {
        cout << "\nERRO! SELF LOOP PROIBIDO!;
        return;
    }
    
    int indice = (n1-1)*nNos + (n2-1);

    mat[indice] = 1;
}

void GrafoIncidencia::plotar()
{
    cout << "\n";
    for(int i = 0; i < nNos; i++)
    {
        for(int j = 0; j < nNos; j++)
        {
            cout << mat[( i*nNos + j)] << ' ';
        }
        cout << "\n";
    }
}
