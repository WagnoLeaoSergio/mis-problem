#include "ListaGrafosVizinho.h"

class ListaGrafos
{
    private:
     int n;
     int tam_max;
     ListaGrafosVizinho *vet[];

    public:
     ListaGrafos(int tam);
     ~ListaGrafos();
     void criarVertice(int valor, int num_vertice);
     void conectar(int x1, int x2, int distancia);
};
