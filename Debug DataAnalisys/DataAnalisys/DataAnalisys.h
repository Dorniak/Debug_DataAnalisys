#pragma once
#include "../Obstaculo/Obstaculo.h"
#include <math.h>
#include "../OpenGl/OpenGl.h"
#include <timeApi.h>
#include <stdlib.h>
#include "../Parametros/Parametros.h"

ref class DataAnalisys {
public:
	//Constructor
	DataAnalisys(List<Punto3D^>^ puntosController, List<Obstaculo^>^ ObstaculosController, cli::array<Object^>^ ParamAnalisys, List<int>^ Conclusiones, cli::array<bool>^ Flags, cli::array<Thread^>^ Threads, OpenGl^ Dibujador);
	//Funcion de thread
	void AnalisysThread2();
	void Esperar2();
	//Funcion para abortar el thread
	void Kill();

private:
	int frecuencia;
	int numCercanos;
	int localizador;
	int Obstmenor;
	bool iguales;

	void Informar(String^ Entrada);
	String^* Informe;
	OpenGl^ Dibujador;
	//Funcion que copia los obstaculos de la vuelta actual a la anterior y al control
	void copiarObstaculos();
	//Puntero al array de thread
	cli::array<Thread^>^ Threads;
	//Puntero al array de flags
	cli::array<bool>^ Flags;
	//Puntero a la lista de conclusiones
	List<int>^ Conclusiones;
	//array de parametros del DataAnalisys
	cli::array<Object^>^ parametros;
	//Valor de consigna de velocidad para el vector de conclusiones
	double  consigna_velocidad;
	//Valor de consigna de volante para el vector de conclusiones
	double  consigna_volante;

	double apertura;

	int indice;

	int menor;
	//Velocidad actual del coche
	double VCOCHE;

	double resolutionH;
	double resolutionV;

	//numero de barridos que es variable por la configuracion del laser
	int NUMERO_COLUMNAS;
	//Lista de obstaculos obtenidos en el analisys de la vuelta actual
	List<Obstaculo^>^ Obstaculos ;
	//Lista de obstaculos de la vuelta anterior
	List<Obstaculo^>^ ObstaculosvAnt ;
	//Lista usada para ordenacion
	cli::array<bool>^ Cercanos ;
	cli::array<Punto3D^>^ PCercanos ;
	//Funcion encargada de agrupar puntos en obstaculos
	void Segmentacion(List<Punto3D^>^ matrix, double apertura);

	void ResetParametros();

	void prepararObstaculos();
	//Funcion encargada de eliminar obstaculos no validos
	void EliminarObstaculos();
	//Funcion encargada de relacionar los obstaculos obtenidos en la vuelta actual con los de la anterior
	void RelacionarObstaculos();
	//Funcion para relacionar los obstaculos por su velocidad
	void relacionarVel(int i, int j);
	//Funcion para relacionar los obstaculos por su posicion
	void relacionarPos(int i, int j, int VelC, int Res);
	//Funcion encargada de comprobar su existe un bloqueo frente al vehiculo
	bool comprobarBloqueo(List<Punto3D^>^ matriz);
	//Funcion que se encarga de decidir si dos puntos estan lo suficientemente cerca
	//para considerarse parte de un mismo obstaculo cuando dos puntos estan en la misma Vertical
	bool puntosCercanosV(Punto3D ^ p1, Punto3D ^ p2);
	bool puntosCercanosD(Punto3D ^ p1, Punto3D ^ p2);
	//Funcion que se encarga de decidir si dos puntos estan lo suficientemente cerca
	//para considerarse parte de un mismo obstaculo cuando dos puntos estan en la misma horizontal
	bool puntosCercanosH(Punto3D^ p1, Punto3D^ p2);
	//COnvierte una coordenada en el plano en una posicion de la lista de puntos
	int convaPos(int columna, int fila);
	//LIsta en la que se guardan los puntos de esta vuelta
	List<Punto3D^>^ matriz;
	List<Punto3D^>^ matriz_pointer;
	//Objeto thread del analisys
	Thread^ thread_analysis;
	void MoverObstaculo(int Obst1, int Obst2);
	int cambios;
};