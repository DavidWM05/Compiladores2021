#include <string>
#include <iostream>
#include <stdio.h>
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

	string estados[Scount];				
	string simbolos[Ecount];			
	string estadoI,estadosF[Fcount];	

	//Estados
	for(int i=0;i<Scount;i++){		
		string aux;
		stringstream ss;			
	 	ss<<i;
		ss>>aux;

		S.push_back(aux);
	}
	//SIMBOLOS
	cout<<"Ingresa los simbolos"<<endl;
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
	for(int i=0;i<Fcount;i++){
		string aux;
		cout<<"F["<<i<<"]: ";
		getline(cin,aux);

		F.push_back(aux);
	}
	
	//TABLA DE TANSICIONES
	for(int i=0;i<Scount;i++){
		cout<<" Estado "<<S[i]<<": "<<endl; 
		for(int j=0;j<Ecount;j++){
			int control=1;	
			int aux;
			cout<<"  Simbolo "<<E[j]<<": "<<endl;
			
			while(control!=0){
				cout<<"   agregar transicion? si=1/0=no: ";
				cin>>control;
				switch(control){
					case 0:		continue;
					break;
					case 1:
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
void AFN::imprimirTupla(){
	cout<<"S: ";
	for(int i=0;i<Scount;i++){
		cout<<S[i];
		if(i+1!=Scount) cout<<",";
	}
	cout<<endl;
	
	cout<<"E: ";
	for(int i=0;i<Ecount;i++){
		cout<<E[i];
		if(i+1!=Ecount) cout<<",";
	}
	cout<<endl;
	
	cout<< "S0: " << S0 << endl;
	
	cout<<"F: ";
	for(int i=0;i<Fcount;i++){
		cout<<F[i];
		if(i+1!=Fcount) cout<<",";
	}
	cout<<endl;
	
	cout<<"T:\tS\\E";
	for(int i=0;i<Ecount;i++) 
		cout<< "\t" << E[i];
	cout<<endl;
	
	for(int i=0;i<Scount;i++){
		cout<< "\t" << i <<"\t";
		for(int j=0;j<Ecount;j++){
			if(tablaTransiciones[i][j].estaVacia()!=true){
				tablaTransiciones[i][j].imprimirElementos();
				cout<< "\t";
			}
			else
				cout<< "--\t";
		}
		cout<<endl;
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
