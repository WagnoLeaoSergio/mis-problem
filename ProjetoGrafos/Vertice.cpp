#include "Vertice.h"

int Vertice::getDis(){
    return dis;
}
void Vertice::setDis(int x){
    dis = x;
}

int Vertice::getNum(){
    return num;
}
void Vertice::setNum(int x){
    num = x;
}

Vertice* Vertice::getAnt(){
    return ant;
}
void Vertice::setAnt(Vertice *p){
    ant = p;
}

Vertice* Vertice::getProx(){
    return prox;
}
void Vertice::setProx(Vertice *p){
    prox = p;
}
