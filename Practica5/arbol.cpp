#include <iostream>
#include<string> 
#include <vector> 
#include <sstream>
#include <cstring>

class AFD{
	private:
		vector<string> alfabeto;
		vector<string> estados;
		string eInicial;
		vector<string> eFinales;
		vector< vector<string> > transiciones;
	
	public:
		void setAlfabeto(string aux){
		}
		string getAlfabeto(int index){
		}
		void setEstados(string aux){
		}
		string getEstados(){
		}
		void setEinicial(string aux){
		}
		string getEinicial(){
		}
		void setEfinales(string aux){
		}
		string getEfinales(int index){
		}
		void setTransicion(string aux){
		}
		string getTransicion(int i,int j){
		}
};
class ExpresionRegular{
	private:
		string expresion;
	
	public:
		void setExpresion(string aux){
		}
		string getExpresion(){
		}
};
class Arbol{
	private:
		AFD afd;
		Expresion expRegular;
    vector <string> arbol;
    string posicionS;
    vector< vector<string> > tablaSiguientes;
	
	public:
		void iniciarAlgoritmo(){
		}
		void construirArbol(){
		}
    void posicionSimbolos(){
    }
    
    
};

int main(){
	
	Arbol arbol = Arbol();
	algoritmo.iniciarAlgoritmo()
	
	system("PAUSE");
	return 0;
}
