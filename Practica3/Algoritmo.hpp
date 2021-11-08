#pragma once
#include <iostream> 
#include <vector> 
#include <string>
#include "EstadoCandidato.hpp"
#include "Transicion.hpp"
#include "Algoritmo.hpp"
#include "AFN.hpp"

using namespace std;

class Algoritmo{
	private:
		vector<EstadoCandidato> candidatos;
		bool destadosRestantes;
	
	public:
		void iniciarAlgoritmo();
		EstadoCandidato mover(AFN afx,EstadoCandidato T, EstadoCandidato nuevoC, int indiceSimbolo);
		EstadoCandidato cerradura_E(EstadoCandidato T, AFN afn, int auxEstado, int nSimbolos);
		void actualizarDestados();
		bool compararNucleos(EstadoCandidato e1, EstadoCandidato e2);
		void limpiar_pantalla();
};
