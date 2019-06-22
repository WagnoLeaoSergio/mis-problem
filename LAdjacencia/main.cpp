#include <iostream>
#include "Grafo.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void carregaGrafo(Grafo* g, char entrada[]){


    ifstream arquivo;
    arquivo.open(entrada, ifstream::in);

    if(arquivo.is_open()){

        string strNumeroDeNos;
        int N;

        getline(arquivo, strNumeroDeNos);

        stringstream issNos(strNumeroDeNos);

        issNos >> N;


        int id1, id2 , peso;
        string linha;
        string c;

        //getline(arquivo, c);

        while(!arquivo.eof() && getline(arquivo, linha).good()){

            stringstream(linha) >> id1 >> id2 >> peso;

            g->inserirNo(id1, 0);
            g->inserirNo(id2, 0);
            g->conectar(id1, id2, peso);

            //getline(arquivo, c);
        }

        arquivo.close();
    }
    else
        cout << endl << "ERRO NA ABERTURA DE ARQUIVO" << endl;

}


int main(int agrc, char* argv[])
{

    //string path(argv[1]);

    char caminho[] = "C:\\Users\\Waguinho\\Documents\\benchmark\\teste3.txt";

    //Grafo t(argv[2], argv[3], argv[4]);
    Grafo t(1, 0, 1);

    //carregaGrafo(&t,argv[1]);
    carregaGrafo(&t, caminho);


    t.plotarGrafo();
    t.caminharEmProfundidade();

    cout << endl << "Numero de nos: " << t.getNumeroDeNos() << endl;

    cout << endl << "Numero de arestas: " << t.getNumeroDeArestas() << endl;

    t.componentesFortementeConexas();

    return 0;
}
