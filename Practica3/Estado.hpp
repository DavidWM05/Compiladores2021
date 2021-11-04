#pragma once
#include <iostream> 
#include <vector> 

using namespace std;

class Estado{
	private:
		vector<int> transicion;
	public:
		void agregarTransicion(int estado);
		bool estaVacia();
		void imprimirDatos();
		int obtenerTransicion(int i); //se debe mandar Ecount-1 (tamaño de simbolos - 1)
		int obtenerTamanio();
};
