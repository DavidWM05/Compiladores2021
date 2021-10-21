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

class Minimizacion{
	private:
		AFD afd,afdmin;
		vector<string> eFinales;
		vector<string> eNoFinales;
		vector<string> nuevoGrupo;
	
	public:
		void iniciarAlgoritmo(){
		}
		void evaluarAgrupacion(string simbolo){
		}
};

int main(){
	
	Minimizacion algoritmo = Minimizacion();
	algoritmo.iniciarAlgoritmo()
	
	system("PAUSE");
	return 0;
}
