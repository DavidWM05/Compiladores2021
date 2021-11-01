#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include "AFN.hpp"
#include "Estado.hpp"
#include "EstadoN.hpp"

using namespace std;

AFN::AFN(string _S[],string _E[],string _S0,string _F[],int nEstados,int nSimbolos,int nFinales){
	Scount = nEstados;
	Ecount = nSimbolos;
	Fcount = nFinales;
	S0=_S0;
	
	for(int i=0;i<Scount;i++)//Estados
		S.push_back(_S[i]);
	for(int i=0;i<Ecount;i++)//Simbolos
		E.push_back(_E[i]);
	for(int i=0;i<Fcount;i++)//Finales
		F.push_back(_F[i]);
}

void AFN::solicitarTransiciones(){
			     //Estados Simbolos
	//transiciones[Scount][Ecount];
	
	for(int i=0;i<Scount;i++){
		cout<<" Estado "<<S[i]<<": "<<endl; 
		
		for(int j=0;j<Ecount;j++){//Transiciones de estados con los simbolos
			int control=1;	//variable que controlara las transiciones
			int aux;
			cout<<"  Simbolo "<<E[j]<<": "<<endl;
			
			while(control!=0){
				cout<<"   agregar transicion? si=1/0=no: ";
				cin>>control;
				switch(control){
					case 0:		continue;
					break;
					case 1:	//se solicita al usuario que ingrese la transicion
							cin.ignore();			
							cout<< "    " <<E[j]<<" -> ";
							cin>>aux;
							transiciones[i][j].agregarTransicion(aux);			
					break;
					default: cout<<"Opcion no valida, solo se puede ingresar 0=no | 1=si ";
				}//end switch
			}//end while
		}
	}
}

void AFN::imprimirTransiciones(){
	for(int i=0;i<Scount;i++){
		for(int j=0;j<Ecount;j++){
			transiciones[i][j].imprimirDatos();
		}
		cout<<endl;
	}
}
Estado AFN::obtenerT_Estado(int i,int j){
	return transiciones[i][j]; 
}

/*
stringstream intValue(S0);
	int auxiliar;
	intValue >> auxiliar;
	
	EstadoN inicial;
	inicial.ingresarNucleo(auxiliar);
	
	auxiliar = transiciones[0][Ecount-1].obtenerTamanio(); //tramaño de vector epsilon para estado 0
	
	for(int i=0;i<auxiliar;i++){
		int epsilon = transiciones[0][Ecount-1].obtenerEpsilon(i);
		inicial.agregarTransicion(epsilon);
	}
		
	candidatos.push_back(inicial);
	
	EstadoN nuevo = candidatos[0];
	
	nuevo.mostrarNucleo();
	nuevo.imprimirDatos();



Imprimir Transicion	
	
*/
	//--------------------------------------

