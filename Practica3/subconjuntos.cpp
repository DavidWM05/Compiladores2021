//Subconjuntos
#include <iostream>
#include<string> 
#include <vector> 
#include <sstream>
#include <cstring>
using namespace std;
class EstadoT{
	private:
		vector<string> transiciones;
	
	public:
		void setT(string t){
			transiciones.push_back(t);
		}
		string getT(int i){
			transiciones[i]
		}
};
class Subconjuntos{
	private: //Atributos
		//Tupla del AFN
		vector<string> S;			//estados
		vector<string> E;			//conjunto de simbolos
		string S0;					//estado inicial
		vector<string> F;			//conjunto de estados finales
		int Scount,Ecount,Fcount; 	//tamaño de S y E sin comas
		
	public: //metodos
		Subconjuntos(string _S[],string _E[],string _S0,string _F[],int nEstados,int nSimbolos,int nFinales){ //constructor
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
		void start(){
			int control=0;
			//TRANSICIONES
			vector<vector<string> > T; 
			
			//--------------------------------------
			for(int i=0,j=0;i<Scount;i++){
				vector<string> vaux;				//vector auxiliar
				vaux.push_back(S[i]);				//la primera posicion es del estado
				cout<<" Estado "<<S[i]<<": "<<endl; 
				
				for(int j=0;j<Ecount;j++){//Transiciones de estados con los simbolos
					int control=1;	//variable que controlara las transiciones
					string taux;	//estring auxiliar para la transicion
					
					cout<<"  Simbolo "<<E[j]<<": "<<endl;
					while(control!=0){
						cout<<"agregar transicion? si=1/0=no";
						cin>>control;
						switch(control){
							case 0:		taux=" - ";
							break;
							case 1:		//se solicita al usuario que ingrese la transicion
										cin.ignore();			
										cout<<E[j]<<" -> ";
										getline(cin,taux);
										control=0;
							break;
							default: cout<<"Opcion no valida, solo se puede ingresar 0=no | 1=si ";
						}//end switch
					}//end while
					vaux.push_back(taux); //se guarda en el vector auxiliar
				}
				T.push_back(vaux);	//se guardan los datos del vector auxiliar
			}
			//---------------------------------
		/*	cout<<"Ingresa las transiciones"<<endl;
			for(int i=0;i<Scount;i++){
				cout<<"Estado " <<T[i][0]<<": "<<endl;
				for(int j=1,k=0;j<Ecount+1;j++){
					cout<<"\t"<<E[k]<<": ";
					getline(cin,T[i][j]);
					k++;
				}
				cout<<endl;
			}*/
			
			for(int i=0;i<Scount;i++){
				for(int j=0;j<Ecount+1;j++){
					cout<<T[i][j]<<" ";
				}
				cout<<endl;
			}
	
		}
		void mover();	
		int vectorAux();
};

//------------------------------------------------------- |MAIN|------------------------------
int main(){
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
	
	
	Subconjuntos algoritmo = Subconjuntos(estados,simbolos,estadoI,estadosF,nEstados,nSimbolos,nFinales);
	algoritmo.start();
	
	
	system("PAUSE");
	return 0;
}
