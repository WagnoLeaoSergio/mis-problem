/*
#include <iostream>
#include "Grafo.h"

using namespace std;

int main()
{
    Grafo t(0);
/*
    t.inserir(3);
    t.inserir(4);
    t.inserir(7);
    t.inserir(8);
    t.inserir(10);
    t.inserir(11);
    t.inserir(2);
    t.inserir(5);
*/

    //for(int i = 0; i < 1000; i++)
      //  t.inserir(i);


/*
    t.conectar(1, 2);
    t.conectar(2, 3);
    t.conectar(3, 4);
    t.conectar(4, 5);
    t.conectar(5, 6);
    t.conectar(6, 7);
    t.conectar(7, 8);
    t.conectar(7, 9);
    t.conectar(9, 10);
    t.conectar(8, 11);
    t.conectar(8, 12);
    t.conectar(12, 13);
    t.conectar(13, 14);
    t.conectar(14, 15);
    t.conectar(19, 26);
*/
//TESTE CONEXO 3
    //TESTE GULOSO 1
/*
    t.conectar(2, 5);
    t.conectar(2, 3);
    t.conectar(5, 4);
    t.conectar(3, 7);
    t.conectar(3, 8);
    t.conectar(11, 10);
    t.conectar(2, 5);
    t.conectar(2, 2);

*/
    //t.conectar(7, 4);
    //t.conectar(10, 1);

    //TESTE 2
/*
    t.conectar(2, 5);
    t.conectar(2, 3);
    t.conectar(2, 4);
    t.conectar(2, 7);
    t.conectar(2, 8);
    t.conectar(2, 11);
*/
    /*
    t.inserir(6);
    */
/*
    t.conectar(1, 3);
    t.conectar(2, 5);
    t.conectar(4, 2);
    t.conectar(4, 6);*/
/*
    t.conectar(1, 2);
    t.conectar(2, 3);
    t.conectar(3, 1);
    t.conectar(3, 4);
    t.conectar(1, 3);
    t.conectar(4, 5);
*/
/*
    t.conectar(1, 2);
    t.conectar(2, 1);
    //t.conectar(1, 3);

    t.conectar(3, 4);
    t.conectar(4, 3);

    t.conectar(10, 11);*/
//Teste fortemente conexo
/*
    t.conectar(1, 3);
    t.conectar(3, 2);
    t.conectar(2, 1);
    t.conectar(3, 5);
    t.conectar(5, 6);
    t.conectar(6, 4);
    t.conectar(4, 2);
    t.conectar(6, 7);
*/
/*
    t.conectar(1, 3);
    t.conectar(3, 5);
    t.conectar(5, 1);
    t.conectar(3, 2);
    t.conectar(2, 6);
    t.conectar(6, 4);
    t.conectar(4, 5);
    t.conectar(6, 7);
*/

/*
    t.conectar(1, 3);
    t.conectar(1, 2);
    t.conectar(2, 3);
    t.conectar(2, 4);
    t.conectar(5, 4);
    t.conectar(5, 6);
    t.conectar(6, 4);
    t.conectar(6, 5);
    t.conectar(3, 7);
    t.conectar(7, 2);
    */
    //t.excluirNo(2);
   // cout << "Caminhamento em largura: " << endl;
   // t.caminhamentoLargura();
   // cout << "Caminhamento em profundidade: " << endl;
   // t.caminhamentoProf();
   // cout << "Impressao do grafo:" << endl;
   // t.printGrafo();
   // cout << "xxxxxxxxxxxxxxxxxxx" << endl;
   // cout << "Componentes conexas: " << t.componentesConexas() << endl;
    //cout << "Componentes fortemente conexas: " << t.componentesFortementeConexas() << endl; ///PROBLEMA NA FUNCAO, RESTANTE ESTA FUNCIONANDO
   // t.ordenacoesTopologicas();

    //t.subconjuntoIndependenteMax();
    //return 0;
//}

#include <iostream>
#include "Grafo.h"
#include <fstream>
#include <sstream>

using namespace std;

bool leArquivo(Grafo* g, char* caminho)
{
    std::ifstream file;
    file.open(caminho, std::ifstream::in);

    if(file.is_open())
    {
        int id1;
        int id2;
        int numNos;
        file >> numNos;
        int i = 0;
        while(true)
        {
            file >> id1 >> id2;
            //cout << "id1: " << id1 << " id2: " << id2 << endl;
            if(file.eof())
                break;
            g->inserir(id1);
            g->inserir(id2);
            g->conectar(id1, id2);
            //cout << "linha: " << i << endl;
            i++;
        }
        file.close();
        cout << "hello there" << endl;
        return true;
    }
    else
    {
        cout << "Caminho de arquivo invalido." << endl;
        return false;
    }
}

void imprimeArquivo(vector <int> sol, char* caminho)
{
    std::ofstream file;
    file.open(caminho, std::ofstream::out);
    if(file.is_open())
    {
        file << "Subconjunto independente maximo obtido pelo algoritmo guloso randomizado: " << endl;
        file << "Numero de nos na solucao: " << sol.size() << endl;
        for(int i = 0; i < (int)sol.size(); i++)
        {
            file << sol[i] <<endl;
        }
        file.close();
    }
}

void menu()
{
    cout << "[1] Exibir caminhamento em largura" << endl;
    cout << "[2] Exibir caminhamento em profundidade" << endl;
    cout << "[3] Exibir componentes conexas" << endl;
    cout << "[4] Exibir componentes fortemente conexas" << endl;
    cout << "[5] Exibir ordenacao topologica" << endl;

}

int main(int agrc, char* argv[])
{
    //string caminho = "C:\\Users\\davim\\OneDrive\\Documentos\\Projetos\\teste0.txt";
    Grafo g(0);
    if(leArquivo(&g, argv[1]))
    {
        vector <int> sol;
        sol = g.subconjuntoIndependenteMax();
        imprimeArquivo(sol, argv[2]);
    }

    return 0;
}

