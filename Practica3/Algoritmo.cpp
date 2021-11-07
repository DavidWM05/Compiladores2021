#include <iostream>
#include <string> 
#include <vector> 
#include <sstream>
#include <cstring>
#include "EstadoCandidato.hpp"
#include "Transicion.hpp"
#include "Algoritmo.hpp"
#include "AFN.hpp"

using namespace std;

void Algoritmo::iniciarAlgoritmo(){
	
	AFN afn; //se crea el objeto AFN mandandole los datos ingresados
	afn.ingresarTupla();		//Se solicita al usuario que ingrese la tupla
	
	int nEstados = afn.totalEstados();
	int nSimbolos = afn.totalSimbolos();
	int nFinales = afn.totalFinales();
	
	//---------------------------------| IMPLEMENTACION DE ALGORITMO TOMADO DEL AHO |--------------------------------------
	
	vector<string> producciones; //Vector que guardara las producciones generadas
	
	do{
		if(candidatos.empty()==true){//Si el vector candidato ESTA vacio entonces hay que agregar el candidato inicial
			EstadoCandidato T;				//Objeto Estado Nuevo 
			T.marcarDestado();		//Se marca como destado
			T.ingresarNucleo(0);	//El nucleo del primer candidato es el estado inicial
			
			Transicion auxiliar = afn.obtenerIndiceTabla(0,nSimbolos-1);	//Se obtienen todas las transiciones epsilon del estado 0
			
			for(int i=0;i<auxiliar.obtenerTamanio();i++){ //se recorren los estados que se pasa en esa transicion epsilon
				int auxEstado = auxiliar.obtenerTransicion(i);
				T.agregarEstado(auxEstado);
				T = cerradura_E(T,afn,auxEstado,nSimbolos);// Estado inicial | AFN | estado epsilon 
			}
			
			T.desmarcarDestado();
			candidatos.push_back(T);
			
			//se evalua a donde se llega con los n simbolos en el estado nuevo A o inicial
			
			for(int i=0;i<nSimbolos-1;i++){//se omite el simbolo epsilon
				EstadoCandidato nuevoC;
				nuevoC = mover(afn,T,nuevoC,i);//Se obtiene el nucleo
			
			
				int nucleoExistente=-1;
				
				for(int j=0;j<candidatos.size();j++){
					EstadoCandidato auxiliar = candidatos[j];	
					
					if(compararNucleos(auxiliar,nuevoC)!=true){
						continue;
					}else{
						nucleoExistente=j;
						break;
					}
				}		
				
				if(nucleoExistente==-1){
					string aux, produccion = " ";
					stringstream ss;				//clase auxiliar para convertir int a string
										
					nuevoC.marcarDestado();
					candidatos.push_back(nuevoC);
					
					ss<<(candidatos.size()-1);
					ss>>aux;
					
					produccion += "0N -> "+afn.indiceSimbolos(i)+" -> "+aux+"N";//-----------------------------
					producciones.push_back(produccion);
				}else{//El nucleo es igual a uno ya existente
					string aux,aux2, produccion = " ";
					stringstream ss,ss2;				//clase auxiliar para convertir int a string
														
					ss<<nucleoExistente;
					ss>>aux;
					
					produccion += "0N -> "+afn.indiceSimbolos(i)+" -> "+aux+"N";//---------------------------
					producciones.push_back(produccion);					
				}
				
			}
			
			destado();	//se actualiza destados
		}
		else{						 //El vector candidato NO esta vacio
			EstadoCandidato T;
			int indiceCandidato;	//variable que guardara el indice en el vector de candidatos para despues poder desmarcarlo
			
			for(int i=0;i<candidatos.size();i++){ //se recorren los candidatos hasta encontrar el siguiente destado marcado
				EstadoCandidato auxiliar = candidatos[i];
				
				if(auxiliar.obtenerDestado()!=0){
					T = candidatos[i];
					indiceCandidato = i;
					break;
				}else{
					continue;
				}
			}
			
			for(int i=0;i<T.nucleoTamanio();i++){//For para recorrer nucleo
				int estado = T.obtenerIndiceNucleo(i);
				Transicion auxiliar = afn.obtenerIndiceTabla(estado,nSimbolos-1);	//Se obtienen todas las transiciones epsilon del estado n
				
				if(auxiliar.estaVacia()!=true){//Se verifica que en ese indice de nucleo si existan transiciones epsilon
				
					for(int j=0;j<auxiliar.obtenerTamanio();j++){ //se recorren los estados que se pasa en esa transicion epsilon
						int auxEstado = auxiliar.obtenerTransicion(j);
						T.agregarEstado(auxEstado);
						T = cerradura_E(T,afn,auxEstado,nSimbolos);// Estado inicial | AFN | estado epsilon 
					}	
				}else{//El estado no tiene transiciones epsilon, no se hace nada
					continue;
				}
			}//fin de for para recorrer nucleo
			
			T.desmarcarDestado();
			candidatos[indiceCandidato]=T;
			
			//NUEVOS CANDIDATOS
			
			for(int i=0;i<nSimbolos-1;i++){//se omite el simbolo epsilon
				EstadoCandidato nuevoC;
				nuevoC = mover(afn,T,nuevoC,i);
				int nucleoExistente=-1;//-1 no existe | >0 si existe
				
				for(int j=0;j<candidatos.size();j++){//Se compara el nucleo del candidato nuevo con los que ya estan agregados
					EstadoCandidato auxiliar = candidatos[j];
					if(compararNucleos(auxiliar,nuevoC)!=true){
						continue;
					}else{
						nucleoExistente=j;//se guarda el candidato al que es igual
						break;
					}
				}
				
				//Condicion sobre nucleo
				if(nucleoExistente==-1){//El nucleo no existe
					string aux,aux2, produccion = " ";
					stringstream ss,ss2;				//clase auxiliar para convertir int a string
					
					
					nuevoC.marcarDestado();
					candidatos.push_back(nuevoC);
					
														
					ss<<(candidatos.size()-1);
					ss>>aux;
					
					ss2<<indiceCandidato;
					ss2>>aux2;
					
					produccion += aux2+"N -> "+afn.indiceSimbolos(i)+" -> "+aux+"N";//----------------------------------------------
					producciones.push_back(produccion);
					
				}else{//El nucleo es igual a uno ya existente
					string aux,aux2, produccion = " ";
					stringstream ss,ss2;				//clase auxiliar para convertir int a string
														
					ss<<nucleoExistente;
					ss>>aux;
					
					ss2<<indiceCandidato;
					ss2>>aux2;
					
					produccion += aux2+"N -> "+afn.indiceSimbolos(i)+" -> "+aux+"N";//---------------------------------------------
					producciones.push_back(produccion);					
				}
			}	
			destado();	//Se actualiza destados
		}
	}while(destadosRestantes!=0);//end do - while

	cout<<"Destados: "<<destadosRestantes<<endl;
	
	//--------------IMPRESION DE LOS ESTADOS CANDIDATOS
	cout<<"\tESTADOS NUEVOS\n"<<endl;
	for(int i=0;i<candidatos.size();i++){
		cout<< "Estado "<<i<<"N:{";
		EstadoCandidato aux = candidatos[i];
		aux.mostrarNucleo();
		cout<<"| ";
		aux.imprimirTabla();
		cout<<"}"<<endl;
	}
	
	//--------------IMPRESION DE LAS PRODUCCIONES
	cout<<"\n\tTRANSICIONES\n"<<endl;
	for(int i=0;i<producciones.size();i++){
		cout<< producciones[i] <<endl;
	}
}
EstadoCandidato Algoritmo::mover(AFN afx,EstadoCandidato T, EstadoCandidato nuevoC, int iSimbolo){
	//NOTA: agragar bloque para un recorrido total para x simbolo	
	int vectorT=T.obtenerTamanioEstados();
	int nucleoT=T.nucleoTamanio();
	int n = vectorT+nucleoT;
	
	for(int i=0,j=0;i<n;i++){
		
		if(i<vectorT){//se recorren primero los que no son nucleos
			int auxEstado = T.obtenerEstado(i); //Estados
			Transicion auxiliar = afx.obtenerIndiceTabla(auxEstado,iSimbolo);
			
			if(auxiliar.estaVacia()!=true){
				nuevoC.ingresarNucleo(auxiliar.obtenerTransicion(0));
			}else{
				continue;
			}
		}else{//se recorre el nucleo
			int auxEstado = T.obtenerIndiceNucleo(j);
			Transicion auxiliar = afx.obtenerIndiceTabla(auxEstado,iSimbolo);
			j++;
			
			if(auxiliar.estaVacia()!=true){
				nuevoC.ingresarNucleo(auxiliar.obtenerTransicion(0));
			}else{
				continue;
			}
		}
		
		
	}
	
	return nuevoC;
}
EstadoCandidato Algoritmo::cerradura_E(EstadoCandidato T, AFN afn, int auxEstado,int nSimbolos){
	Transicion eAuxiliar = afn.obtenerIndiceTabla(auxEstado,nSimbolos-1); //se optienen las transiciones epsilon del estado que se mando
	
	if(eAuxiliar.estaVacia()!=true){//Verifica que el estado obtenido no este vacio
		for(int i=0;i<eAuxiliar.obtenerTamanio();i++){
			int auxEstado = eAuxiliar.obtenerTransicion(i);
			T.agregarEstado(auxEstado);
			T = cerradura_E(T,afn,auxEstado,nSimbolos);// Estado inicial | AFN | estado epsilon | Simbolos
		}
		return T;	
	}else{//Si esta vacio entonces se retorna el mismo estado nuevo
		return T;	
	}
}
void Algoritmo::destado(){//comprueba si quedan estado sin marcar
	for(int i=0;i<candidatos.size();i++){
		EstadoCandidato aux = candidatos[i];
		destadosRestantes = aux.obtenerDestado();
	}
}
bool Algoritmo::compararNucleos(EstadoCandidato e1, EstadoCandidato e2){
	vector<int> n1 = e1.obtenerNucleoVector();
	vector<int> n2 = e2.obtenerNucleoVector();
	
	if(n1==n2){
		return true;
	}else{
		return false;
	}
}