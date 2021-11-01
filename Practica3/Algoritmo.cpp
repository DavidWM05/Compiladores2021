#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>
#include <cstring>
#include "EstadoN.hpp"
#include "Estado.hpp"
#include "Algoritmo.hpp"
#include "AFN.hpp"

using namespace std;

void Algoritmo::iniciarAlgoritmo(){
	//Variables
	int nEstados, nSimbolos,nFinales; //numero de estados | numero de simbolos
	
	//Entrada de datos
	cout<<"Numero de estados: ";
	cin>>nEstados;
	cout<<"Numero de simbolos: ";
	cin>>nSimbolos;
	cout<<"Numero de estados finales: ";
	cin>>nFinales;
	cin.ignore();						//Se limpia el buffer
	
	string estados[nEstados];			//vector de estados
	string simbolos[nSimbolos];			//vector de simbolos
	string estadoI,estadosF[nFinales];	//estado inicial | vector de estados finales
	
	for(int i=0;i<nEstados;i++){		//Se guardan los estados
		stringstream ss;				//clase auxiliar para convertir int a string
	 	ss<<i;
		ss>>estados[i];
	}
	
	estadoI = estados[0]; 				//se guarda el estado inicial
	
	cout<<"\nIngresa los estados finales"<<endl;
	for(int i=0;i<nFinales;i++){		//Se solicita al usuario que ingrese los estados finales
		cout<<"F["<<i<<"]: ";
		getline(cin,estadosF[i]);
	}
	
	cout<<"Ingresa los simbolos"<<endl;	//Se solicita al usuario ingresar los simbolos 
	for(int i=0;i<nSimbolos;i++){
		cout<<"["<<i<<"]: ";
		getline(cin,simbolos[i]);
	}		
	cout<<endl;
	
	
	AFN afn = AFN(estados,simbolos,estadoI,estadosF,nEstados,nSimbolos,nFinales);
	afn.solicitarTransiciones();
	//-------------------------------------------------------
	
	destados=1;//hay estados sin marcar
	//while(destados!=0){
		if(candidatos.empty()==true){//si el vector candidato esta vacio entonces hay que agregar el candidato inicial
			EstadoN T;
			T.marcarDestado();
			T.ingresarNucleo(0);
			
			Estado auxiliar = afn.obtenerT_Estado(0,nSimbolos-1);	
			
			for(int i=0;i<auxiliar.obtenerTamanio();i++)
				T.agregarTransicion(auxiliar.obtenerTransicion(i));
			
			cerradura_E(T);
			
			T.desmarcarDestado();
			candidatos.push_back(T);
			
			EstadoN nuevoC;
			for(int i=0;i<nSimbolos-2;i++){//se omite el simbolo epsilon
				mover(afn,T,nuevoC,i);
			}
			
		}else{
			
		}
	//}//end while
	
		for(int i=0;i<candidatos.size();i++){
			cout<< "Estado "<<i<<"N:{";
			EstadoN aux = candidatos[i];
			aux.mostrarNucleo();
			cout<<"| ";
			aux.imprimirDatos();
			cout<<"}"<<endl;
		}
}

void Algoritmo::mover(AFN afx,EstadoN T, EstadoN nuevoC, int indiceSimbolo){
	
	for(int i=0;i<T.obtenerTamanio();i++){
		int estado = T.obtenerTransicion(i); //se obtendran los estados por los que pasa el candidato
		Estado auxiliar = afx.obtenerT_Estado(estado,indiceSimbolo);
		if(auxiliar.estaVacia()==true){
			continue;
		}else{ //si existe alguna transicion
			int nuevoNucleo = auxiliar.obtenerTransicion(0);
			nuevoC.ingresarNucleo(nuevoNucleo);
		}
	}
	candidatos.push_back(nuevoC);
}
void Algoritmo::cerradora_E(EstadoN T){
	
		for(int i=0;i<T.obtenerTamanio();i++){
		int estado = T.obtenerTransicion(i); //se obtendran los estados por los que pasa el candidato
		Estado auxiliar = afx.obtenerT_Estado(estado,indiceSimbolo);
		if(auxiliar.estaVacia()==true){
			continue;
		}else{ //si existe alguna transicion
			int nuevoNucleo = auxiliar.obtenerTransicion(0);
			nuevoC.ingresarNucleo(nuevoNucleo);
		}
	}
	candidatos.push_back(nuevoC);
	
}
int Algoritmo::destado(){//comprueba si quedan estado sin marcar
	return 1;
}

