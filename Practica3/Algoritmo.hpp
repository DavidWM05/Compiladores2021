#pragma once
#include <iostream> 
#include <vector> 
#include <string>
#include "EstadoN.hpp"
#include "Estado.hpp"
#include "Algoritmo.hpp"
#include "AFN.hpp"

using namespace std;

class Algoritmo{
	private:
		vector<EstadoN> candidatos;
		int destados;
	
	public:
		void iniciarAlgoritmo();
		EstadoN mover(AFN afx,EstadoN T, EstadoN nuevoC, int indiceSimbolo);
		EstadoN cerradura_E(EstadoN T, AFN afn, int auxEstado, int nSimbolos);
		void destado();
};
