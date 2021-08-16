/******************************************************************************

Peralta Gonzalez Luis David
Compiladores

*******************************************************************************/

#include <iostream>
#include <vector>
#define MAX 100

using namespace std;

class AFD{
    //Atributos de la clase AFN
        vector<int> Q;          //Estados
        vector<char> Alfabeto;  //Alfabeto
        int q0;                 // Estado inicial
        int qf;          // Estado final
        int Transiciones[MAX][MAX]; //Transiciones

    //Funciones
    public:
        void iniciarAutomata(){
            cout << "Iniciando automata AFD" << endl;
        }
    };

int main(){    
    AFD obj;
    obj.iniciarAutomata();

    return 0;
}
