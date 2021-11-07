#include <iostream> 
#include <vector> 
#include "Transicion.hpp"

using namespace std;

void Transicion::agregarTransicion(int estado){
	transiciones.push_back(estado);
}
bool Transicion::estaVacia(){
	return transiciones.empty();
}
void Transicion::imprimirElementos(){
	for(int i=0;i<transiciones.size();i++){
		cout<< transiciones[i] <<" ";
	}
}
int Transicion::obtenerTransicion(int i){
	return transiciones[i];
}
int Transicion::obtenerTamanio(){
	return transiciones.size();
}
