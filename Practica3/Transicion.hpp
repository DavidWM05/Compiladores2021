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
		int obtenerTransicion(int i);
		int obtenerTamanio();
};