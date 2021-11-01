#pragma once
#include <iostream> 
#include <vector> 
#include <string>
#include "EstadoN.hpp"
#include "Estado.hpp"
#include "Algoritmo.hpp"
#include "AFN.hpp"

class Algoritmo{
	private:
		vector<EstadoN> candidatos;
		int destados;
	
	public:
		void iniciarAlgoritmo();
		void mover(AFN afx,EstadoN T, EstadoN nuevoC, int indiceSimbolo);
		void cerradora_E();		
		int destado();
};
