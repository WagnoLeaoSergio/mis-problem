#include "No.h"
#include <set>
#include <vector>

using namespace std;

class Grafo
{
    private:
        int numNos;
        int numArestas;
        No* primeiro;
        int grau;
        bool direcionado;
        bool pondNo;
        bool pondAresta;

        int contaNos();
        No* buscaNo(int id);
        bool temAresta(int id1, int id2);
        int getRandomIntNumber(int nMin, int nMax);
        double getRandomFloatNumber(double nMin, double nMax);
        int auxOrdenaMenorGrau(set < int > &visitados);
        vector <int> ordenaGrau();

        vector <int> auxCaminhamentoLargura(No* p, set <int> &visitados);
        vector <int> auxCaminhamentoProf(No* p, set <int> &visitados);

        bool ehConexo(set <int> visitados);
        int ehFortementeConexo(No* p, set <int> &ida);
        int auxCFC(No* p, No* t, Aresta* a, vector < vector <int> > &comp, int i);
        void auxOT(No* primeiro, std::vector <int> &vect, No** visitados, int n);

        void auxGuloso_atualizaCandidatos(vector <int> &candidatos, int remocao);
        vector <int> guloso();
        vector <int> gulosoRandomizado(float alfa, int itera);

        int selecionaAlfa(vector <double> p);
        void atualizaProb(vector <float> &alfas, vector <int> &cont, vector <int> &numNosSol, vector <int> &sol, vector <double> &p, int delta);
        void atualizaDados(vector <int> &sol, int indexAlfa, vector <int> &cont, vector <int> &numNosSol);
        vector <int> gulosoRandomizadoReativo(int maxItera, int bloco);

    public:
        //Grafo();
        Grafo(bool ponderado, bool dir);
        ~Grafo();
        bool busca(int id);
        //Apenas declaracao do metodo
        void inserir(int id1);
        void conectar(int id1, int id2, float peso);
        void desconectar(int id1, int id2);
        void excluirNo(int id); ///EM ANDAMENTO
        int getNumArestas();
        int getNumNos();
        void printGrafo();

        vector <int> caminhamentoLargura();
        vector <int> caminhamentoProf();

        vector < vector <int> > componentesConexas();
        void componentesFortementeConexas();
        void ordenacoesTopologicas();

        int* dijkstra(int id);
        void floyd();
        int prim();
        Grafo* kruskal();

        vector <int> subconjuntoIndependenteMaxG();
        vector <int> subconjuntoIndependenteMaxGR();
        vector <int> subconjuntoIndependenteMaxGRR();
};
