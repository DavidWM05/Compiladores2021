#pragma once
#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>
#include <cstring>
#include "EstadoN.hpp"
#include "Estado.hpp"
#define	MAX 100

using namespace std;

class AFN{
	private:
		vector<string> S;			//estados
		vector<string> E;			//conjunto de simbolos
		string S0;					//estado inicial
		vector<string> F;			//conjunto de estados finales
		int Scount,Ecount,Fcount; 	//tamaño de S y E sin comas
		Estado transiciones[MAX][MAX]; //Los tados [i][Ecount-1] son de las transiciones epsilon
		
	public:
		AFN(string _S[],string _E[],string _S0,string _F[],int nEstados,int nSimbolos,int nFinales);
		void solicitarTransiciones();
		void imprimirTransiciones();
		Estado obtenerT_Estado(int i,int j);
};
