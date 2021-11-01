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
		void marcarDestado();
		void desmarcarDestado();
};
