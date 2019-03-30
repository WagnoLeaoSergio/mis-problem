
class Aresta
{

private:
    int noAdj;
    float peso;
    Aresta* prox;
    Aresta* ant;

public:
    void setNoAdj(int noAdj)
    {
        this->noAdj = noAdj;
    }
    int getNoadj()
    {
        return noAdj;
    }

    void setPeso(int peso)
    {
        this->peso = peso;
    }
    int getPeso()
    {
        return peso;
    }

    void setProx(Aresta* prox)
    {
        this->prox = prox;
    }
    Aresta* getProx()
    {
        return prox;
    }

    void setAnt(Aresta* ant)
    {
        this->ant = ant;
    }
    Aresta* getAnt()
    {
        return ant;
    }
};

