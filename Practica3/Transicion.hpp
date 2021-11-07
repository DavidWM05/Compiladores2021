#pragma once
#include <iostream> 
#include <vector> 

using namespace std;

class Transicion{
	private:
		vector<int> transiciones;
	public:
		void agregarTransicion(int estado);
		bool estaVacia();
		void imprimirElementos();
		int obtenerTransicion(int i); //se debe mandar Ecount-1 (tamaño de simbolos - 1)
		int obtenerTamanio();
};