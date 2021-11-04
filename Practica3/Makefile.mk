#Variables
OBJS = Main.o Algoritmo.o AFN.o Estado.o EstadoN.o

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

Estado.o: Estado.cpp Estado.hpp
	g++ -c Estado.cpp

EstadoN.o: EstadoN.cpp EstadoN.hpp
	g++ -c EstadoN.cpp

#Se eliminan los archivos .o
clean:
	rm -f programa OBJS