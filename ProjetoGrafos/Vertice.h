
class Vertice
{
    private:
     int dis;
     int num;
     Vertice* ant;
     Vertice* prox;

    public:
     void setDis(int x);
     int getDis();

     void setNum(int x);
     int getNum();

     void setAnt(Vertice *p);
     Vertice* getAnt();

     void setProx(Vertice *p);
     Vertice* getProx();
};
