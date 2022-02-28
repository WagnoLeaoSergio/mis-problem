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

bool leGrafoDeArquivo(Grafo* g, char* argv[])
{
    char* caminho = argv[1];
    std::ifstream file;
    file.open(caminho, std::ifstream::in);

    if(file.is_open())
    {
        bool ponderado = argv[3][0] - 48;
        if(ponderado)
        {
            int id1;
            int id2;
            float peso;
            int numNos;
            file >> numNos;
            int i = 0;
            while(true)
            {
                file >> id1 >> id2 >> peso;
                //cout << "id1: " << id1 << " id2: " << id2 << endl;
                if(file.eof())
                    break;
                g->inserir(id1);
                g->inserir(id2);
                g->conectar(id1, id2, peso);
                //cout << "linha: " << i << endl;
                i++;
            }
            file.close();
            return true;
        }
        else
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
                    g->conectar(id1, id2, 0);
                    //cout << "linha: " << i << endl;
                    i++;
                }
                file.close();
                return true;
            }
    }
    else
    {
        cout << "Caminho de arquivo invalido." << endl;
        return false;
    }
}

bool imprimeSolucaoMISEmArquivo(vector <int> sol, char* argv[])
{
    char* caminho = argv[2];
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
        return true;
    }
    return false;
}

void menu(Grafo* g)
{
    int opcao;
    cout << "[1] Caminhamento em largura" << endl;
    cout << "[2] Caminhamento em profundidade" << endl;
    cout << "[3] Componentes conexas" << endl;
    cout << "[4] Componentes fortemente conexas (para grafo orientado)" << endl;
    cout << "[5] Ordenacao topologica (para grafo orientado" << endl;
    cout << "[6] Dijkstra" << endl;
    cout << "[7] Floyd" << endl;
    cout << "[8] Prim" << endl;
    cout << "[9] Kruskal" << endl << endl;
    cout << "[10] Algoritmo guloso para o subconjunto independente maximo" << endl;
    cout << "[11] Algoritmo guloso randomizado para o subconjunto independente maximo" << endl;    cout << "[12] Algoritmo guloso randomizado reativo para o subconjunto independente maximo" << endl;    cin >> opcao;

    switch(opcao)
    {
        case 1: g->caminhamentoLargura();
                break;
        case 2: g->caminhamentoProf();
                break;
        case 3: g->componentesConexas();
                break;
        case 4: g->componentesFortementeConexas();
                break;
        case 5: g->ordenacoesTopologicas();
                break;
        case 6: int id;
                cout << "Digite o vertice inicial: " << endl;
                cin >> id;
                g->dijkstra(id);
                break;
        case 7: g->floyd();
                break;
        case 8: g->prim();
                break;
        case 9: g->kruskal();
                break;
        case 10: g->subconjuntoIndependenteMaxG();
                break;
        case 11:
            {
                vector <int> sol;
                sol = g->subconjuntoIndependenteMaxGRR();
                //imprimeSolucaoMISEmArquivo(sol, argv);
                break;
            }
        case 12: g->subconjuntoIndependenteMaxGRR();
                break;

    }
}

int main(int agrc, char* argv[])
{
    //string caminho = "C:\\Users\\davim\\OneDrive\\Documentos\\Projetos\\teste0.txt";
    bool ponderado = argv[3][0] - 48;
    bool direcionado = argv[4][0] - 48;
    Grafo g(ponderado, direcionado);
    if(leGrafoDeArquivo(&g, argv))
    {
        vector <int> sol;
        sol = g.subconjuntoIndependenteMaxGRR();
        imprimeSolucaoMISEmArquivo(sol, argv);
    }

    return 0;
}

