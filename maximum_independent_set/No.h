#include "Aresta.h"
#include <cstddef>

using namespace std;

class No
{
    private:
        int id;
        float peso;
        Aresta* primeiroAdj;
        No* prox;
        No* ant;
        int grauEntrada;
        int grauSaida;

    public:
        No()
        {
            primeiroAdj = NULL;
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
        void setPeso(float peso)
        {
            this->peso = peso;
        }

        //Funcao para retornar o peso do no caso tenha
        float getPeso()
        {
            return peso;
        }

        //Funcao set da aresta que liga esse no a outro
        void alocarAresta(int id, float peso)
        {
            Aresta *a = new Aresta;
            a->setPeso(peso);
            a->setNoAdj(id);
            if(primeiroAdj == NULL)
            {
                this->primeiroAdj = a;
            }
            else
            {
                Aresta *t = new Aresta;
                t = primeiroAdj;
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

        void alocarAresta(int id)
        {
            Aresta *a = new Aresta;
            a->setPeso(0);
            a->setNoAdj(id);
            if(primeiroAdj == NULL)
            {
                this->primeiroAdj = a;
            }
            else
            {
                Aresta *t = new Aresta;
                t = primeiroAdj;
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
        
        //Funcao para retornar a aresta do no
        Aresta* getAdj()
        {
            return primeiroAdj;
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
            //if(primeiroAdj != NULL)
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
