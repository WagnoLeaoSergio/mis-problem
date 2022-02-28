#include "Grafo.h"
#include <stdio.h>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <stdlib.h>
#include <list>
#include <stdlib.h>
#include <algorithm>
#include <time.h>
#include <chrono>
#include <random>
#include <windows.h>

using namespace std;

Grafo::Grafo(bool ponderado, bool dir)
{
    cout << "A graph has been created.\n" << endl;
    primeiro = NULL;
    grau = 0;
    numNos = 0;
    numArestas = 0;
    direcionado = dir;
    pondNo = false;
    pondAresta = ponderado;
}

Grafo::~Grafo()
{
    for(No* t = primeiro; t != NULL;)
    {
        for(Aresta* p = t->getAdj(); p != NULL;)
        {
            Aresta* aux1 = p->getProx();
            delete p;
            p = aux1;
        }

        No* aux2 = t->getProx();
        delete t;
        t = aux2;
    }
    cout << "\nA graph has been destroyed.\n";
}

int Grafo::getNumArestas()
{
    return this->numArestas;
}

int Grafo::getNumNos()
{
    return this->numNos;
}

bool Grafo::busca(int id)
{
    for(No* p = primeiro; p != NULL; p = p->getProx())
    {
        if(p->getId() == id)
            return true;
    }
    return false;
}

void Grafo::inserir(int id)
{
    if(!(busca(id)))
    {
        No *p = new No;
        p->setId(id);
        p->setEntrada(0);
        p->setSaida(0);
        if(primeiro != NULL)
        {
            for(No *i = primeiro; i != NULL; i = i->getProx())
                if(i->getProx() == NULL)
                {
                    //cout << i->getId() << "asd" << endl;
                    i->setProx(p);
                    p->setProx(NULL);
                    p->setAnt(i);
                    break;
                }
        }
        else
        {
            primeiro = p;
            primeiro->setProx(NULL);
            primeiro->setAnt(NULL);
        }
        numNos++;
    }
    else
        return;
}

void Grafo::conectar(int id1, int id2, float peso)
{
    if(direcionado)
    {
        if(!busca(id1) || !busca(id2) || id1 == id2 || temAresta(id1, id2))
        {
            cout << "Erro: conexao invalida (" << id1 <<", " << id2 << ")." << endl;
            exit(1);
            //return;
        }
        else
        {
            for(No *n = primeiro; n != NULL; n = n->getProx())
            {
                if(n->getId() == id1)
                {
                    n->alocarAresta(id2, peso);
                    n->setSaida(n->getSaida() + 1);
                }
                if(n->getId() == id2)
                {
                    n->setEntrada(n->getEntrada() + 1);
                }
            }
            numArestas++;
        }
    }
    else
    {
        if(!busca(id1) || !busca(id2) || id1 == id2 || temAresta(id1, id2))
        {
            cout << "Erro: conexao invalida (" << id1 <<", " << id2 << ")." << endl;
            exit(2);
            //return;
        }
        else
        {
            for(No *n = primeiro; n != NULL; n = n->getProx())
            {
                if(n->getId() == id1)
                {
                    n->alocarAresta(id2, peso);
                    n->setEntrada(n->getEntrada() + 1);
                }
                if(n->getId() == id2)
                {
                    n->alocarAresta(id1, peso);
                    n->setEntrada(n->getEntrada() + 1);
                }
            }
            numArestas++;
        }
    }
}

///EM ANDAMENTO---------------------------------------------------
void Grafo::desconectar(int id1, int id2)
{
    if(!(busca(id1)))
        exit(1);
        //return;
    if(!(busca(id2)))
        exit(2);
        //return;
    for(No *n = primeiro; n != NULL; n = n->getProx())
    {
        if(n->getId() == id1)
        {
            //for(Aresta* a = n->getAdj())
        }
        if(n->getId() == id2)
            n->alocarAresta(id1);
    }
}
///----------------------------------------------------------------
vector <int> Grafo::caminhamentoLargura()
{
    set < int > visitados;
    No* p = primeiro;
    vector <int> caminho;
    caminho = auxCaminhamentoLargura(p, visitados);
    return caminho;
}

vector <int> Grafo::auxCaminhamentoLargura(No* p, set < int > &visitados)
{
    queue < int > fila;
    int vertice = p->getId();
    fila.push(vertice);
    visitados.insert(p->getId());

    vector <int> componente;
    componente.push_back(vertice);
    cout << vertice << endl;

    while(!fila.empty())
    //while(fila.size() > 0)
    {
        //cout << "teste" << endl;
        vertice = fila.front();
        fila.pop();
        //cout << "tam " << fila.size() << endl;
        No* i;
        for(i = primeiro; i != NULL; i = i->getProx())
        {
            if(i->getId() == vertice)
                break;
        }
        for(Aresta *a = i->getAdj(); a != NULL; a = a->getProx())
        {
            if(visitados.find(a->getNoadj()) == visitados.end())
            {
                fila.push(a->getNoadj());
                visitados.insert(a->getNoadj());
                componente.push_back(a->getNoadj());
                cout << a->getNoadj() << endl;
            }
        }
        //cout << "asdasdas" << fila.size() << endl;
    }
    return componente;
}

vector <int> Grafo::caminhamentoProf()
{
    set < int > visitados;
    No* p = primeiro;
    vector <int> caminho;
    caminho = auxCaminhamentoProf(p, visitados);
    return caminho;
}

vector <int> Grafo::auxCaminhamentoProf(No* p, set <int> &visitados)
{
    stack < int > pilha;
    int vertice = p->getId();
    pilha.push(vertice);
    visitados.insert(p->getId());

    vector <int> componente;
    componente.push_back(vertice);
    cout << vertice << endl;
    //cout << vertice << endl;

    while(!pilha.empty())
    {
        vertice = pilha.top();
        cout << vertice << endl;
        pilha.pop();
        No* i;
        for(i = p; i != NULL; i = i->getProx())
        {
            if(i->getId() == vertice)
                break;
        }
        for(Aresta *a = i->getAdj(); a != NULL; a = a->getProx())
        {
            if(visitados.find(a->getNoadj()) == visitados.end())
            {
                pilha.push(a->getNoadj());
                visitados.insert(a->getNoadj());
                componente.push_back(a->getNoadj());
                cout << a->getNoadj() << endl;
            }
        }
    }
    return componente;
}

void Grafo::printGrafo()
{
    for(No* p = primeiro; p != NULL; p = p->getProx())
    {
        cout << p->getId() << " -> ";
        if(p->getAdj() != NULL)
            for(Aresta* a = p->getAdj(); a != NULL; a = a->getProx())
                cout << a->getNoadj() << " ";
        cout << endl;
    }
}

int Grafo::contaNos()
{
    int cont = 0;
    for(No* p = primeiro; p != NULL; p = p->getProx())
    {
        cont++;
    }
    //cout << "numero de nos: " << cont << endl;
    return cont;
}

bool Grafo::ehConexo(set < int > visitados)
{
    if((int) visitados.size() == contaNos())
        return true;
    else
        return false;
}

vector < vector <int> > Grafo::componentesConexas()
{
    vector <int> c;
    int cont = 0;
    set <int> visitados;
    No* p = primeiro;
    vector < vector <int> > componentes;
    if(ehConexo(visitados))
    {
        cout << "Componente " << cont << " " << endl;
        c = auxCaminhamentoLargura(p, visitados);
        componentes.push_back(c);
        cont++;
    }
    else
    {
        //cont++;
        for(No* p = primeiro; p != NULL; p = p->getProx())
        {
            if(visitados.find(p->getId()) == visitados.end())
            {
                cont++;
                cout << "Componente " << cont - 1 << " " << endl;
                componentes.push_back(auxCaminhamentoLargura(p, visitados));
                if(ehConexo(visitados))
                {
                    break;
                }
            }
        }
        cout << "deadjdleahdlakda " << componentes[0][0];
        /* HOW TO USE ITERATOR
        set < No* > componente;
        componente.insert(primeiro);
        set < No* > ::iterator it;
        it = componente.begin();
        cout << "teste iterator de p, id: " << (*it)->getId();
        */
    }
    return componentes;
}
/*
int Grafo::ehFortementeConexo(No* p, set < int > &visitados)
{
}

int Grafo::componentesFortementeConexas()
{
}
*/
void Grafo::componentesFortementeConexas()
{
    No* p = primeiro;
    No* t = p;
    vector < vector <int> > comp;
    auxCFC(p, t, p->getAdj(), comp, 0);
}

int Grafo::auxCFC(No* p, No* t, Aresta* a, vector < vector <int> > &comp, int i)
{
    if(p != NULL && t != NULL && a != NULL)
    {
        if(!temAresta(p->getId(), t->getId()))
        {
            a = a->getProx();
            t = buscaNo(a->getNoadj());
            //No* t = buscaNo(t->getAdj()->getNoadj());
            if(auxCFC(p, t, a, comp, i))
            {
                comp[i].push_back(t->getId());
            }
            /*
            if(temAresta(p->getId(), t->getId()))
            {
                comp[i].push_back(t->getId());
                i++;
                return 1;
            }
            else
            {

            }*/
        }
        else
        {
            comp[i].push_back(t->getId());
            return 1;
        }
    }
    i++;
    p = p->getProx();
    t = buscaNo(p->getAdj()->getNoadj());

    while(std::find(comp[i].begin(), comp[i].end(), p->getId()) != (comp[i].begin() + comp[i].size()) && std::find(comp[i].begin(), comp[i].end(), t->getId()) != (comp[i].begin() + comp[i].size()))
    {
        p = p->getProx();
        t = buscaNo(p->getAdj()->getNoadj());
    }
    a = p->getAdj();
    auxCFC(p, t, a, comp, i);
    return 0;
}

No* Grafo::buscaNo(int id)
{
    for(No* p = primeiro; p != NULL; p = p->getProx())
    {
        if(p->getId() == id)
            return p;
    }
    return NULL;
}

void Grafo::auxOT(No* primeiro, std::vector< int > &vect, No** visitados, int n)
{
   No* p = primeiro;
   int j = 0;

    for(int i = 0; i < n; i++)
    {
        visitados[i] = NULL;
    }

    queue<No*> fila;
    fila.push(p);
    visitados[0] = p;

    j++;

        while(!(fila.empty()))
        {
            No* q = fila.front();
            fila.pop();

            vect.push_back(q->getId());

            Aresta* a = q->getAdj();


            for(; a != NULL; a = a->getProx())
            {

                bool jaFoi = false;
                No* aux = this->buscaNo(a->getNoadj());

                for(int i = 0; i < n; i++)
                {
                    if(visitados[i] == aux)
                    {
                        jaFoi = true;
                    }
                }

                if(!jaFoi)
                {
                    fila.push(aux);
                    visitados[j] = aux;
                    j++;
                }
                if(j == n)
                    break;
            }

        }
}

void Grafo::ordenacoesTopologicas()
{
    if(numArestas > numNos - 1 || !direcionado)
    {
        cout << "\nGrafo possui pelo menos um ciclo, Ordenacao Topologica impossivel" << endl;
        //exit(0);
        return;
    }

    No* p = primeiro;
    vector<No*> nos;
    vector<int> ot;
    queue<No*>fontes;

    No** visitados = new No*[numNos]();

    for(; p != NULL; p = p->getProx())
    {
        nos.push_back(p);
        if(p->getEntrada() == 0)
            fontes.push(p);
    }


    while(!fontes.empty())
    {
        No* r = fontes.front();
        auxOT(r, ot, visitados, numNos);
        fontes.pop();
    }

    cout << "\nOrdenacao topologica: ";
    for (int i = 0; i < (int)ot.size(); i++)
    {
        cout << ot[i] << ", ";
    }
}

int* Grafo::dijkstra(int id){

    No* p = this->buscaNo(id);

    if(p == NULL){
        cout << endl << "ERRO! NO NAO ENCONTRADO" << endl;
        return 0;
    }

    if(!this->pondAresta){
        cout << endl << "ERRO! ESSE GRAFO NAO E PONDERADO NAS ARESTAS";
        return 0;
    }

    vector<No*> nosPorIndice;
    int custoPadrao = std::numeric_limits<int>::max();

    vector<int> visitados;
    vector<int> distancias;

    priority_queue < pair<int,int> , vector< pair<int,int> >, greater< pair<int,int> > > filaP;
    No* q = primeiro;

    for(int i = 0 ; i < numNos && q != NULL; i++, q = q->getProx())
    {
        visitados.push_back(0);
        distancias.push_back(custoPadrao);
        nosPorIndice.push_back(q);
    }

    vector<No*>::iterator iter;
    iter = find(nosPorIndice.begin(), nosPorIndice.end(), p);
    int p_index = distance(nosPorIndice.begin(), iter);


    No* aux = nosPorIndice[0];
    nosPorIndice[0] = nosPorIndice[p_index];
    nosPorIndice[p_index] = aux;

    distancias[0] = 0;


    filaP.push(make_pair(visitados[0], distancias[0]));

    while(!filaP.empty())
    {
        pair<int, int> par = filaP.top();
        int vertice = par.second;
        filaP.pop();

        if(visitados[vertice] == false)
        {
            visitados[vertice] = true;

            No* u = nosPorIndice[vertice];
            Aresta* e = u->getAdj();

            vector<No*>::iterator it = nosPorIndice.begin();

            for(; e != NULL; e = e->getProx())
            {
                No* v = this->buscaNo(e->getNoadj());
                int v_custo = e->getPeso();

                it = find(nosPorIndice.begin(), nosPorIndice.end(), v);

                int v_index = distance(nosPorIndice.begin(), it);


                if(distancias[v_index] > (distancias[vertice] + v_custo))
                {
                    distancias[v_index] = (distancias[vertice] + v_custo);
                    filaP.push(make_pair(distancias[v_index], v_index));
                }

            }

        }
    }
    return distancias.data();
}


void Grafo::floyd()
{
    int n = this->numNos;
    int matriz[n][n];
    vector<No*> nosIndice;
    No* p = primeiro;
    int cINFINITO = 100000;

    for(int i = 0; i < n && p != NULL; i++, p = p->getProx()){
        nosIndice.push_back(p);
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j)
                matriz[i][j] = 0;
            else
            {
                if(this->temAresta(nosIndice[i]->getId(), nosIndice[j]->getId()))
                {
                    for(Aresta* k = nosIndice[i]->getAdj(); k != NULL; k = k->getProx()){
                        if(k->getNoadj() == nosIndice[j]->getId())
                            matriz[i][j] = k->getPeso();
                    }
                }
                else
                    matriz[i][j] = cINFINITO;
            }
        }
    }


    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j != i)
            {
                for(int k = 0 ; k < n; k++)
                {
                    if(matriz[j][k] > matriz[j][i] + matriz[i][k])
                    {
                        //int y = matriz[j][k] + matriz[i][k], x = matriz[j][k];
                        matriz[j][k] = matriz[j][i] + matriz[i][k];
                    }
                }
            }
        }
    }

    cout << endl;
    for(int i = 0; i < n; i++){
        cout << "No " << i << ": ";
        for(int j = 0; j < n; j++){
            cout << matriz[i][j] << ", ";
        }
        cout << endl;
    }
}


int Grafo::prim()
{
    No* p = primeiro;

    if(p == NULL){
        cout << endl << "ERRO! NO NAO ENCONTRADO" << endl;
        return -1;
    }

    if(!this->pondAresta){
        cout << endl << "ERRO! ESSE GRAFO NAO E PONDERADO NAS ARESTAS";
        return -1;
    }

    if(this->direcionado){
        cout << endl << "ERRO! GRAFOS DIRECIONADOS SAO INVALIDOS";
        return -1;
    }

    vector<No*> nos;
    vector<Aresta*> arestas;
    vector<No*> cFinal;
    vector<int> visitados;


    for(; p != NULL; p = p->getProx()){
        nos.push_back(p);
    }
    p = primeiro;

    cFinal.push_back(p);
    int custoFinal = 0;


    while((int)cFinal.size() < this->numNos){

        vector<int>::iterator it2;

        Aresta* e = cFinal[0]->getAdj();
        Aresta* eMP = cFinal[0]->getAdj();
        No* noMP = this->buscaNo(e->getNoadj());
        int menorPeso = cFinal[0]->getAdj()->getPeso();

        for(int i = 0 ; i < (int)cFinal.size(); i++)
        {
            e = cFinal[i]->getAdj();

            for(; e != NULL; e = e->getProx())
            {
                it2 = find(visitados.begin(), visitados.end(), e->getNoadj());

                if(it2 != visitados.end())
                    break;

                if(e->getPeso() < menorPeso)
                {
                    menorPeso = e->getPeso();
                    noMP = this->buscaNo(e->getNoadj());
                    eMP = e;
                    visitados.push_back(eMP->getNoadj());

                }

            }

        }

        cFinal.push_back(noMP);
        arestas.push_back(eMP);
        custoFinal = custoFinal + eMP->getPeso();
    }

    /*cout << endl << "Custo minimo final: " << custoFinal << endl;
    for(int i = 0; i < (int)arestas.size(); i++){
        cout << arestas[i]->getPeso() << ", ";
    }*/

    return custoFinal;
}

static bool comparaMenorAresta(Aresta* e1, Aresta* e2)
{
    return e1->getPeso() < e2->getPeso();
}

Grafo* Grafo::kruskal()
{
    No* p = primeiro;

    if(p == NULL){
        cout << endl << "ERRO! NO NAO ENCONTRADO" << endl;
        return NULL;
    }

    if(!this->pondAresta){
        cout << endl << "ERRO! ESSE GRAFO NAO E PONDERADO NAS ARESTAS";
        return NULL;
    }

    if(this->direcionado){
        cout << endl << "ERRO! GRAFOS DIRECIONADOS SAO INVALIDOS";
        return NULL;
    }

    Grafo* h = new Grafo(0, 1);
    vector< Aresta* > arestas;
    vector< int > nos;
    vector< Aresta* >::iterator it;

    for(int i = 0; p != NULL; p = p->getProx(), i++)
    {
        nos.push_back(i);
        Aresta* e = p->getAdj();
        for(; e != NULL; e = e->getProx())
        {
            it = find(arestas.begin(), arestas.end(), e);
            if(it == arestas.end())
            {
                arestas.push_back(e);
            }
        }
    }

    sort(arestas.begin(), arestas.end(), comparaMenorAresta);

    for(int i = 0; i < (int)arestas.size() && h->getNumArestas() < this->numNos - 1; i++)
    {
        if(i % 2 == 0)
        {
            int r = arestas[i]->getNoadj();
            int q = arestas[i+1]->getNoadj();

            h->inserir(r);
            h->inserir(q);

            h->conectar(r, q, arestas[i]->getPeso());
        }
    }

    h->printGrafo();
    return h;
}

int Grafo::auxOrdenaMenorGrau(set <int> &visitados)
{
    if(primeiro != NULL && (int)visitados.size() != numNos)
    {
        No* t;
        No* p;
        for(No* i = primeiro; i != NULL; i = i->getProx())
            if(visitados.find(i->getId()) == visitados.end())
            {
                t = i;
                break;
            }
        for(p = t; p != NULL; p = p->getProx())
            if(p->getEntrada() < t->getEntrada() && visitados.find(p->getId()) == visitados.end())
                t = p;
        visitados.insert(t->getId());
        return t->getId();
    }
    return -1;
}

vector <int> Grafo::ordenaGrau()
{
    vector <int> ordenados;
    set <int> visitados;
    for(int i = 0; i < numNos; i++)
    {
        ordenados.push_back(auxOrdenaMenorGrau(visitados));
    }
    return ordenados;
}

bool Grafo::temAresta(int id1, int id2)
{
    for(No* p = primeiro; p != NULL; p = p->getProx())
    {
        if(p->getId() == id1)
            for(Aresta* a = p->getAdj(); a != NULL; a = a->getProx())
                if(a->getNoadj() == id2)
                    return true;
        else
            if(p->getId() == id2)
                for(Aresta* a = p->getAdj(); a != NULL; a = a->getProx())
                    if(a->getNoadj() == id1)
                        return true;
    }
    return false;
}

void Grafo::auxGuloso_atualizaCandidatos(std::vector <int> &candidatos, int remocao)
{
    for(int i = 0; i < (int)candidatos.size(); i++)
    {
        if(candidatos[i] != remocao)
        {
            if(temAresta(remocao, candidatos[i]))
            {
                candidatos.erase(candidatos.begin() + i);
                i--;
            }
        }
        else
        {
            candidatos.erase(candidatos.begin() + i);
            i--;
        }
    }
}

int Grafo::getRandomIntNumber(int nMin, int nMax)
{
    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generator (seed);  // mt19937 is a standard mersenne_twister_engine
    std::uniform_int_distribution <int> dis(nMin, nMax);

    return dis(generator);
}

double Grafo::getRandomFloatNumber(double nMin, double nMax)
{
    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generator (seed);  // mt19937 is a standard mersenne_twister_engine
    std::uniform_real_distribution <double> dis(nMin, nMax);

    cout << dis(generator) << endl;
    return dis(generator);
}

vector <int> Grafo::guloso()
{
    vector < int > solucao;
    std::vector <int> candidatos = ordenaGrau();

    while(!candidatos.empty())
    {
        solucao.push_back(candidatos[0]);
        auxGuloso_atualizaCandidatos(candidatos, candidatos[0]);
    }

    return solucao;
}

vector <int> Grafo::gulosoRandomizado(float alfa, int itera)
{
    int i;
    vector <int> solucaoFinal;

    cout << endl << "Procurando solucao";
    //cout.flush();
    for(int j = 0; j < itera; j++)
    {

        for (int i = 0; i < 3; i++)
        {
            cout << ".";
            //cout.flush();
            Sleep(300);
        }
        cout << "\b\b\b   \b\b\b";


        vector <int> solucaoAtual;
        vector <int> candidatos = ordenaGrau();

        while(!candidatos.empty())
        {
            i = getRandomIntNumber(0, candidatos.size() * alfa);
            solucaoAtual.push_back(candidatos[i]);
            auxGuloso_atualizaCandidatos(candidatos, candidatos[i]);
        }

        if(solucaoAtual.size() > solucaoFinal.size())
            solucaoFinal = solucaoAtual;
    }
    return solucaoFinal;
}


void Grafo::atualizaProb(vector <float> &alfas, vector <int> &cont, vector <int> &numNosSol, vector <int> &sol, vector <double> &p, int delta)
{
    vector <float> q;
    float somatorio = 0;
    for(int i = 0; i < (int)alfas.size(); i++)
    {
        q[i] = pow(sol.size() / (numNosSol[i] / cont[i]), delta);
        somatorio += q[i];
    }
    for(int i = 0; i < (int)p.size(); i++)
    {
        p[i] = q[i] / somatorio;
    }
}

int Grafo::selecionaAlfa(vector <double> p)
{
    int indexAlfa;
    double perc = getRandomFloatNumber(0.0, 100.0);
    cout << "rand: " << perc << endl;
    double s = 0;
    for(int i = 0; i < (int)p.size(); i++)
    {
        s += (p[i] * 100);
        if(s >= perc)
        {
            indexAlfa = i;
            break;
        }
    }
    return indexAlfa;
}

void Grafo::atualizaDados(vector <int> &sol, int indexAlfa, vector <int> &cont, vector <int> &numNosSol)
{
    cont[indexAlfa]++;
    numNosSol[indexAlfa] = sol.size();
}

vector <int> Grafo::gulosoRandomizadoReativo(int maxItera, int bloco)
{
    vector <int> solucaoAtual;
    vector <int> solucaoFinal;
    vector <float> alfas;
    vector <double> p;
    vector <int> cont;
    vector <int> numNosSol;

    float alfai = 0.05;

    while(alfai <= 0.3)
    {
        alfas.push_back(alfai);
        alfai += 0.05;
        cout << "teste" << alfai << endl;
    }


    for(int i = 0; i < (int)alfas.size(); i++)
    {
        cout << alfas[i] << endl;
    }

    for(int i = 0; i < (int)alfas.size(); i++)
    {
        p.push_back(1.0 / alfas.size());
    }

    for(int i = 0; i < (int)alfas.size(); i++)
    {
        solucaoAtual = gulosoRandomizado(alfas[i], 30);
        if(solucaoAtual.size() > solucaoFinal.size())
            solucaoFinal = solucaoAtual;
        atualizaDados(solucaoAtual, i, cont, numNosSol);
    }
    //if(i % bloco == 0)
    //  atualizaProb(alfas, cont, numNosSol, solucaoAtual, p, 100);

    for(int i = 0; i < maxItera; i++)
    {
        cout << "teste 1" << endl;
        if(i % bloco == 0)
            atualizaProb(alfas, cont, numNosSol, solucaoAtual, p, 100);
        cout << "teste 2" << endl;
        int indexAlfa = selecionaAlfa(p);
        cout << "teste 3" << endl;
        cout << "indexAlfa: " << indexAlfa << " alfa: " << endl;
        solucaoAtual = gulosoRandomizado(alfas[indexAlfa], 1);
        cout << "teste 4" << endl;
        if(solucaoAtual.size() > solucaoFinal.size())
            solucaoFinal = solucaoAtual;

        atualizaDados(solucaoAtual, indexAlfa, cont, numNosSol);
    }

    return solucaoFinal;
}

vector <int> Grafo::subconjuntoIndependenteMaxG()
{
    clock_t ticks[2];
    ticks[0] = clock();
    vector <int> solucao = guloso();
    ticks[1] = clock();
    double funcTime = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    funcTime = funcTime / 1000;
    cout << endl << "Subconjunto independente maximo obtido pelo algoritmo guloso randomizado: " << endl;
    for(int i = 0; i < (int)solucao.size(); i++)
        cout << solucao[i] << endl;
    cout << endl << "Numero de nos na solucao: " << solucao.size() << endl;
    cout << "Tempo gasto: " << funcTime << " s." << endl;
    return solucao;
}

vector <int> Grafo::subconjuntoIndependenteMaxGR()
{
    clock_t ticks[2];
    ticks[0] = clock();
    vector <int> solucao = gulosoRandomizado(0.05, 10);
    ticks[1] = clock();
    double funcTime = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    funcTime = funcTime / 1000;
    cout << endl << "Subconjunto independente maximo obtido pelo algoritmo guloso randomizado: " << endl;
    for(int i = 0; i < (int)solucao.size(); i++)
        cout << solucao[i] << endl;
    cout << endl << "Numero de nos na solucao: " << solucao.size() << endl;
    cout << "Tempo gasto: " << funcTime << " s." << endl;
    return solucao;
}


vector <int> Grafo::subconjuntoIndependenteMaxGRR()
{
    clock_t ticks[2];
    ticks[0] = clock();
    vector <int> solucao = gulosoRandomizadoReativo(30, 1000);
    ticks[1] = clock();
    double funcTime = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    funcTime = funcTime / 1000;
    cout << endl << "Subconjunto independente maximo obtido pelo algoritmo guloso randomizado: " << endl;
    for(int i = 0; i < (int)solucao.size(); i++)
        cout << solucao[i] << endl;
    cout << endl << "Numero de nos na solucao: " << solucao.size() << endl;
    cout << "Tempo gasto: " << funcTime << " s." << endl;
    return solucao;
}

