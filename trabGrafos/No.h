#include "Aresta.h"
#include <cstddef>

using namespace std;

class No
{

private:
    int id;
    float p;
    Aresta* adj;
    No* prox;
    No* ant;
    int grauEntrada;
    int grauSaida;

public:
    No()
    {
        adj = NULL;
        prox = NULL;
        ant = NULL;
    }
    //Funcao set ID do no
    void setId(int id)
    {
        this->id = id;
    }

    //Funcao para retornar o ID do no
    int getId()
    {
        return id;
    }

    //Funcao set do peso do no caso o mesmo seja ponderado
    void setP(int p)
    {
        this->p = p;
    }

    //Funcao para retornar o peso do no caso tenha
    float getP()
    {
        return p;
    }

    //Funcao set da aresta que liga esse no a outro
    void alocarAdj(int id)
    {
        Aresta *a = new Aresta;
        a->setNoAdj(id);
        if(adj == NULL)
        {
            this->adj = a;
        }
        else
        {
            Aresta *t = new Aresta;
            t = adj;
            while(t != NULL)
            {
                if(t->getProx() == NULL)
                {
                    t->setProx(a);
                    a->setAnt(t);
                    a->setProx(NULL);
                    break;
                }
                t = t->getProx();
            }
        }
    }
    ///EM ANDAMENTO --------------------------------------------------
    /*
    void desalocarAdj(int id)
    {
        if(adj != NULL)
        {
            if(adj->getNoadj() == id)
            {
                Aresta *a = adj;
                adj = adj->getProx();
                adj->setAnt(NULL);
                delete a;
            }
            else
            {
                for(Aresta *a = adj; a != NULL; a = a->getProx())
                    if(a->getNoadj() == id)
                    {
                        if(a->getProx() == NULL)
                        {
                            a->getAnt()->setProx(NULL);
                            delete a;
                            break;
                        }
                        else
                        {
                            a->getAnt()->setProx(a->getProx());
                            a->getProx()->setAnt(a->getAnt());
                            delete a;
                            break;
                        }
                    }
            }
        }
    }
    */
    ///-----------------------------------------------------------------
    //Funcao para retornar a aresta do no
    Aresta* getAdj()
    {
        return adj;
    }

    //Funcao set do proximo no da lista grafo
    void setProx(No* prox)
    {
        this->prox = prox;
    }

    //Funcao para retornar o proximo no do grafo
    No* getProx()
    {
        return prox;
    }

    //Funcao set do no anterior desse na lista grafo
    void setAnt(No* ant)
    {
        //if(adj != NULL)
        this->ant = ant;
    }

    //Funcao para retornar o no anterior a esse na lista grafo
    No* getAnt()
    {
        return ant;
    }

    //Funcao set do grau de entrada do no
    void setEntrada(int grauEntrada)
    {
        this->grauEntrada = grauEntrada;
    }

    //Funcao para retornar o grau de entrada do no
    int getEntrada()
    {
        return grauEntrada;
    }

    //Funcao set para o grau de saida do no
    void setSaida(int grauSaida)
    {
        this->grauSaida = grauSaida;
    }

    //Funcao para retornar o grau de saida do no
    int getSaida()
    {
        return grauSaida;
    }
};
