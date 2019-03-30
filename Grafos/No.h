#include "Aresta.h"
#include <cstddef>
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
    void setId(int id)
    {
        this->id = id;
    }
    int getId()
    {
        return id;
    }

    void setP(int p)
    {
        this->p = p;
    }
    float getP()
    {
        return p;
    }

    void setAdj(Aresta* a)
    {
        this->adj = a;
    }
    Aresta* getAdj()
    {
        return adj;
    }

    void setProx(No* prox)
    {
        this->prox = prox;
    }
    No* getProx()
    {
        return prox;
    }

    void setAnt(No* ant)
    {
        this->ant = ant;
    }
    No* getAnt()
    {
        return ant;
    }

    void setEntrada(int grauEntrada)
    {
        this->grauEntrada = grauEntrada;
    }
    int getEntrada()
    {
        return grauEntrada;
    }

    void setSaida(int grauSaida)
    {
        this->grauSaida = grauSaida;
    }
    int getSaida()
    {
        return grauSaida;
    }

};
