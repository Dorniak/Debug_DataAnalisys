#pragma once
#include "../Obstaculo/Obstaculo.h"
#include <math.h>
#include "../OpenGl/OpenGl.h"
#include <timeApi.h>
#include <stdlib.h>
#include "../Parametros/Parametros.h"

ref class DataAnalisys {
public:
	DataAnalisys(List<Punto3D^>^ puntosController, List<Obstaculo^>^ ObstaculosController, cli::array<Object^>^ ParamAnalisys, List<double>^ Conclusiones, cli::array<bool>^ Flags, cli::array<Thread^>^ Threads, OpenGl^ Dibujador);
	void AnalisysThread_debug();
	void Esperar_debug();
	void Kill();
private:
	int frecuencia;
	int cambios;
	/// <summary>
	/// Numero de columnas de la vuelta actual considerando la lista de entrada como una matriz de 16 filas y n columnas
	/// </summary>
	int NUMERO_COLUMNAS;
	/// <summary>
	/// Numero de puntos ya tratados que se consideran cercanos al punto a tratar
	/// </summary>
	int numCercanos;
	/// <summary>
	/// Indicador de la posicion del punto cercano al punto a tratar en el array de puntos cercanos
	/// </summary>
	int localizador;
	/// <summary>
	/// Numero del obstaculo menor entre los posibles obstaculos a incluir el punto
	/// </summary>
	int Obstmenor;
	/// <summary>
	/// Selector del obstaculo a relacionar entre la vuelta actual y la anterior
	/// </summary>
	int indice;
	/// <summary>
	/// Grados de apertura util del laser a tratar descartando los puntos fuera de ese rango
	/// </summary>
	double apertura;
	/// <summary>
	/// Valor de velocidad objetivo devuelto por el algoritmo segun las condiciones del entorno
	/// </summary>
	double  consigna_velocidad;
	/// <summary>
	/// Valor de volante objetivo devuelto por el algoritmo segun las condiciones del entorno
	/// </summary>
	double  consigna_volante;
	/// <summary>
	/// Velocidad real del coche obtenida del ordenador de bajo nivel
	/// </summary>
	double VCOCHE;
	/// <summary>
	/// Indicador de si los puntos adyacentes y cercanos ya tratados corresponden al mismo obstaculo
	/// </summary>
	bool iguales;
	/// <summary>
	/// Valor de resolucion entre disparos adyacentes horizontales del laser
	/// </summary>
	double resolutionH;
	/// <summary>
	/// Valor de resolucion entre disparos adyacentes verticales del laser
	/// </summary>
	double resolutionV;
	/// <summary>
	/// Puntero al informe de ejecución de del DataAnalisys localizado en el controlador
	/// </summary>
	String^* Informe;
	/// <summary>
	/// Objeto dibujador necesario para poder enviar la informacion del los obstaculos creados a la interfaz
	/// </summary>
	OpenGl^ Dibujador;
	/// <summary>
	/// Lista de entrada de parametros que vienen de la interfaz
	/// </summary>
	cli::array<Object^>^ parametros;
	/// <summary>
	/// Array de threads necesario para guardar el identificador de thread creado y asi poder cerrarlo al finalizar la ejecución
	/// </summary>
	cli::array<Thread^>^ Threads;
	/// <summary>
	/// Array de flags que indican los servicios levantados
	/// </summary>
	cli::array<bool>^ Flags;
	/// <summary>
	/// Array de indicadores de puntos cercanos validos
	/// </summary>
	cli::array<bool>^ Cercanos;
	/// <summary>
	/// Array donde se guardan los puntos cercanos
	/// </summary>
	cli::array<Punto3D^>^ PCercanos;
	/// <summary>
	/// Lista de conclusiones que se envia al controlador para que ejecute las medidas necesarias
	/// </summary>
	List<double>^ Conclusiones;
	/// <summary>
	/// Lista de obstaculos obtenidos de los puntos de la vuelta actual
	/// </summary>
	List<Obstaculo^>^ Obstaculos;
	/// <summary>
	/// Lista de obstaculos obtenidos de los puntos de la vuelta anterior
	/// </summary>
	List<Obstaculo^>^ ObstaculosvAnt;
	/// <summary>
	/// Matriz de puntos interna al DataAnalisys
	/// </summary>
	List<Punto3D^>^ matriz;
	/// <summary>
	/// Enlace a la matriz de puntos real localizada en el controlador
	/// </summary>
	List<Punto3D^>^ matriz_pointer;
	/// <summary>
	/// Funcion encargada de agrupar los puntos en obstaculos mediante un algoritmo de agrupacion de puntos por vecindad
	/// </summary>
	/// <param name="matrix">Lista de entrada de puntos</param>
	/// <param name="apertura">Rango de espacio valido para el tratamiento</param>
	void Segmentacion(List<Punto3D^>^ matrix, double apertura);
	/// <summary>
	/// Funcion encargada de guardar los informes de ejecución en el informe general para poder enviarlo a la interfaz
	/// </summary>
	/// <param name="Entrada">String de entreda que se añade al informe de ejecución</param>
	void Informar(String^ Entrada);
	/// <summary>
	/// Resetea los parametros necesarios para el tratamiento de cada punto
	/// </summary>
	void ResetParametros();
	/// <summary>
	/// Copia los obstaculos obtenidos al dibujador para que los represente en la interfaz
	/// </summary>
	void copiarObstaculos();
	/// <summary>
	/// Calcula algunos parametros basicos del obstaculo para realizar tratamientos posteriores
	/// </summary>
	void prepararObstaculos();
	/// <summary>
	/// Elimina los obstaculos que no cumplen ciertas caracteristicas para ser considerados peligrosos
	/// </summary>
	void EliminarObstaculos();
	/// <summary>
	/// relaciona cada obstaculo de la vuelta actual con uno de la vuelta anterior si es posible para hacer un tracking del obstaclo
	/// </summary>
	void RelacionarObstaculos();
	/// <summary>
	/// Funcion	que relaciona obstaculos que ya tienen una velociadad asignada anteriormente
	/// </summary>
	/// <param name="i">Selector del primer obstaculo</param>
	/// <param name="j">Selector del segundo obstaculo</param>
	void relacionarVel(int i, int j);
	/// <summary>
	/// Mueve los puntos de un obstaculo a otro si se detecta que son coincidentes
	/// </summary>
	/// <param name="Obst1"></param>
	/// <param name="Obst2"></param>
	void MoverObstaculo(int Obst1, int Obst2);
	/// <summary>
	/// Funcion	que relaciona obstaculos que no han sido relacionados con ningun otro antes
	/// </summary>
	/// <param name="i"></param>
	/// <param name="j"></param>
	/// <param name="Frecuency">Frecuencia de giro</param>
	void relacionarPos(int i, int j, double Frecuency);
	/// <summary>
	/// Comprueba si hay algun obstaculo enfrente del laser
	/// </summary>
	/// <param name="matriz">Matriz de puntos</param>
	/// <returns></returns>
	bool comprobarBloqueo(List<Punto3D^>^ matriz);
	/// <summary>
	/// Funcion que indica si dos puntos colocados verticalmente estan cerca
	/// </summary>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <returns></returns>
	bool puntosCercanosV(Punto3D ^ p1, Punto3D ^ p2);
	/// <summary>
	/// Funcion que indica si dos puntos colocados diagonalmente estan cerca
	/// </summary>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <returns></returns>
	bool puntosCercanosD(Punto3D ^ p1, Punto3D ^ p2);
	/// <summary>
	/// Funcion que indica si dos puntos colocados horizontalmente estan cerca
	/// </summary>
	/// <param name="p1"></param>
	/// <param name="p2"></param>
	/// <returns></returns>
	bool puntosCercanosH(Punto3D^ p1, Punto3D^ p2);
	/// <summary>
	/// Convierte una coordenada en la matriz en una posicion en la lista de puntos
	/// </summary>
	/// <param name="columna"></param>
	/// <param name="fila"></param>
	/// <returns></returns>
	int convaPos(int columna, int fila);
	/// <summary>
	/// Objeto thread en el que se guarda el thread del DataAnalisys
	/// </summary>
	Thread^ thread_analysis;

};