#pragma once
//Posicion parametros array Flags
#define SIZE_ARRAY_FLAGS 8

#define FLAG_TRATAMIENTO 0
#define FLAG_LOG 1
#define FLAG_WARNING 2
#define FLAG_PAUSA 3
#define FLAG_ANALISYS 4
#define FLAG_OPENGL 5
#define FLAG_LOCK 6
#define FLAG_ANALIZAR 7


//Numero de parametros de los arrays
#define SIZE_ARRAY_READER 14
#define SIZE_ARRAY_ANALISYS 7
//Posicion parametros array Reader
#define PATH_LOG 0
#define IP 1
#define PCALIBRATE_X 2
#define PCALIBRATE_Y 3
#define PCALIBRATE_Z 4
#define PCALIBRATE_R 5
#define PCALIBRATE_P 6
#define PCALIBRATE_W 7
#define MAX_DISTANCE 8
#define MIN_DISTANCE 9
#define INFORME 10
#define FRECUENCY_TIME 11
#define PROCESS_TIME 12
#define Hz 13


#define NUMBER_OF_BLOCKS 12
#define NUMBER_OF_CHANNELS 32


//Analisys puntos
#define VERTICAL_TOLERANCE 300
#define DIAGONAL_TOLERANCE 300
#define HORIZONTAL_TOLERANCE 300


//Posicion parametros array DataAnalisys
#define HORIZONTAL_RESOLUTION 0
#define VERTICAL_RESOLUTION 1
#define OPENING 2
#define CAR_VELOCITY 3
#define INFORME_ANALISYS 4
#define INFORMEA 5
#define FRECUENCIA 6

//Constantes DataAnalisys
#define NUMERO_FILAS 16 //Coincide con el numero de canales
#define TAMAÑO_MINIMO_OBSTACULO 20
#define TIEMPO_MARGEN 0.3 //TODO: Ajustar parametro
#define DISTANCIA_MAXIMA 2
#define PI Math::PI

//Constantes OpenGl
#define NUM_OBSTACULOS 250

//Constantes GPS
#define SIZE_ARRAY_GPS 8
#define TIPO_TRAMA 0
#define TRAMA 1
#define START 2
#define COM 3
#define QUALITY 4
#define SATELITES 5
#define RATE 6
#define ESTADO 7
//THREADS
#define NUMERO_THREADS 4 
#define THREAD_READER 0
#define THREAD_ANALISIS 1
#define THREAD_OPENGL 2
#define THREAD_GPS 3 

//Constantes Logger
#define SIZE_ARRAY_LOGGER 1
#define BUFFER 0
//Includes para las clases Controller Reader DataAnalisys y OpenGl
using namespace std;
using namespace System;
//using namespace System::Net;
using namespace System::Text;
//using namespace System::Net::Sockets;
using namespace System::IO;
using namespace System::Text;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace System::Diagnostics;



ref class Parametros {

};