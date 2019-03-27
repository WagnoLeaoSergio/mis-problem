#include "Vertice.h"

class ListaGrafosVizinho
{
    private:
     Vertice *primeiro;
     Vertice *ultimo;
     int n;

    public:
     ListaGrafosVizinho()
     {
        primeiro = NULL;
        ultimo = NULL;
        n = 0;
     }
     ~ListaGrafosVizinho()
     {
        Vertice *p = new Vertice();
        p = primeiro;
        while(p != NULL)
        {
            Vertice* q = p;
            delete q;
            p = p->getProx();
        }
     }
     void insereUltimo(int dis, int num)
     {
        Vertice *p = new Vertice();
        p->setDis(dis);
        p->setNum(num);

        if(n == 0){
            p->setAnt(NULL);
            p->setProx(NULL);
            p = primeiro = ultimo;
        }
        else if(n == 1){
            p->setAnt(primeiro);
            p->setProx(NULL);
            ultimo = p;
        }
        else{
            p->setAnt(ultimo);
            p->setProx(NULL);
            ultimo = p;
        }
        n++;
     }

};
