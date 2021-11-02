#include <iostream> 
#include <vector> 
#include "EstadoN.hpp"
#include "Estado.hpp"

void EstadoN::ingresarNucleo(int estado){
	nucleo.push_back(estado);
}
void EstadoN::mostrarNucleo(){
	for(int i=0;i<nucleo.size();i++)
		cout<<" "<<nucleo[i];	
}
void EstadoN::marcarDestado(){
	destado=1;
}
void EstadoN::desmarcarDestado(){
	destado=0;
}
int EstadoN::obtenerDestado(){
	return destado;
}
int EstadoN::obtenerNucleo(int i){
	return nucleo[i];
}
int EstadoN::nucleoTamanio(){
	return nucleo.size();
}

