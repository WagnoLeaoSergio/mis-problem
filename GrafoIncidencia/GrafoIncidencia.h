
class GrafoIncidencia
{
private:
    int *mat;
    int nNos;

public:
    GrafoIncidencia(int n);
    ~GrafoIncidencia();
    void conectar(int n1, int n2);
    void plotar();
};
