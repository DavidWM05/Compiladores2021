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
		vector<string> S;				//Vector de Estados
		vector<string> E;				//Vector de Simbolos
		string S0;						//Estado inicial
		vector<string> F;				//Vector de Estados Finales
		int Scount,Ecount,Fcount; 		//Tamaño de vectores S, E y F
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
		void imprimirTupla();
};
