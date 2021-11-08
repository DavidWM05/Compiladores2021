#pragma once
#include <iostream> 
#include <vector>

using namespace std;

class EstadoCandidato{
	private:
		vector<int> nucleo;
		vector<int> estados;
		bool marcaDestado;
	public:
		void mostrarNucleo();
		void ingresarNucleo(int estado);
		int obtenerIndiceNucleo(int i);
		vector<int> obtenerNucleoVector();
		int nucleoTamanio();
		void marcarDestado();
		void desmarcarDestado();
		bool obtenerDestado();
		void agregarEstado(int estado);
		bool tablaVacia();
		void imprimirTabla();
		int obtenerEstado(int i); //se debe mandar Ecount-1 (tamaño de simbolos - 1)
		int obtenerTamanioEstados();
};
