#pragma once
#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>
#include <cstring>
#include "Transicion.hpp"
#define	MAX 100

using namespace std;

class AFN{
	private:
		vector<string> S;				//estados
		vector<string> E;				//conjunto de simbolos
		string S0;						//estado inicial
		vector<string> F;				//conjunto de estados finales
		int Scount,Ecount,Fcount; 		//tamaño de S y E sin comas
		Transicion tablaTransiciones[MAX][MAX]; 	//Matriz de transiciones[nEstados][nSimbolos]
		
	public:
		void ingresarTupla();
		int totalEstados();
		string obtenerIndiceEstado(int i);
		int totalSimbolos();
		string indiceSimbolos(int i);		
		int totalFinales();
		string indiceFinales(int i);
		string	obtenerInicial();	
		Transicion obtenerIndiceTabla(int i,int j);
		void imprimirTabla();

};
