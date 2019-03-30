#include "No.h"
class Grafo
{
    private:
     No* ListaNo;
     int nAresta;
     int grau;
     bool direcionado;
     bool pondNo;
     bool pondAresta;

    public:
     Grafo();
     Grafo(bool dir);
     ~Grafo();
     void conectar(int id1, int id2, char** argv);
};
