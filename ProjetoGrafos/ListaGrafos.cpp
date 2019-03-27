#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define DNULO = 10000000000
#include "ListaGrafos.h"

ListaGrafos::ListaGrafos(int tam){
    *vet = new ListaGrafosVizinho[tam];
    tam_max = tam;
    n = 0;
}

ListaGrafos::~ListaGrafos(){
    delete vet;
    n = 0;
}

void ListaGrafos::criarVertice(int valor, int num_vertice){
    if(n == tam_max){
        printf("\nERRO! TAMANHO MAXIMO ATINGIDO");
        exit(1);
    }
    /*else{
        if(valor == 0)
            vet[n]->insereUltimo(DNULO, num_vertice);
        else
            vet[n]->insereUltimo(valor, num_vertice);
    }*/
    else{
        vet[n]->insereUltimo(-1 , -1);
    }
    n++;
}

void ListaGrafos::conectar(int x1, int x2, int distancia){
    bool temX1 = false, temX2 = false;
    for(int i = 0; i < n; i++){
        if(x1 == i)
            temX1 = true;
        if(x2 == i && x2 != x1)
            temX2 = true;
    }
    if(x1 == false || x2 == false){
        printf("\nERRO! VERTICE(S) NAO ENCONTRADO(S)");
        exit(1);
    }
    else{
        vet[x1]->insereUltimo(distancia, x2);
        vet[x2]->insereUltimo(distancia, x1);
    }
}
