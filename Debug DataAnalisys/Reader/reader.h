#pragma once
#pragma warning( disable : 4244 ) //Life is not perfect
#include "../Punto3D/Punto3D.h"
#include <cliext/vector>
#include "../OpenGl/OpenGl.h"
#include "../Parametros/Parametros.h"

ref class DataReader
{

public:
	
	DataReader(List<Punto3D^>^ puntosController, cli::array<Object^>^ parameters, String^ path, cli::array<bool>^ Flags, cli::array<Thread^>^ Threads, OpenGl^ Dibujador_in);

	void Read_t(int selector);

	void Read_S();
	
	void Read();

	void Kill();
	
	long frame;

	bool newFrame;

	int numSelector;

private:
		
	String^ path;

	OpenGl^ Dibujador;

	cli::array<Object^>^ ArrayDataReader;
	
	cli::array<Thread^>^ Threads;
	
	cli::array<bool>^ Flags;
	
	cli::array<Object^>^ ArrayGps;
	
	List<Punto3D^>^ puntosController;

	double CALIBRATE_X, CALIBRATE_Y, CALIBRATE_Z, CALIBRATE_R, CALIBRATE_P, CALIBRATE_W, max, min,recorrido_disparo,recorrido_recarga;
	int azimuth_index, distance_index, intensity_index;

	StreamReader^ sr;

	List<Punto3D^>^ Puntos = gcnew List<Punto3D^>;
	
	Thread^ thread_reader;

	Thread^ Selector_thread;

	
	
	StreamWriter^ loger;

	void copiarPuntos();

	void Informar(String ^ Entrada);
		
	void Esperar();
};

