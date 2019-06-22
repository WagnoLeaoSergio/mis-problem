#include <stdio.h>
#include <iostream>
#include <queue>
#include <set>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "Grafo.h"
#include <limits>
#include <utility>

using namespace std;



Grafo::Grafo(bool dir)
{
    cout << "\nA graph has been created\n";
    ListaNo = NULL;
    numeroDeNos = 0;
    numeroDeArestas = 0;
    grau = 0;
    direcionado = dir;
    pondNo = false;
    pondAresta = false;
}

Grafo::Grafo(bool dir, bool ponderadoNo, bool ponderadoAresta)
{
    cout << "\nA graph has been created\n";
    ListaNo = NULL;
    numeroDeNos = 0;
    numeroDeArestas = 0;
    grau = 0;
    direcionado = dir;
    pondNo = ponderadoNo;
    pondAresta = ponderadoAresta;
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
    cout << "\nA graph has been destroyed\n";
}


No* Grafo::getPrimeiro()
{
    return this->ListaNo;
}


int Grafo::getNumeroDeNos() {
    return numeroDeNos;
}
int Grafo::getNumeroDeArestas() {
    return numeroDeArestas;
}

void  Grafo::inserirNoNaoPonderado(int id)
{

    if (numeroDeNos != 0 && this->buscaNo(id) != NULL){
        //cout << endl << "Um no com o ID " << id << " ja esta inserido" << endl;
        return;
    }

    No* n1 = new No();
    n1->setAnt(NULL);
    n1->setProx(NULL);
    n1->setId(id);
    n1->setEntrada(0);
    n1->setSaida(0);

    if(ListaNo == NULL)
    {
        ListaNo = n1;

    }

    else if(ListaNo->getAnt() == NULL && ListaNo->getProx() == NULL)
    {
        ListaNo->setProx(n1);
        n1->setAnt(ListaNo);

    }
    else
    {
        No*p = ListaNo;

        for(; p->getProx() != NULL; p = p->getProx()) {}

        p->setProx(n1);
        n1->setAnt(p);

    }

    numeroDeNos++;

}


void  Grafo::inserirNoPonderado(int id, int p)
{

    if (numeroDeNos != 0 && this->buscaNo(id) != NULL){
        //cout << endl << "Um no com o ID " << id << " ja esta inserido" << endl;
        return;
    }

    No* n1 = new No();
    n1->setAnt(NULL);
    n1->setProx(NULL);
    n1->setId(id);
    n1->setPeso(p);
    n1->setAdj(NULL);
    n1->setEntrada(0);
    n1->setSaida(0);

    if(ListaNo == NULL)
    {
        ListaNo = n1;
        cout << n1->getId();
    }

    else if(ListaNo->getAnt() == NULL && ListaNo->getProx() == NULL)
    {
        ListaNo->setProx(n1);
        n1->setAnt(ListaNo);
    }
    else
    {
        No*p = ListaNo;

        for(; p->getProx() != NULL; p = p->getProx()) {}

        p->setProx(n1);
        n1->setAnt(p);

    }

    numeroDeNos++;

}


void Grafo::inserirNo(int id, int p){
    if(this->pondNo)
        this->inserirNoPonderado(id, p);
    else
        this->inserirNoNaoPonderado(id);
}


void Grafo::plotarGrafo()
{
    No* p = ListaNo;
    cout << "\n////////////////////////////////\n";
    for(; p != NULL; p = p->getProx())
    {
        cout << "\n" << p->getId() << "-> ";
        Aresta* a = p->getAdj();

        if(a != NULL){

            for(; a != NULL; a = a->getProx())
            {
                cout << a->getNoadj() << " , ";
            }
        }
            cout << "\n";
    }
    cout << "\n////////////////////////////////\n";
}


//EM OBRAS
void Grafo::excluirNo(int id)
{
    No* p = this->buscaNo(id);

    if(p == NULL)
    {
        cout << "\nERRO! NO NAO ENCONTRADO\n";
        exit(1);
    }

    int idn = p->getId();
    Aresta* a = p->getAdj();

    while(a != NULL)
    {
        No* aux = this->buscaNo(a->getNoadj());

        Aresta* a2 = aux->getAdj();

        while(a2->getNoadj() != p->getId() && a2 != NULL){

            a2 = a2->getProx();
        }

        if(a2->getAnt() != NULL && a2->getProx() != NULL)
        {
            a2->getAnt()->setProx(a2->getProx());
            a2->getProx()->setAnt(a2->getAnt());
            delete a2;
        }

        else if(a2->getAnt() == NULL && a2->getProx() != NULL)
        {
            aux->setAdj(a2->getProx());
            a2->getProx()->setAnt(NULL);
            delete a2;
        }

        else if(a2->getAnt() != NULL && a2->getProx() == NULL)
        {
            a2->getAnt()->setProx(NULL);
            delete a2;
        }

        else if(a2->getAnt() == NULL && a2->getProx() == NULL)
        {
            aux->setAdj(NULL);
            delete a2;
        }

        a = a->getProx();
    }

    if(p->getAnt() == NULL && p->getProx() == NULL) {}

    else if(p->getAnt() == NULL && p->getProx() != NULL)
        p->getProx()->setAnt(NULL);

    else if(p->getAnt() != NULL && p->getProx() == NULL)
        p->getAnt()->setProx(NULL);

    else
    {
        p->getAnt()->setProx(p->getProx());
        p->getProx()->setAnt(p->getAnt());
    }
    delete p;

    cout << "\nNo "<< idn <<" Excluido\n";

}


//EM OBRAS
void Grafo::excluirNoDirecionado(int id)
{
    No* n1 = this->buscaNo(id);

    if(n1 == NULL)
    {
        cout << "\nERRO! O NO NAO ESTA NO GRAFO";
        exit(1);
    }

    for(No* p = ListaNo; p != NULL; p = p->getProx())
    {
        Aresta* a = p->getAdj();
        for(; a != NULL; a = a->getProx())
        {
            if(a ->getNoadj() == n1->getId())
            {
                p->setEntrada(p->getEntrada() - 1);

                if(a->getAnt() != NULL && a->getProx() != NULL)
                {
                    a->getAnt()->setProx(a->getProx());
                    a->getProx()->setAnt(a->getAnt());
                }

                else if(a->getAnt() == NULL && a->getProx() != NULL)
                {
                    p->setAdj(a->getProx());
                    a->getProx()->setAnt(NULL);
                }

                else if(a->getAnt() != NULL && a->getProx() == NULL)
                {
                    a->getAnt()->setProx(NULL);
                }

                else if(a->getAnt() == NULL && a->getProx() == NULL)
                {
                    p->setAdj(NULL);
                }
                delete a;
            }
        }
    }

    if(n1->getAnt() == NULL && n1->getProx() == NULL)
    {
        this->ListaNo = NULL;
    }

    else if(n1->getAnt() == NULL && n1->getProx() != NULL)
        n1->getProx()->setAnt(NULL);

    else if(n1->getAnt() != NULL && n1->getProx() == NULL)
        n1->getAnt()->setProx(NULL);

    else
    {
        n1->getAnt()->setProx(n1->getProx());
        n1->getProx()->setAnt(n1->getAnt());
    }
    delete n1;

}


void Grafo::conectarNaoDirecionado(int id1, int id2, int peso)
{
    if(ListaNo == NULL)
    {
        cout << "\nERRO! GRAFO VAZIO";
        exit(1);
    }
    else if(id1 == id2)
    {
        cout << "\nERRO! SELF LOOP NAO PERMITIDO";
        exit(2);
    }
    else if(this->conectado(id1, id2))
    {
        //cout << "\nERRO! MULTIARESTA NAO PERMITIDO";
        return;
    }

    No* p = ListaNo;
    No* n1 = NULL;
    No* n2 = NULL;

    for (; p != NULL; p = p->getProx())
    {

        if(p->getId() == id1)
            n1 = p;
        else if(p->getId() == id2)
            n2 = p;
    }
    if(n1 == NULL || n2 == NULL)
    {
        cout << "\nERRO! UM DOS NOS NAO ESTA NO GRAFO";
        exit(1);
    }
    else
    {


        Aresta* a1 = new Aresta();
        a1->setNoAdj(id2);
        a1->setProx(NULL);
        a1->setAnt(NULL);
        a1->setPeso(peso);

        Aresta* a2 = new Aresta();
        a2->setNoAdj(id1);
        a2->setProx(NULL);
        a2->setAnt(NULL);
        a2->setPeso(peso);

        if(n1->getAdj() == NULL)
        {
            n1->setAdj(a1);
        }
        else
        {
            Aresta* aux = n1->getAdj();

            while(aux->getProx() != NULL)
            {
                aux = aux->getProx();
            }

            aux->setProx(a1);
            a1->setAnt(aux);
        }



        if(n2->getAdj() == NULL)
        {
            n2->setAdj(a2);
        }
        else
        {
            Aresta* aux = n2->getAdj();

            while(aux->getProx() != NULL)
            {
                aux = aux->getProx();
            }

            aux->setProx(a2);
            a2->setAnt(aux);
        }

        n1->setEntrada( n1->getEntrada() + 1);
        n2->setEntrada( n2->getEntrada() + 1);

        cout << "\nNos "<< n1->getId() << " e " << n2->getId() << " conectados \n";
        numeroDeArestas++;
    }


}


void Grafo::conectarDirecionado(int id1, int id2, int peso)
{
    if(ListaNo == NULL)
    {
        cout << "\nERRO! GRAFO VAZIO";
        exit(1);
    }
    else if(id1 == id2)
    {
        cout << "\nERRO! SELF LOOP NAO PERMITIDO";
        exit(2);
    }
    else if(this->conectado(id1, id2))
    {
        cout << "\nERRO! MULTIARESTA NAO PERMITIDO";
        return;
    }

    No* n1  = this->buscaNo(id1);
    No* n2 = this->buscaNo(id2);

    if(n1 == NULL || n2 == NULL)
    {
        cout << "\nERRO! UM DOS NOS NAO ESTA NO GRAFO";
        exit(3);
    }

    Aresta* a = new Aresta();
    a->setAnt(NULL);
    a->setProx(NULL);
    a->setNoAdj(n2->getId());

    if(n1->getAdj() == NULL)
    {
        n1->setAdj(a);
    }
    else
    {
        Aresta* aux = n1->getAdj();

        for(; aux->getProx() != NULL; aux = aux->getProx() ){}

        aux->setProx(a);
        a->setAnt(aux);
    }

    n1->setSaida(n1->getSaida() + 1);
    n2->setEntrada(n2->getEntrada() + 1);

    cout << "\nNo " << n1->getId() << " direcionado para o no " << n2->getId();
   numeroDeArestas++;

}


void Grafo::conectar(int id1, int id2, int p)
{
    int peso;
    if(this->pondAresta)
        peso = p;
    else
        peso = 0;

    if(this->direcionado)
        conectarDirecionado(id1, id2, peso);
    else
        conectarNaoDirecionado(id1, id2, peso);
}

int Grafo::contaNos()
{
    No* p = ListaNo;
    int i = 0;
    for (; p != NULL; p = p->getProx(), i++) {}

    return i;
}

No* Grafo::buscaNo(int id)
{
    if(ListaNo == NULL)
    {
        cout << "ERRO! GRAFO VAZIO";
        exit(1);
    }

    No* p = ListaNo;
    No* q = NULL;

    for(; p != NULL; p = p->getProx())
    {
        if(p->getId() == id)
        {
            q = p;
        }
    }
    return q;
}

void Grafo::listarAdjacentes(int id)
{
    if(ListaNo == NULL)
    {
        cout << "\nERRO! GRAFO VAZIO";
        exit(1);
    }

    No* p = this->buscaNo(id);


    if(p == NULL)
    {
        cout << "\nERRO! O NO NAO ESTA NO GRAFO";
        exit(2);
    }
    else
    {
        cout << "\nNos adjacentes:";
        Aresta* aux = p->getAdj();
        for(; aux != NULL; aux = aux->getProx())
        {
            cout << "\n" << aux->getNoadj();
        }
    }

}


void Grafo::caminharEmLargura()
{
    if(ListaNo == NULL)
    {
        cout << "\nERRO! GRAFO VAZIO";
        exit(1);
    }
    auxCaminharEmLargura(ListaNo, numeroDeNos);
}

void Grafo::auxCaminharEmLargura(No* primeiro, int n)
{
    No* p = primeiro;
    No** visitados = new No*[n]();
    int j = 0;

    cout << "\n/////////// INICIO DO CAMINHAMENTO/////////////////\n";


    //cout << "\nNumero de vertices: " << n << "\n";

    for(int i = 0; i < n; i++)
    {
        visitados[i] = NULL;
    }

    queue<No*> fila;
    fila.push(p);
    visitados[0] = p;

    //cout << "\nNo atual: " << p->getId() << "\n";

    j++;

    while(!(fila.empty()))
    {

        No* q = fila.front();
        fila.pop();

        cout << q->getId() << "\n";

        Aresta* a = q->getAdj();


        for(; a != NULL; a = a->getProx())
        {
            //cout << "\nNo conectado ao no atual: " << a->getNoadj() << "\n";

            bool jaFoi = false;
            No* aux = this->buscaNo(a->getNoadj());

            for(int i = 0; i < n; i++)
            {
                if(visitados[i] == aux)
                {
                    jaFoi = true;
                }

            }
            //cout << "\nO no conectado ja foi?: " << jaFoi << "\n";
            //cout << "\nPosicao de visitados atual: " << j << "\n";

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
    if(j < n)
        cout << "\nEsse grafo nao eh conexo\n";
    else if(j == n)
        cout << "\nEsse grafo eh conexo\n";

    cout << "\n/////////// FIM DO CAMINHAMENTO/////////////////\n";
}


void Grafo::caminharEmProfundidadeAuxiliar(No* p, int* visitados, int* nos){

    int i = 0;
    for(; i < this->numeroDeNos; i++){
        if(nos[i] == p->getId())
            break;
    }


    cout << endl << nos[i];
    visitados[i] = 1;

    Aresta* e = p->getAdj();
    for(; e != NULL; e = e->getProx())
    {
        int j = 0;
        for(; j < this->numeroDeNos; j++){
            if(nos[j] == e->getNoadj())
                break;
        }
        if(visitados[j] == 0){
            No* q = this->buscaNo(e->getNoadj());
            this->caminharEmProfundidadeAuxiliar(q, visitados, nos);
        }
    }


}

void Grafo::caminharEmProfundidade() {

    No* p = ListaNo;
    int visitados[this->numeroDeNos];
    int nos[this->numeroDeNos];

    for(int i = 0; i < numeroDeNos && p != NULL; i++, p = p->getProx()) {
        visitados[i] = -1;
        nos[i] = p->getId();
    }

    p = ListaNo;

    for(int i = 0; p != NULL; p = p->getProx(), i++){
        if(visitados[i] == -1)
            this->caminharEmProfundidadeAuxiliar(p, visitados, nos);
    }
}


bool Grafo::conectado(int id1, int id2)
{
    bool conected = false;
    No* n1 = this->buscaNo(id1);

    for(Aresta* a = n1->getAdj(); a != NULL; a = a->getProx())
    {
        if(a->getNoadj() == id2)
            conected = true;
    }
    return conected;
}

Grafo* Grafo::grafoReverso(){

    Grafo *s = new Grafo(this->direcionado);
    No* p = ListaNo;
    for(; p != NULL; p = p->getProx()){
        s->inserirNo(p->getId(), p->getPeso());
    }

    p = ListaNo;
    No* q = p;

    for(; p != NULL; p = p->getProx())
    {
        for(; q != NULL; q = q->getProx())
        {
            if(p != q && (this->conectado(p->getId(), q->getId())))
            {
                int peso;
                if(p->getAdj() != NULL)
                    peso = p->getAdj()->getPeso();
                else {
                    if(q->getAdj() != NULL)
                        peso = q->getAdj()->getPeso();
                    else
                        peso = 0;
                    }
                s->conectar(q->getId(), p->getId(), peso);
            }
        }

        q = ListaNo;
    }

    return s;
}

Grafo* Grafo::copiarGrafo()
{
    Grafo* h = new Grafo(1);

    No* p = ListaNo;
    for(; p != NULL; p = p->getProx())
    {
        h->inserirNo(p->getId(), p->getPeso());
    }

    p = ListaNo;

    for(; p != NULL; p = p->getProx()){

        Aresta* a = p->getAdj();
        for(; a != NULL ; a = a->getProx())
        {
            h->conectar(p->getId(), a->getNoadj(), a->getPeso());
        }
    }

    return h;

}

static bool comparador1(No* n1, No* n2)
{
    return n1->getEntrada() < n2->getEntrada();
}

No** Grafo::ordenaPorGrau()
{
    No* p = ListaNo;
    vector< No* >nos;
    for(; p != NULL; p = p->getProx()){
        nos.push_back(p);
    }

    sort(nos.begin(), nos.end(), comparador1);

    return nos.data();
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
    No* p = ListaNo;
    int n = this->contaNos();

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



void Grafo::DFSAux(No* p, std::vector<int>* visitados, int* nos, std::stack< No* >* pilha){

    int i = 0;
    for(; i < this->numeroDeNos; i++){
        if(nos[i] == p->getId())
            break;
    }


    cout << endl << nos[i];
    (*visitados)[i] = 1;

    Aresta* e = p->getAdj();
    No* q;

    for(; e != NULL; e = e->getProx())
    {
        int j = 0;
        for(; j < this->numeroDeNos; j++){
            if(nos[j] == e->getNoadj())
                break;
        }
        if((*visitados)[j] == -1){
            q = this->buscaNo(e->getNoadj());
            this->DFSAux(q, visitados, nos, pilha);
        }
    }

    pilha->push(q);
}

vector<int>* Grafo::DFS(No* q, std::stack< No* >* pilha){

    No* p = ListaNo;
    vector<int>* visitados = new vector<int>();
    int nos[this->numeroDeNos];

    for(int i = 0; i < numeroDeNos && p != NULL; i++, p = p->getProx()) {
        visitados->push_back(-1);
        nos[i] = p->getId();
    }

    this->DFSAux(q, visitados, nos, pilha);

    cout << endl << "Componente fortemente conexa: ";
    for(int j = 0 ; j < (int)visitados->size(); j++){
        if((*visitados)[j] == 1)
            cout << nos[j] << ", ";
    }
    cout << endl;

    return visitados;
}



void Grafo::componentesFortementeConexas()
{
    if(!this->direcionado){
        cout << endl << "ERRO! O GRAFO NAO E DIRECIONADO";
        return;
    }

    stack< No* >* pilha = new stack< No* >();
    stack< No* >* aux = new stack< No* >();
    Grafo* h = this->grafoReverso();

    vector<int>* pathT = h->DFS(h->getPrimeiro(), pilha);

    /*while(!pilha->empty())
    {
        No* r = pilha->top();
        pilha->pop();
        this->DFS(r, aux);
    }*/

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
    No* q = ListaNo;

    for(int i = 0 ; i < numeroDeNos && q != NULL; i++, q = q->getProx())
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
    int n = this->numeroDeNos;
    int matriz[n][n];
    vector<No*> nosIndice;
    No* p = ListaNo;
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
                if(this->conectado(nosIndice[i]->getId(), nosIndice[j]->getId()))
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
    No* p = ListaNo;

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
    p = ListaNo;

    cFinal.push_back(p);
    int custoFinal = 0;


    while((int)cFinal.size() < this->numeroDeNos){

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

static bool comparador2(Aresta* e1, Aresta* e2)
{
    return e1->getPeso() < e2->getPeso();
}

Grafo* Grafo::kruskal()
{
    No* p = ListaNo;

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

    Grafo* h = new Grafo(0, this->pondNo, 1);
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

    sort(arestas.begin(), arestas.end(), comparador2);

    for(int i = 0; i < (int)arestas.size() && h->getNumeroDeArestas() < this->numeroDeNos - 1; i++)
    {
        if(i % 2 == 0)
        {
            int r = arestas[i]->getNoadj();
            int q = arestas[i+1]->getNoadj();

            h->inserirNo(r, 0);
            h->inserirNo(q, 0);

            h->conectar(r, q, arestas[i]->getPeso());
        }
    }

    h->plotarGrafo();
    return h;
}
