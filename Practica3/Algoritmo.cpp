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
	//VARIABLES DE ENTRADA
	int nEstados, nSimbolos,nFinales; //Numero de estados | Numero de simbolos | Numero de simbolos finales
	
	//SOLICITUS DE DATOS
	cout<<"Numero de estados: ";
	cin>>nEstados;
	cout<<"Numero de simbolos: ";
	cin>>nSimbolos;
	cout<<"Numero de estados finales: ";
	cin>>nFinales;
	cin.ignore();						//Se limpia el buffer
	
	string estados[nEstados];			//Vector de estados
	string simbolos[nSimbolos];			//Vector de simbolos
	string estadoI,estadosF[nFinales];	//Estado inicial | Vector de estados finales
	
	for(int i=0;i<nEstados;i++){		//Se guardan los estados
		stringstream ss;				//clase auxiliar para convertir int a string
	 	ss<<i;
		ss>>estados[i];
	}
	
	estadoI = estados[0]; 				//Se guarda el estado inicial
	
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
	
	AFN afn = AFN(estados,simbolos,estadoI,estadosF,nEstados,nSimbolos,nFinales); //se crea el objeto AFN mandandole los datos ingresados
	afn.solicitarTransiciones();		//Se solicita al usuario que ingrese la tabla de transiciones
	
	//---------------------------------| IMPLEMENTACION DE ALGORITMO TOMADO DEL AHO |--------------------------------------
	
	vector<string> producciones; //Vector que guardara las producciones generadas
	
	do{
		if(candidatos.empty()==true){//Si el vector candidato ESTA vacio entonces hay que agregar el candidato inicial
			EstadoN T;				//Objeto Estado Nuevo 
			T.marcarDestado();		//Se marca como destado
			T.ingresarNucleo(0);	//El nucleo del primer candidato es el estado inicial
			
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
			
			
				int nucleoExistente=-1;
				
				for(int j=0;j<candidatos.size();j++){
					EstadoN auxiliar = candidatos[j];	
					
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
					
					produccion += "0N -> "+simbolos[i]+" -> "+aux+"N";
					producciones.push_back(produccion);
				}else{//El nucleo es igual a uno ya existente
					string aux,aux2, produccion = " ";
					stringstream ss,ss2;				//clase auxiliar para convertir int a string
														
					ss<<nucleoExistente;
					ss>>aux;
					
					produccion += "0N -> "+simbolos[i]+" -> "+aux+"N";
					producciones.push_back(produccion);					
				}
				
			}
			
			destado();	//se actualiza destados
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
			
			//NUEVOS CANDIDATOS
			
			for(int i=0;i<nSimbolos-1;i++){//se omite el simbolo epsilon
				EstadoN nuevoC;
				nuevoC = mover(afn,T,nuevoC,i);
				int nucleoExistente=-1;//-1 no existe | >0 si existe
				
				for(int j=0;j<candidatos.size();j++){//Se compara el nucleo del candidato nuevo con los que ya estan agregados
					EstadoN auxiliar = candidatos[j];
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
					
					produccion += aux2+"N -> "+simbolos[i]+" -> "+aux+"N";
					producciones.push_back(produccion);
					
				}else{//El nucleo es igual a uno ya existente
					string aux,aux2, produccion = " ";
					stringstream ss,ss2;				//clase auxiliar para convertir int a string
														
					ss<<nucleoExistente;
					ss>>aux;
					
					ss2<<indiceCandidato;
					ss2>>aux2;
					
					produccion += aux2+"N -> "+simbolos[i]+" -> "+aux+"N";
					producciones.push_back(produccion);					
				}
			}	
			destado();	//Se actualiza destados
		}
	}while(destados!=0);//end do - while

	cout<<"Destados: "<<destados<<endl;
	
	//--------------IMPRESION DE LOS ESTADOS CANDIDATOS
	cout<<"\tESTADOS NUEVOS\n"<<endl;
	for(int i=0;i<candidatos.size();i++){
		cout<< "Estado "<<i<<"N:{";
		EstadoN aux = candidatos[i];
		aux.mostrarNucleo();
		cout<<"| ";
		aux.imprimirDatos();
		cout<<"}"<<endl;
	}
	
	//--------------IMPRESION DE LAS PRODUCCIONES
	cout<<"\n\tTRANSICIONES\n"<<endl;
	for(int i=0;i<producciones.size();i++){
		cout<< producciones[i] <<endl;
	}
}
EstadoN Algoritmo::mover(AFN afx,EstadoN T, EstadoN nuevoC, int iSimbolo){
	//NOTA: agragar bloque para un recorrido total para x simbolo	
	int vectorT=T.obtenerTamanio();
	int nucleoT=T.nucleoTamanio();
	int n = vectorT+nucleoT;
	
	for(int i=0,j=0;i<n;i++){
		
		if(i<vectorT){//se recorren primero los que no son nucleos
			int auxEstado = T.obtenerTransicion(i); //Estados
			Estado auxiliar = afx.obtenerT_Estado(auxEstado,iSimbolo);
			
			if(auxiliar.estaVacia()!=true){
				nuevoC.ingresarNucleo(auxiliar.obtenerTransicion(0));
			}else{
				continue;
			}
		}else{//se recorre el nucleo
			int auxEstado = T.obtenerNucleo(j);
			Estado auxiliar = afx.obtenerT_Estado(auxEstado,iSimbolo);
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
bool Algoritmo::compararNucleos(EstadoN e1, EstadoN e2){
	vector<int> n1 = e1.obtenerNucleoVector();
	vector<int> n2 = e2.obtenerNucleoVector();
	
	if(n1==n2){
		return true;
	}else{
		return false;
	}
}
