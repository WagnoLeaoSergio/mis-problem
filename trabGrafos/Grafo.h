#include "No.h"
#include <set>
#include <vector>

using namespace std;

class Grafo
{
    private:
     int n;
     int e;
     No* ListaNo;
     int nAresta;
     int grau;
     bool direcionado;
     bool pondNo;
     bool pondAresta;
     vector <int> auxCaminhamentoLargura(No* p, set <int> &visitados);
     void auxCaminhamentoProf(No* p, set <int> &visitados);
     bool ehConexo(set <int> visitados);
     int ehFortementeConexo(No* p, set <int> &ida);
     void auxOT(No* primeiro, std::vector <int> &vect, No** visitados, int n);
     No* buscaNo(int id);
     vector <int> ordenaGrau();
     int auxOrdenaGrau(set < int > &visitados);
     vector <int> gulosoIndependente();
     vector <int> gulosoIndependenteRandomizado(float alfa, int itera);
     void auxGuloso_atualizaCandidatos(vector <int> &candidatos, int remocao);
     bool temAresta(int id1, int id2);
     int getRandomIntNumber(int nMin, int nMax);
     float getRandomFloatNumber(float nMin, float nMax);
     vector <int> gulosoIndependenteReativo(int maxItera, int bloco);
     void atualizaProb(vector <float> &alfas, vector <int> &cont, vector <int> &numNosSol, vector <int> &sol, vector <float> &p, int delta);
     int selecionaAlfa(vector <float> p);
     void atualizaDados(vector <int> &sol, int indexAlfa, vector <int> &cont, vector <int> &numNosSol);
     int auxCFC(No* p, No* t, Aresta* a, vector < vector <int> > &comp, int i);

    public:
     //Grafo();
     Grafo(bool dir);
     ~Grafo();
     bool busca(int id);
     //Apenas declaracao do metodo
     void conectar(int id1, int id2);
     void desconectar(int id1, int id2);
     void caminhamentoLargura();
     void printGrafo();
     void caminhamentoProf();
     void excluirNo(int id); ///EM ANDAMENTO
     int contaNos();
     int componentesConexas();
     void inserir(int id1);
     void componentesFortementeConexas();
     void ordenacoesTopologicas();
     vector <int> subconjuntoIndependenteMax();
};
