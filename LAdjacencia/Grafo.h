#include <vector>
#include <stack>
#include <utility>
#include "No.h"


class Grafo
{
    private:
     No* ListaNo;
     int nAresta;
     int grau;
     bool direcionado;
     bool pondNo;
     bool pondAresta;
     int numeroDeNos;
     int numeroDeArestas;

     No* buscaNo(int id);

     void excluirAresta(Aresta* a);

     void auxCaminharEmLargura(No* primeiro, int n);

     //Geralmente, o algoritmo de caminhamento em profundidade
     // eh implementado fora do TAD do grafo.

     //Como este esta dentro, nao eh necessario
     // especificar qual o grafo deve-se fazer a busca
     // nos parametros da funcao.
     void caminharEmProfundidadeAuxiliar(No*p, int* visitados, int* nos);

     void conectarNaoDirecionado(int id1, int id2, int peso);
     void conectarDirecionado(int id1, int id2, int peso);

     bool conectado(int id1, int id2);
     void auxOT(No* primeiro, std::vector<int> &vect, No** visitados, int n);

     void inserirNoNaoPonderado(int id);
     void inserirNoPonderado(int id, int p);

     No** ordenaPorGrau();

     void DFSAux(No* p, std::vector<int>* visitados, int* nos, std::stack< No* >* pilha);
     std::vector<int>* DFS(No* q, std::stack< No* >* pilha);

     void caminhoMinimoAuxiliar();

    public:

     Grafo(bool dir);
     Grafo(bool dir, bool ponderadoNo, bool ponderadoAresta);

     ~Grafo();

     int getNumeroDeNos();
     int getNumeroDeArestas();

     No* getPrimeiro();


     //So funciona para o digrafo
     Grafo* copiarGrafo();

     int contaNos();
     void plotarGrafo();

     void inserirNo(int id, int p);

     void excluirNo(int id);
     void excluirNoDirecionado(int id);

     void conectar(int id1, int id2, int p);

     void listarAdjacentes(int id);

     void caminharEmLargura();
     Grafo* grafoReverso();

     void caminharEmProfundidade();
     void ordenacoesTopologicas();

     void componentesFortementeConexas();

     int* dijkstra(int id);
     void floyd();
     int prim();
     Grafo* kruskal();


};
