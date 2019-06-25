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
/*
Grafo::Grafo()
{
    cout << "\nA graph has been created\n";

    ListaNo = NULL;
    nAresta = 0;
    grau = 0;
    direcionado = false;
    pondNo = false;
    pondAresta = false;
}
*/
Grafo::Grafo(bool dir)
{
    cout << "A graph has been created.\n" << endl;
    ListaNo = NULL;
    nAresta = 0;
    grau = 0;
    n = 0;
    e = 0;
    direcionado = dir;
    pondNo = false;
    pondAresta = false;
}

Grafo::~Grafo()
{
    for(No* t = ListaNo; t != NULL;)
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

bool Grafo::busca(int id)
{
    for(No* p = ListaNo; p != NULL; p = p->getProx())
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
        if(ListaNo != NULL)
        {
            for(No *i = ListaNo; i != NULL; i = i->getProx())
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
            ListaNo = p;
            ListaNo->setProx(NULL);
            ListaNo->setAnt(NULL);
        }
        n++;
    }
    else
        return;
}

void Grafo::conectar(int id1, int id2)
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
            for(No *n = ListaNo; n != NULL; n = n->getProx())
            {
                if(n->getId() == id1)
                {
                    n->alocarAdj(id2);
                    n->setSaida(n->getSaida() + 1);
                }
                if(n->getId() == id2)
                {
                    n->setEntrada(n->getEntrada() + 1);
                }
            }
            e++;
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
            for(No *n = ListaNo; n != NULL; n = n->getProx())
            {
                if(n->getId() == id1)
                {
                    n->alocarAdj(id2);
                    n->setEntrada(n->getEntrada() + 1);
                }
                if(n->getId() == id2)
                {
                    n->alocarAdj(id1);
                    n->setEntrada(n->getEntrada() + 1);
                }
            }
            e++;
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
    for(No *n = ListaNo; n != NULL; n = n->getProx())
    {
        if(n->getId() == id1)
        {
            //for(Aresta* a = n->getAdj())
        }
        if(n->getId() == id2)
            n->alocarAdj(id1);
    }
}
///----------------------------------------------------------------
void Grafo::caminhamentoLargura()
{
    set < int > visitados;
    No* primeiro = ListaNo;
    auxCaminhamentoLargura(primeiro, visitados);
}

vector < int > Grafo::auxCaminhamentoLargura(No* p, set < int > &visitados)
{
    queue < int > fila;
    int vertice = p->getId();
    fila.push(vertice);
    visitados.insert(p->getId());

    vector < int > componente;
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
        for(i = ListaNo; i != NULL; i = i->getProx())
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

void Grafo::caminhamentoProf()
{
    set < int > visitados;
    No* p = ListaNo;
    auxCaminhamentoProf(p, visitados);
}

void Grafo::auxCaminhamentoProf(No* p, set < int > &visitados)
{
    stack < int > pilha;
    int vertice = p->getId();
    pilha.push(vertice);
    visitados.insert(p->getId());

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
                //cout << a->getNoadj() << endl;
            }
        }
    }
}

void Grafo::printGrafo()
{
    for(No* p = ListaNo; p != NULL; p = p->getProx())
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
    for(No* p = ListaNo; p != NULL; p = p->getProx())
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

int Grafo::componentesConexas()
{
    vector < int > c;
    int cont = 0;
    set < int > visitados;
    No* p = ListaNo;
    set < set < int > > componentes;
    if(ehConexo(visitados))
    {
        cout << "Componente " << cont << " " << endl;
        c = auxCaminhamentoLargura(p, visitados);
        cont++;
        return cont;
    }
    else
    {
        vector < vector < int > > componentes;
        //cont++;
        for(No* p = ListaNo; p != NULL; p = p->getProx())
        {
            if(visitados.find(p->getId()) == visitados.end())
            {
                set < int > comp;
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
        componente.insert(ListaNo);
        set < No* > ::iterator it;
        it = componente.begin();
        cout << "teste iterator de p, id: " << (*it)->getId();
        */
        return cont;
    }
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
    No* p = ListaNo;
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
    for(No* p = ListaNo; p != NULL; p = p->getProx())
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
    if(e > n - 1 || !direcionado)
    {
        cout << "\nGrafo possui pelo menos um ciclo, Ordenacao Topologica impossivel" << endl;
        //exit(0);
        return;
    }

    No* p = ListaNo;
    vector<No*> nos;
    vector<int> ot;
    queue<No*>fontes;

    No** visitados = new No*[n]();

    for(; p != NULL; p = p->getProx())
    {
        nos.push_back(p);
        if(p->getEntrada() == 0)
            fontes.push(p);
    }


    while(!fontes.empty())
    {
        No* r = fontes.front();
        auxOT(r, ot, visitados, n);
        fontes.pop();
    }

    cout << "\nOrdenacao topologica: ";
    for (int i = 0; i < (int)ot.size(); i++)
    {
        cout << ot[i] << ", ";
    }
}

int Grafo::auxOrdenaGrau(set <int> &visitados)
{
    if(ListaNo != NULL && (int)visitados.size() != n)
    {
        No* t;
        No* p;
        for(No* i = ListaNo; i != NULL; i = i->getProx())
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
    for(int i = 0; i < n; i++)
    {
        ordenados.push_back(auxOrdenaGrau(visitados));
    }
    return ordenados;
}

bool Grafo::temAresta(int id1, int id2)
{
    for(No* p = ListaNo; p != NULL; p = p->getProx())
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

float Grafo::getRandomFloatNumber(float nMin, float nMax)
{
    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

    std::mt19937 generator (seed);  // mt19937 is a standard mersenne_twister_engine
    std::uniform_real_distribution <float> dis(nMin, nMax);

    return dis(generator);
}

vector <int> Grafo::gulosoIndependente()
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

vector <int> Grafo::gulosoIndependenteRandomizado(float alfa, int itera)
{
    int i;
    vector < int > solucaoFinal;

    cout << "Procurando solucao";
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
        std::vector <int> candidatos = ordenaGrau();

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

vector <int> Grafo::subconjuntoIndependenteMax()
{
    clock_t ticks[2];
    ticks[0] = clock();
    vector <int> sol = gulosoIndependenteRandomizado(0.05, 10);
    ticks[1] = clock();
    double funcTime = (ticks[1] - ticks[0]) * 1000.0 / CLOCKS_PER_SEC;
    funcTime = funcTime / 1000;
    cout << endl << "Subconjunto independente maximo obtido pelo algoritmo guloso randomizado: " << endl;
    for(int i = 0; i < (int)sol.size(); i++)
        cout << sol[i] << endl;
    cout << endl << "Numero de nos na solucao: " << sol.size() << endl;
    cout << "Tempo gasto: " << funcTime << " s." << endl;
    return sol;
}

void Grafo::atualizaProb(vector <float> &alfas, vector <int> &cont, vector <int> &numNosSol, vector <int> &sol, vector <float> &p, int delta)
{
    vector <float> q;
    float s = 0;
    for(int i = 0; i < alfas.size(); i++)
    {
        q[i] = pow((sol.size() / alfas[i]), delta);
        s += q[i];
    }
    for(int i = 0; i < p.size(); i++)
    {
        p[i] = q[i] / s;
    }
}

int Grafo::selecionaAlfa(vector <float> p)
{
    int indexAlfa;
    float perc = getRandomFloatNumber(0, 100);
    float s = 0;
    for(int i = 0; i < p.size(); i++)
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

vector <int> Grafo::gulosoIndependenteReativo(int maxItera, int bloco)
{
    vector <int> solucaoAtual = gulosoIndependenteRandomizado(0.05, 30);
    vector <int> solucaoFinal = solucaoAtual;
    vector <float> alfas;
    for(int i = 0.05, j = 0; i < 0.5; i += 0.05, j++)
    {
        alfas[j] = i;
    }

    vector <float> p;
    for(int i = 0; i < alfas.size(); i++)
    {
        p[i] = 1 / n;
    }

    vector <int> cont;
    cont[0] = 1;
    for(int i = 1; i < alfas.size(); i++)
    {
        cont[i] = 0;
    }
    vector <int> numNosSol;
    numNosSol[0] = solucaoAtual.size();
    for(int i = 1; i < alfas.size(); i++)
    {
        numNosSol[i] = 0;
    }


    for(int i = 1; i < maxItera; i++)
    {
        if(i % bloco == 0)
            atualizaProb(alfas, cont, numNosSol, solucaoAtual, p, 100);

        int indexAlfa = selecionaAlfa(p);
        solucaoAtual = gulosoIndependenteRandomizado(alfas[indexAlfa], 1);

        if(solucaoAtual.size() > solucaoFinal.size())
            solucaoFinal = solucaoAtual;

        atualizaDados(solucaoAtual, indexAlfa, cont, numNosSol);
    }

    return solucaoFinal;
}



