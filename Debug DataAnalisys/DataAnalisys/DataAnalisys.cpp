#include "DataAnalisys.h"
DataAnalisys::DataAnalisys(List<Punto3D^>^ puntosController, List<Obstaculo^>^ ObstaculosController, cli::array<Object^>^ ParamAnalisys, List<double>^ Conclusiones, cli::array<bool>^ Flags, cli::array<Thread^>^ Threads, OpenGl^ Dibujador)
{
	try {
		this->Informe = Informe;
		this->Threads = Threads;
		this->Flags = Flags;
		parametros = ParamAnalisys;
		parametros[INFORMEA] = " ";
		this->Conclusiones = Conclusiones;
		matriz_pointer = puntosController;
		matriz = gcnew List<Punto3D^>();
		ObstaculosvAnt = ObstaculosController;
		Obstaculos = gcnew List<Obstaculo^>();
		Cercanos = gcnew cli::array<bool>(4);
		cambios = 0;
		PCercanos = gcnew cli::array<Punto3D^>(4);
		if (!thread_analysis) {
			thread_analysis = gcnew Thread(gcnew ThreadStart(this, &DataAnalisys::Esperar2));
		}
		thread_analysis->Start();
		//Guarda el identificador de thread en el array de threads del Controllerador 
		Threads[1] = thread_analysis;
	}
	catch (Exception^ e) {
		Informar(e->ToString());
	}
}
//matriz::Lista de puntos
//resolucionAngular::resolucion del laser
//Vcoche::velocidad actual del coche
//consigna velocidad:: puntero para devolucion de parametro de velocidad
//consigna volante:: puntero para devolucion de parametro de volante
//apertura::Angulo de interes de lectura en grados
//List<Punto3D^>^ matriz, double resolucionAngular,double Vcoche, double &consigna_velocidad, double &consigna_volante, double apertura

void DataAnalisys::AnalisysThread2()
{
	Informar("Iniciando Thread Analisis");
	//while (Flags[FLAG_ANALISYS] && !Flags[FLAG_WARNING] && !Flags[FLAG_PAUSA])
	//{
	while (Flags[FLAG_ANALIZAR]) {
		Informar("Interior del while");
		try
		{
			if (!Flags[FLAG_TRATAMIENTO]) {
				Informar("Tratamiento");
				matriz->Clear();
				matriz->AddRange(matriz_pointer);
				//matriz = Controllerador->Puntos;  La matriz es siempre igual a la matriz de puntos
				resolutionH = Convert::ToDouble(parametros[HORIZONTAL_RESOLUTION]);//Resolucion
				resolutionV = Convert::ToDouble(parametros[VERTICAL_RESOLUTION]);//Resolucion
				VCOCHE = Convert::ToDouble(parametros[CAR_VELOCITY]);//Vcoche
				apertura = Convert::ToDouble(parametros[OPENING]);//Apertura
				NUMERO_COLUMNAS = matriz->Count / NUMERO_FILAS;
				frecuencia = Convert::ToInt32(parametros[FRECUENCIA]);
				
				//Trabajo

				if (/*VCOCHE > 5*/true) {
					Informar("Velocidad minima tratamiento");
					if (!comprobarBloqueo(matriz))
					{
						Informar("No hay bloqueo");
						Informar("Segmentacion");
						Segmentacion(matriz, apertura);
						Informar("Fin Segmentacion");
						Informar("Numero de obstaculos:" + Obstaculos->Count);
						Informar("Cambios" + cambios);
						Informar("Puntos totales " + matriz->Count);
						//TODO::Identificar tipo de obstaculo
						if (Obstaculos->Count > 0) {
							Informar("Eliminar obstaculos no validos");
							EliminarObstaculos();
							Informar("Preparar obstaculos");
							prepararObstaculos();
							Informar("Relacionar obstaculos");
							RelacionarObstaculos();
							//Copiar el vector de obstaculos obtenido en Controller y comprueba colisiones
							Informar("Copiar Obstaculos");
							copiarObstaculos();
						}
					}
					else {
						Informar("Bloqueo");
						consigna_velocidad = 0.0;
					}
				}
				else {
					Informar("Error Velocidad minima tratamiento");
				}

				//Fin tratamiento
				//Actualizar consignas en el vector de conclusiones
				Conclusiones[0] = consigna_velocidad;
				Conclusiones[1] = consigna_volante;
			}
			Sleep(200);
			Flags[FLAG_ANALIZAR] = false;
		}
		catch (Exception^ e)
		{
			Informar("Excepcion" + e->ToString());
			Flags[FLAG_WARNING] = true;
			Flags[FLAG_ANALIZAR] = false;
		}
	}
	//En caso de que se desactive y se reactive despues hay que limpiar los objetos
	ObstaculosvAnt->Clear();
	Esperar2();
}


void DataAnalisys::Esperar2()
{
	Informar("ESTOY EN ESPERA");
	while (!Flags[FLAG_ANALIZAR]) {
		//	if (Flags[FLAG_WARNING])
		//		Kill();
		Sleep(200);
	}
	AnalisysThread2();
}

void DataAnalisys::Kill()
{
	thread_analysis->Abort();
}

void DataAnalisys::Informar(String ^ Entrada)
{
	parametros[INFORME_ANALISYS] += "[" + DateTime::Now.ToString("HH - mm - ss") + "]" + Entrada + "\r\n";
}

void DataAnalisys::copiarObstaculos()
{

	//Controller de collision
	if (Flags[FLAG_TRATAMIENTO]) {
		Flags[FLAG_WARNING] = true;
		Informar("Error de Colision");
		//mensaje pantalla
	}
	Flags[FLAG_TRATAMIENTO] = true;
	

	ObstaculosvAnt->Clear();
	ObstaculosvAnt->AddRange(Obstaculos);

	Informar("Numero de obstaculos a copiar: " + ObstaculosvAnt->Count);
	if (Flags[FLAG_OPENGL]) {
		Informar("Obstaculos->OpenGl");
		Dibujador->modificarObstaculos(ObstaculosvAnt);
	}
	Obstaculos->Clear();
}

void DataAnalisys::Segmentacion(List<Punto3D^>^ matrix, double apertura)
{
	//int inicio = (NUMERO_COLUMNAS / 2); //- aprr;
	//int final = (NUMERO_COLUMNAS / 2); //+ aprr;
	int inicio = 0;
	int final = NUMERO_COLUMNAS;

	//Se recorre la matriz linealmente
	Informar("Comienzo del recorrido de la matriz");
	for (int fila = 0; fila <= NUMERO_FILAS - 1; fila++)//Recorrido de filas
	{
		for (int columna = inicio; columna < final; columna++)//Recorrido de columnas
		{
			try {
				//Se comprubea si el punto a tratar Existe
				if (matrix[convaPos(columna, fila)]->valido && (matrix[convaPos(columna, fila)]->getAzimuth()>(180 - apertura)) && (matrix[convaPos(columna, fila)]->getAzimuth() < (180 + apertura)))
				{
					ResetParametros();
					//En caso de que sea el primer punto se asigna directamente al obstaculo 0
					if (columna == 0 && fila == inicio && matrix[convaPos(columna, fila)]->valido)
					{
						//Mete al final del vector de obstaculos un obstaculo que crea
						Obstaculos->Add(gcnew Obstaculo());
						matrix[convaPos(columna, fila)]->setObstacle(0);
						//Accede al obstaculo 0, al vector de componentes, mente el punto en el vector de componentes
						Obstaculos[Obstaculos->Count - 1]->components->Add(matrix[convaPos(columna, fila)]);
					}
					else {
						//Se compara cada punto a tratar con sus puntos adyacentes ya tratados

						if (fila > 0)
						{
							//Punto de encima misma columna fila-1
							if (puntosCercanosV(matrix[convaPos(columna, fila)], matrix[convaPos(columna, fila - 1)]))
							{
								Cercanos[0] = true;
								PCercanos[0] = matrix[convaPos(columna, fila - 1)];
							}
							if (columna > 0)
							{
								//Punto de encima a la izquierda columna-1 fila-1
								if (puntosCercanosD(matrix[convaPos(columna, fila)], matrix[convaPos(columna - 1, fila - 1)]))
								{
									Cercanos[1] = true;
									PCercanos[1] = matrix[convaPos(columna - 1, fila - 1)];
								}
							}
							if (columna < NUMERO_COLUMNAS - 1)
							{
								//Punto de encima a la derecha columna+1 fila-1
								if (puntosCercanosD(matrix[convaPos(columna, fila)], matrix[convaPos(columna + 1, fila - 1)]))
								{
									Cercanos[2] = true;
									PCercanos[2] = matrix[convaPos(columna + 1, fila - 1)];
								}
							}
						}
						if (columna > 0)
						{
							//Punto de la izquierda columna-1 fila
							if (puntosCercanosH(matrix[convaPos(columna, fila)], matrix[convaPos(columna - 1, fila)]))
							{
								Cercanos[3] = true;
								PCercanos[3] = matrix[convaPos(columna - 1, fila)];
							}
						}

						numCercanos = 0;
						for (int recorrido = 0; recorrido < 4; recorrido++)
						{
							if (Cercanos[recorrido])
							{
								numCercanos++;
								localizador = recorrido;
							}
						}

						if (numCercanos == 0)
						{
							Obstaculos->Add(gcnew Obstaculo());
							matrix[convaPos(columna, fila)]->setObstacle(Obstaculos->Count - 1);
							Obstaculos[Obstaculos->Count - 1]->components->Add(matrix[convaPos(columna, fila)]);
						}
						else if (numCercanos == 1) {
							if (PCercanos[localizador]->getObstacle() != -1) {
								matrix[convaPos(columna, fila)]->setObstacle(PCercanos[localizador]->getObstacle());
								Obstaculos[matrix[convaPos(columna, fila)]->getObstacle()]->components->Add(matrix[convaPos(columna, fila)]);
							}
							else {
								Obstaculos->Add(gcnew Obstaculo());
								matrix[convaPos(columna, fila)]->setObstacle(Obstaculos->Count - 1);
								Obstaculos[Obstaculos->Count - 1]->components->Add(matrix[convaPos(columna, fila)]);
							}
						}
						else {
							for (int recorrido2 = 0; recorrido2 < 4; recorrido2++)
							{
								if (Cercanos[recorrido2]) {
									if (Obstmenor == -1) {
										Obstmenor = PCercanos[recorrido2]->getObstacle();
									}
									else if (PCercanos[recorrido2]->getObstacle() != Obstmenor) {
										iguales = false;
										if (PCercanos[recorrido2]->getObstacle() < Obstmenor)
										{
											Obstmenor = PCercanos[recorrido2]->getObstacle();
										}
									}
								}
							}
							if (iguales) {
								matrix[convaPos(columna, fila)]->setObstacle(Obstmenor);
								Obstaculos[Obstmenor]->components->Add(matrix[convaPos(columna, fila)]);
							}
							else {
								for (int recorrido3 = 0; recorrido3 < 4; recorrido3++) {
									if (Cercanos[recorrido3]) {
										if (PCercanos[recorrido3]->getObstacle() != Obstmenor && Obstmenor != -1) {
											MoverObstaculo(PCercanos[recorrido3]->getObstacle(), Obstmenor);
											cambios++;
										}
									}
								}
								matrix[convaPos(columna, fila)]->setObstacle(Obstmenor);
								Obstaculos[Obstmenor]->components->Add(matrix[convaPos(columna, fila)]);
							}
						}
					}
					if (matrix[convaPos(columna, fila)]->getObstacle() == -1) {
						Obstaculos->Add(gcnew Obstaculo());
						matrix[convaPos(columna, fila)]->setObstacle(Obstaculos->Count - 1);
						Obstaculos[Obstaculos->Count - 1]->components->Add(matrix[convaPos(columna, fila)]);
					}
				}
			}
			catch (Exception^) {
			}
		}
	}
	//Tratamiento de la linea del 0

	for (int fila = 0; fila < NUMERO_FILAS; fila++) {
		try {
			ResetParametros();
			//Comprobar punto de arriba
			if (matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]->valido) {
				if (fila == 0) {
					//punto horizontal
					if (puntosCercanosH(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)], matrix[convaPos(0, fila)]))
					{
						Cercanos[1] = true;
						PCercanos[1] = matrix[convaPos(0, fila)];
					}
					//Punto diagonal abajo
					if (puntosCercanosD(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)], matrix[convaPos(0, fila + 1)]))
					{
						Cercanos[2] = true;
						PCercanos[2] = matrix[convaPos(0, fila + 1)];
					}
				}
				//Comprobar punto de abajo
				else if (fila == NUMERO_FILAS - 1) {
					//Punto diagonal arriba
					if (puntosCercanosD(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)], matrix[convaPos(0, fila - 1)]))
					{
						Cercanos[0] = true;
						PCercanos[0] = matrix[convaPos(0, fila - 1)];
					}
					//punto horizontal
					if (puntosCercanosH(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)], matrix[convaPos(0, fila)]))
					{
						Cercanos[1] = true;
						PCercanos[1] = matrix[convaPos(0, fila)];
					}
				}
				//Comprobar punto centrales
				else {
					//Punto diagonal arriba
					if (puntosCercanosD(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)], matrix[convaPos(0, fila - 1)]))
					{
						Cercanos[0] = true;
						PCercanos[0] = matrix[convaPos(0, fila - 1)];
					}
					//punto horizontal
					if (puntosCercanosH(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)], matrix[convaPos(0, fila)]))
					{
						Cercanos[1] = true;
						PCercanos[1] = matrix[convaPos(0, fila)];
					}
					//Punto diagonal abajo
					if (puntosCercanosD(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)], matrix[convaPos(0, fila + 1)]))
					{
						Cercanos[2] = true;
						PCercanos[2] = matrix[convaPos(0, fila + 1)];
					}
				}
				numCercanos = 0;
				for (int recorrido = 0; recorrido < 4; recorrido++)
				{
					if (Cercanos[recorrido])
					{
						numCercanos++;
						localizador = recorrido;
					}
				}
				if (numCercanos == 0)
				{
				}
				else if (numCercanos == 1) {
					if (PCercanos[localizador]->getObstacle() != -1) {
						matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]->setObstacle(PCercanos[localizador]->getObstacle());
						Obstaculos[matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]->getObstacle()]->components->Add(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]);
					}
				}
				else {
					for (int recorrido2 = 0; recorrido2 < 4; recorrido2++)
					{
						if (Cercanos[recorrido2]) {
							if (Obstmenor == -1) {
								Obstmenor = PCercanos[recorrido2]->getObstacle();
							}
							else if (PCercanos[recorrido2]->getObstacle() != Obstmenor) {
								iguales = false;
								if (PCercanos[recorrido2]->getObstacle() < Obstmenor)
								{
									Obstmenor = PCercanos[recorrido2]->getObstacle();
								}
							}
						}
					}
					if (iguales) {
						matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]->setObstacle(Obstmenor);
						Obstaculos[Obstmenor]->components->Add(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]);
					}
					else {
						for (int recorrido3 = 0; recorrido3 < 4; recorrido3++) {
							if (Cercanos[recorrido3]) {
								if (PCercanos[recorrido3]->getObstacle() != Obstmenor && Obstmenor != -1) {
									MoverObstaculo(PCercanos[recorrido3]->getObstacle(), Obstmenor);
									cambios++;
								}
							}
						}
						matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]->setObstacle(Obstmenor);
						Obstaculos[Obstmenor]->components->Add(matrix[convaPos(NUMERO_COLUMNAS - 1, fila)]);
					}
				}
			}
		}
		catch (Exception^ e) {
		}
	}
}

void DataAnalisys::ResetParametros() {
	Obstmenor = -1;
	for (int i = 0; i < 4; i++)
	{
		Cercanos[i] = false;
		PCercanos[i] = nullptr;
	}

	iguales = true;
}

void DataAnalisys::prepararObstaculos()
{
	for (int i = 0; i < Obstaculos->Count; i++)
	{
		Obstaculos[i]->prepareObstacle();//TODO::Calcular centro,cubo,y todo lo necesario
	}
}

void DataAnalisys::EliminarObstaculos()
{
	int ObstPequeños = 0;
	int ObstEliminados = 0;
	Informar("Numero de obstaculos inicial " + Obstaculos->Count);
	for (int p = 0; p < Obstaculos->Count; p++)
	{
		if (!Obstaculos[p]->Valido) {
			Obstaculos->RemoveAt(p);
			p--;
			ObstEliminados++;
		}
		else if (Obstaculos[p]->components->Count < TAMAÑO_MINIMO_OBSTACULO)
		{
			//TODO::Ajustar el numero minimo de puntos para considerarlo un obstaculo
			Obstaculos->RemoveAt(p);
			p--;
			ObstPequeños++;
		}
	}
	Informar("Numero de obstaculos pequeños " + ObstPequeños + " Numero de Obstaculos eliminados: " + ObstEliminados + " Numero de obstaculos final: " + Obstaculos->Count);
}

void DataAnalisys::RelacionarObstaculos()
{
	Informar("Relacionar obstaculos inicio");
	for (int i = 0; i < Obstaculos->Count; i++)
	{
		indice = -1;
		for (int j = 0; j < ObstaculosvAnt->Count; j++)
		{
			Informar("Primera comparacion");
			if (ObstaculosvAnt[j]->getVelocity() >= 1)
			{
				Informar("Relacion por velocidad");
				//0.3 es la distancia maxima que que puede recorrer entre barridos
				if (Obstaculos[i]->getCenter()->distanceToPoint(ObstaculosvAnt[j]->getPrediceCenter()) < (VCOCHE / 3.6) * TIEMPO_MARGEN)// POrque 0.3??  = 0.0833
				{
					relacionarVel(i, j);
					indice = j;
				}
			}
			else if (Obstaculos[i]->getCenter()->distanceToPoint(ObstaculosvAnt[j]->getCenter()) < DISTANCIA_MAXIMA /*&& fabs(Obstaculos[i].getYaw() - Obstaculos[i].getYaw()) < 5*/)
			{
				Informar("Relacion por posicion");
				relacionarPos(i, j,frecuencia);
				indice = j;

			}
			Informar("Obstaculo " + i +" "+ j+" Distancia ==> "+ Obstaculos[i]->getCenter()->distanceToPoint(ObstaculosvAnt[j]->getCenter()));
		}
		
		Informar("Obstaculo " + i + " ==> " + indice);
	}
}

void DataAnalisys::relacionarVel(int i, int j)
{
	Obstaculos[i]->setDirection(ObstaculosvAnt[j]->getCenter());
	Obstaculos[i]->calculatePrediceCenter();
	Obstaculos[i]->setVelocity(VCOCHE, resolutionH);
	Obstaculos[i]->calculateTimeToCollision(VCOCHE);
}

void DataAnalisys::relacionarPos(int i, int j, double Frecuency)
{
	Obstaculos[i]->setDirection(ObstaculosvAnt[j]->getCenter());
	Obstaculos[i]->calculatePrediceCenter();
	Obstaculos[i]->setVelocity(VCOCHE, Frecuency);
}
//TODO::Modificar en el original
bool DataAnalisys::comprobarBloqueo(List<Punto3D^>^ matriz)
{

	//Devuelve true cuando hay bloqueo
	int medio = (matriz->Count / 16) / 2;
	Punto3D^ prueba;

	for (int k = medio - 30; k < medio + 30; k++) {
		for (int i = 0; i < NUMERO_FILAS; i++) {
			if (matriz[convaPos(k, i)]->valido && matriz[convaPos(k, i)]->getDistance() < 15 && matriz[convaPos(k, i)]->getCoordinatesZ() > 5) {//Altura de bloquepmayor k 0.2
				prueba = matriz[convaPos(k, i)];
				return true;
			}
		}
	}
	return false;
}

bool DataAnalisys::puntosCercanosH(Punto3D^ p1, Punto3D^ p2)
{
	double tolerancia = p1->getDistance() * tan(resolutionH * PI / 180);
	tolerancia = tolerancia * ((100 + HORIZONTAL_TOLERANCE) / 100);
	return(tolerancia > p1->distanceToPoint(p2));
}

bool DataAnalisys::puntosCercanosV(Punto3D^ p1, Punto3D^ p2)
{
	double toleranciaV = p1->getDistance() * tan(resolutionV  * PI / 180);
	double toleranciaH = p1->getDistance() * tan(((resolutionH - (2 * 20 * 0.00001843 * 180)) / 16)  * PI / 180);
	Punto3D ^ a = gcnew Punto3D(toleranciaH, toleranciaV, 0);
	double tolerancia = a->getModule();
	tolerancia = tolerancia * ((100 + VERTICAL_TOLERANCE) / 100);
	return(tolerancia > p1->distanceToPoint(p2));
}

bool DataAnalisys::puntosCercanosD(Punto3D^ p1, Punto3D^ p2)
{
	double toleranciaV = p1->getDistance() * tan(resolutionV  * PI / 180);
	double toleranciaH = p1->getDistance() * tan(resolutionH  * PI / 180);
	Punto3D ^ a = gcnew Punto3D(toleranciaH, toleranciaV, 0);
	double tolerancia = a->getModule();
	tolerancia *= ((100 + DIAGONAL_TOLERANCE) / 100);
	return(tolerancia > p1->distanceToPoint(p2));
}

int DataAnalisys::convaPos(int columna, int fila)
{
	int f;
	switch (fila)
	{
	case 0: f = 15; break;
	case 1: f = 13; break;
	case 2: f = 11; break;
	case 3: f = 9; break;
	case 4: f = 7; break;
	case 5: f = 5; break;
	case 6: f = 3; break;
	case 7: f = 1; break;
	case 8: f = 14; break;
	case 9: f = 12; break;
	case 10: f = 10; break;
	case 11: f = 8; break;
	case 12: f = 6; break;
	case 13: f = 4; break;
	case 14: f = 2; break;
	case 15: f = 0; break;
	default: f=-1;
	}
	return columna * 16 + f;
}

void DataAnalisys::MoverObstaculo(int Obst1, int Obst2)
{
	for (int i = 0; i < Obstaculos[Obst1]->components->Count; i++) {
		Obstaculos[Obst1]->components[i]->setObstacle(Obst2);
		Obstaculos[Obst2]->components->Add(Obstaculos[Obst1]->components[i]);
	}
	Obstaculos[Obst1]->Valido = false;
}
