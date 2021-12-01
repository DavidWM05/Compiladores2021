#include <iostream> 
#include <vector>
#include "EstadoCandidato.hpp"

void EstadoCandidato::mostrarNucleo(){
	for(int i=0;i<nucleo.size();i++)
		cout<<" "<<nucleo[i];	
}
void EstadoCandidato::ingresarNucleo(int estado){
	nucleo.push_back(estado);
}
int EstadoCandidato::obtenerIndiceNucleo(int i){
	return nucleo[i];
}
vector<int> EstadoCandidato::obtenerNucleoVector(){
	return nucleo;
}
int EstadoCandidato::nucleoTamanio(){
	return nucleo.size();
}
void EstadoCandidato::marcarDestado(){
	marcaDestado=true;
}
void EstadoCandidato::desmarcarDestado(){
	marcaDestado=false;
}
bool EstadoCandidato::obtenerDestado(){
	return marcaDestado;
}
void EstadoCandidato::agregarEstado(int estado){
	estados.push_back(estado);
}
bool EstadoCandidato::tablaVacia(){
	return estados.empty();
}
void EstadoCandidato::imprimirTabla(){
	for(int i=0;i<estados.size();i++){
		cout<< estados[i] <<" ";
	}
}
int EstadoCandidato::obtenerEstado(int i){
	return estados[i];
}
int EstadoCandidato::obtenerTamanioEstados(){
	return estados.size();
}
