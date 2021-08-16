/******************************************************************************

Peralta Gonzalez Luis David
Compiladores

*******************************************************************************/

#include <iostream>
#include <vector>
#define MAX 100

using namespace std;

class AFN{
    //Atributos de la clase AFN
        vector<int> Q;          //Estados
        vector<char> Alfabeto;  //Alfabeto
        int q0;                 // Estado inicial
        vector<int>qf;          // Estados final
        int Transiciones[MAX][MAX]; //Transiciones

    //Funciones
    public:
        void iniciarAutomata(){
            cout << "Iniciando automata AFN" << endl;
        }
    };

int main()
{

    AFN obj;
    obj.iniciarAutomata();

    return 0;
}
