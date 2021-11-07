#Variables
OBJS = Main.o Algoritmo.o AFN.o Transicion.o EstadoCandidato.o

#Reglas para compilar el programa principal
all: programa

programa: $(OBJS)
	g++ -o programa $(OBJS)

Main.o: Main.cpp
	g++ -c Main.cpp

Algoritmo.o: Algoritmo.cpp Algoritmo.hpp
	g++ -c Algoritmo.cpp

AFN.o: AFN.cpp AFN.hpp
	g++ -c AFN.cpp

Transicion.o: Transicion.cpp Transicion.hpp
	g++ -c Transicion.cpp

EstadoCandidato.o: EstadoCandidato.cpp EstadoCandidato.hpp
	g++ -c EstadoCandidato.cpp

#Se eliminan los archivos .o
clean:
	rm -f programa $(OBJS)
