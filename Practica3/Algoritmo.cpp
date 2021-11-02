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
	
	//destados=1;//hay estados sin marcar
	do{
		if(candidatos.empty()==true){//si el vector candidato ESTA vacio entonces hay que agregar el candidato inicial
			EstadoN T;
			T.marcarDestado();
			T.ingresarNucleo(0);	//Estado inicial
			
			Estado auxiliar = afn.obtenerT_Estado(0,nSimbolos-1);	//Se obtienen todas las transiciones epsilon del estado 0
			
			for(int i=0;i<auxiliar.obtenerTamanio();i++){ //se recorren los estados que se pasa en esa transicion epsilon
				int auxEstado = auxiliar.obtenerTransicion(i);
				T.agregarTransicion(auxEstado);
				T = cerradura_E(T,afn,auxEstado,nSimbolos);// Estado inicial | AFN | estado epsilon 
			}
			
			T.desmarcarDestado();
			candidatos.push_back(T);
			
			//se evalua a donde se llega con los n simbolos en el estado nuevo A o inicial
			
			for(int i=0;i<nSimbolos-1;i++){//se omite el simbolo epsilon
				EstadoN nuevoC;
				nuevoC = mover(afn,T,nuevoC,i);//Se obtiene el nucleo
				nuevoC.marcarDestado();
				candidatos.push_back(nuevoC);
			}
			
			destado();
		}
		else{						 //El vector candidato NO esta vacio
			EstadoN T;
			int indiceCandidato;	//variable que guardara el indice en el vector de candidatos para despues poder desmarcarlo
			
			for(int i=0;i<candidatos.size();i++){ //se recorren los candidatos hasta encontrar el siguiente destado marcado
				EstadoN auxiliar = candidatos[i];
				
				if(auxiliar.obtenerDestado()!=0){
					T = candidatos[i];
					indiceCandidato = i;
					break;
				}else{
					continue;
				}
			}
			
			for(int i=0;i<T.nucleoTamanio();i++){//For para recorrer nucleo
				int estado = T.obtenerNucleo(i);
				Estado auxiliar = afn.obtenerT_Estado(estado,nSimbolos-1);	//Se obtienen todas las transiciones epsilon del estado n
				
				if(auxiliar.estaVacia()!=true){//Se verifica que en ese indice de nucleo si existan transiciones epsilon
				
					for(int j=0;j<auxiliar.obtenerTamanio();j++){ //se recorren los estados que se pasa en esa transicion epsilon
						int auxEstado = auxiliar.obtenerTransicion(j);
						T.agregarTransicion(auxEstado);
						T = cerradura_E(T,afn,auxEstado,nSimbolos);// Estado inicial | AFN | estado epsilon 
					}	
				}else{//El estado no tiene transiciones epsilon, no se hace nada
					continue;
				}
			}//fin de for para recorrer nucleo
			
			T.desmarcarDestado();
			candidatos[indiceCandidato]=T;
			
			/*
			
			
			
			
			
			candidatos.push_back(T);
			
			//se evalua a donde se llega con los n simbolos en el estado nuevo A o inicial
			EstadoN nuevoC;
			for(int i=0;i<nSimbolos-2;i++){//se omite el simbolo epsilon
				nuevoC = mover(afn,T,nuevoC,i);
			}
			nuevoC.marcarDestado();
			candidatos.push_back(nuevoC);
			*/
			
			destado();					
		}
	}while(destados!=0);//end do - while

	cout<<"Destados: "<<destados<<endl;
	
	for(int i=0;i<candidatos.size();i++){//--------------IMPRESION DE LOS CANDIDATOS
		cout<< "Estado "<<i<<"N:{";
		EstadoN aux = candidatos[i];
		aux.mostrarNucleo();
		cout<<"| ";
		aux.imprimirDatos();
		cout<<"}"<<endl;
	}
}

EstadoN Algoritmo::mover(AFN afx,EstadoN T, EstadoN nuevoC, int iSimbolo){
	//NOTA: agragar bloque para un recorrido total para x simbolo
	int nucleo = -1;
	
	for(int i=0;i<T.obtenerTamanio();i++){
		int auxEstado = T.obtenerTransicion(i); //Estados del candidato inicial
		Estado auxiliar = afx.obtenerT_Estado(auxEstado,iSimbolo);
		
		if(auxiliar.estaVacia()!=true){
			nuevoC.ingresarNucleo(auxiliar.obtenerTransicion(0));
		}else{
			continue;
		}
	}
	
	return nuevoC;
}
EstadoN Algoritmo::cerradura_E(EstadoN T, AFN afn, int auxEstado,int nSimbolos){
	Estado eAuxiliar = afn.obtenerT_Estado(auxEstado,nSimbolos-1); //se optienen las transiciones epsilon del estado que se mando
	
	if(eAuxiliar.estaVacia()!=true){//Verifica que el estado obtenido no este vacio
		for(int i=0;i<eAuxiliar.obtenerTamanio();i++){
			int auxEstado = eAuxiliar.obtenerTransicion(i);
			T.agregarTransicion(auxEstado);
			T = cerradura_E(T,afn,auxEstado,nSimbolos);// Estado inicial | AFN | estado epsilon | Simbolos
		}
		return T;	
	}else{//Si esta vacio entonces se retorna el mismo estado nuevo
		return T;	
	}
}
void Algoritmo::destado(){//comprueba si quedan estado sin marcar
	for(int i=0;i<candidatos.size();i++){
		EstadoN aux = candidatos[i];
		destados = aux.obtenerDestado();
	}
}




