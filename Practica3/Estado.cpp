#include <iostream> 
#include <vector> 
#include "Estado.hpp"

using namespace std;

void Estado::agregarTransicion(int estado){
	transicion.push_back(estado);
}
bool Estado::estaVacia(){
	return transicion.empty();
}
void Estado::imprimirDatos(){
	for(int i=0;i<transicion.size();i++){
		cout<< transicion[i] <<" ";
	}
}
int Estado::obtenerTamanio(){
	transicion.size();
}
int Estado::obtenerTransicion(int i){
	return transicion[i];
}

