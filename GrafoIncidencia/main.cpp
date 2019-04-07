#include <iostream>
#include "GrafoIncidencia.h"

using namespace std;

int main()
{
    GrafoIncidencia g(3);
    g.plotar();
    g.conectar(2,2);
    g.plotar();
    return 0;
}
