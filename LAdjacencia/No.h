
#include "Aresta.h"
#include <cstddef>
class No
{

private:
    int id;
    int peso;
    Aresta* adj;
    No* prox;
    No* ant;
    int grauEntrada;
    int grauSaida;

public:
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
    void setPeso(int peso)
    {
        this->peso = peso;
    }

    //Funcao para retornar o peso do no caso tenha
    int getPeso()
    {
        return peso;
    }

    //Funcao set da aresta que liga esse no a outro
    void setAdj(Aresta* a)
    {
        this->adj = a;
    }

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
