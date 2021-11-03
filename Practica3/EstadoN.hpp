#pragma once
#include <iostream> 
#include <vector>
#include "Estado.hpp"

using namespace std;

class EstadoN : public Estado{
	private:
		vector<int> nucleo;
		int destado; //1 verdadero | 0 falso
	public:
		void mostrarNucleo();
		void ingresarNucleo(int estado);
		int obtenerNucleo(int i);
		vector<int> obtenerNucleoVector();
		int nucleoTamanio();
		void marcarDestado();
		void desmarcarDestado();
		int obtenerDestado();
		void ordenarNucleo();
};
