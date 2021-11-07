#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sstream>
#include "AFN.hpp"
#include "Transicion.hpp"
#include "EstadoCandidato.hpp"

using namespace std;

void AFN::ingresarTupla(){
	//SOLICITUD DE DATOS
	cout<<"Numero de estados: ";
	cin>>Scount;
	cout<<"Numero de simbolos: ";
	cin>>Ecount;
	cout<<"Numero de estados finales: ";
	cin>>Fcount;
	cin.ignore();						//Se limpia el buffer

	string estados[Scount];			//Vector de estados
	string simbolos[Ecount];			//Vector de simbolos
	string estadoI,estadosF[Fcount];	//Estado inicial | Vector de estados finales

	//Estados
	for(int i=0;i<Scount;i++){		//Se guardan los estados
		string aux;
		stringstream ss;				//clase auxiliar para convertir int a string
	 	ss<<i;
		ss>>aux;

		S.push_back(aux);
	}
	//SIMBOLOS
	cout<<"Ingresa los simbolos"<<endl;	//Se solicita al usuario ingresar los simbolos 
	for(int i=0;i<Ecount;i++){
		string aux;
		cout<<"["<<i<<"]: ";
		getline(cin,aux);

		E.push_back(aux);
	}
	//ESTADO INCIAL
	S0 = S[0]; 		
	//ESTADOS FINALES
	cout<<"\nIngresa los estados finales"<<endl;
	for(int i=0;i<Fcount;i++){		//Se solicita al usuario que ingrese los estados finales
		string aux;
		cout<<"F["<<i<<"]: ";
		getline(cin,aux);

		F.push_back(aux);
	}
	//TABLA DE TANSICIONES
	for(int i=0;i<Scount;i++){
		cout<<" Estado "<<S[i]<<": "<<endl; 
		
		for(int j=0;j<Ecount;j++){//Transiciones de estados con los simbolos
			int control=1;	
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
							tablaTransiciones[i][j].agregarTransicion(aux);			
					break;
					default: cout<<"Opcion no valida, solo se puede ingresar 0=no | 1=si ";
				}//end switch
			}//end while
		}
	}
}
void AFN::imprimirTabla(){
	for(int i=0;i<Scount;i++){
		for(int j=0;j<Ecount;j++){
			tablaTransiciones[i][j].imprimirElementos();
		}
		cout<<endl;
	}
}
Transicion AFN::obtenerIndiceTabla(int i,int j){
	return tablaTransiciones[i][j]; 
}

int AFN::totalEstados(){
	return S.size();
}
string AFN::obtenerIndiceEstado(int i){
	return S[i];
}

int AFN::totalSimbolos(){
	return E.size();
}
string AFN::indiceSimbolos(int i){
	return E[i];
}

int AFN::totalFinales(){
	return F.size();
}
string AFN::indiceFinales(int i){
	return F[i];
}

string	AFN::obtenerInicial(){
	return S0;
}
