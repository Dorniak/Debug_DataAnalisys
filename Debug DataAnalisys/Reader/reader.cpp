#include "reader.h"
#include <locale.h>

DataReader::DataReader(List<Punto3D^>^ puntosController_in, cli::array<Object^>^ parameters,String^ path, cli::array<bool>^ Flags_in, cli::array<Thread^>^ Threads_in, OpenGl^ Dibujador_in)
{
	try
	{
		this->Threads = Threads_in;
		this->Flags = Flags_in;
		this->path = path;
		this->puntosController = puntosController_in;
		this->ArrayDataReader = parameters;
		Informar("Comienzo");
		this->Dibujador = Dibujador_in;
		if (!thread_reader) {
			thread_reader = gcnew Thread(gcnew ThreadStart(this, &DataReader::Read));
		}
		thread_reader->Start();
		this->Threads[THREAD_READER] = thread_reader;
	}
	catch (Exception^ e)
	{
		
	}
}
void DataReader::Read_t(int selector) {
	numSelector = selector;
	if (!Selector_thread) {
		Selector_thread = gcnew Thread(gcnew ThreadStart(this, &DataReader::Read_S));
	}
	else {
		Selector_thread->Abort();
		Selector_thread = gcnew Thread(gcnew ThreadStart(this, &DataReader::Read_S));
	}
	Selector_thread->Start();
}

void DataReader::Read_S()
{
	Informar("Arranque del thread selector");
	if (sr) {
		sr->Close();
	}
	if (File::Exists(path)) {
		sr = File::OpenText(path);
		Informar("Apertura del fichero correcta");
	}
	else Informar("Error en la direccion del fichero");
	Informar("Limpieza de puntos");
	Puntos->Clear();
	frame = 0;
	String^ entrada;
	Informar("Lectura de la primera linea");
	entrada = sr->ReadLine();
	Informar("Numero de frame seleccionado: " + numSelector);
	while ((frame != -1 && numSelector > frame) || entrada->Length < 5)
	{
		Informar("while Busqueda" + "NumSelector " + numSelector + "Frame " + frame);
		entrada = sr->ReadLine();
		if (entrada != nullptr && entrada->Length > 5) {
			frame = Convert::ToInt32(entrada->Split(',')[0]);
			Informar("Correcto " + frame);
		}
		else if (entrada != nullptr) {
			Informar("Error de frame");
			frame = -1;
		}
	}
	Informar("Fin While Busqueda" + frame);
	if (frame == numSelector) {
		Punto3D^ a;
		Puntos->Add(gcnew Punto3D(Convert::ToDouble(entrada->Split(',')[2]), Convert::ToDouble(entrada->Split(',')[3]), Convert::ToDouble(entrada->Split(',')[4])));
		while (entrada->Length < 5 || frame == numSelector) {
			Informar("While Puntos");
			entrada = sr->ReadLine();
			if (entrada->Length > 5) {
				frame = Convert::ToInt32(entrada->Split(',')[0]);
				if (frame == numSelector) {
					Informar("Meter puntos");
					Punto3D^ a;
					Puntos->Add(gcnew Punto3D(Convert::ToDouble(entrada->Split(',')[2]), Convert::ToDouble(entrada->Split(',')[3]), Convert::ToDouble(entrada->Split(',')[4])));
				}
			}
		}
	}
	copiarPuntos();
	sr->Close();
	Informar("Fin Selector");
}
void DataReader::Read()
{
	Informar("Comienzo");
	if (File::Exists(path)) {
		sr = File::OpenText(path);
	}
	while (true) {
		//entrada = Console::ReadLine();
		String^ entrada ;
		/*-------------------------------------------------------------------------------------------*/
		/*----------------------------------Lectura de fichero---------------------------------------*/
		/*-------------------------------------------------------------------------------------------*/
		//String^ interno = path+"\\Frame_"+frame;
		//String^ interno = path + "log.log";

		/*while ((entrada = sr->ReadLine()) != nullptr) {
		Punto3D^ a;
		Puntos->Add(gcnew Punto3D(Convert::ToDouble(entrada->Split(',')[2]), Convert::ToDouble(entrada->Split(',')[3]), Convert::ToDouble(entrada->Split(',')[4])));
		}
		sr->Close();*/
		if (Flags[FLAG_PAUSA]) {
			Esperar();
		}
		else {
			Sleep(1000/Convert::ToInt32(ArrayDataReader[Hz]));
		}
		while (true) {
			entrada = sr->ReadLine();
			if (entrada != nullptr && entrada->Length>5) {
				if (Convert::ToInt32(entrada->Split(',')[0]) == frame) {
					if(Convert::ToDouble(entrada->Split(',')[5])<=0){
						Puntos->Add(gcnew Punto3D());
						Puntos[Puntos->Count - 1]->CalculateCoordinates(0, 0, 0, 0, 0, 0);
					}
					else {
						//Puntos->Add(gcnew Punto3D(Convert::ToDouble(entrada->Split(',')[2]), Convert::ToDouble(entrada->Split(',')[3]), Convert::ToDouble(entrada->Split(',')[4])));
						Puntos->Add(gcnew Punto3D(Convert::ToDouble(entrada->Split(',')[5]), Convert::ToDouble(entrada->Split(',')[6]), Convert::ToDouble(entrada->Split(',')[1]), Convert::ToDouble(entrada->Split(',')[7]), Convert::ToDouble(entrada->Split(',')[0])));
						Puntos[Puntos->Count - 1]->CalculateCoordinates(0, 0, 0, 0, 0, 0);
					}
				}
				else break;
			}
		}
		frame++;
		
		newFrame = true;
		Console::WriteLine(frame);
		Console::WriteLine(Puntos->Count);
		/*-------------------------------------------------------------------------------------------*/
		/*--------------------------------------Fin de lectura---------------------------------------*/
		/*-------------------------------------------------------------------------------------------*/


		/*-------------------------------------------------------------------------------------------*/
		/*--------------------------------------Tratamiento------------------------------------------*/
		/*-------------------------------------------------------------------------------------------*/
		/*Flags[FLAG_TRATAMIENTO] = false;
		Flags[FLAG_PAUSA] = false;*/
		copiarPuntos();
		if (Flags[FLAG_LOCK] && (numSelector == frame)) {
			Esperar();
		}

		/*-------------------------------------------------------------------------------------------*/
		/*--------------------------------------Fin tratamiento--------------------------------------*/
		/*-------------------------------------------------------------------------------------------*/
	}



	Esperar();
}

void DataReader::Esperar()
{
	while (Flags[FLAG_PAUSA] || (Flags[FLAG_LOCK] && frame == numSelector)) {
		//	if (Flags[FLAG_WARNING])
		//		Kill();
		Sleep(250);
	}
}

void DataReader::Kill()
{
	thread_reader->Abort();
}

void DataReader::copiarPuntos()
{
	Informar("Copiar puntos" + Puntos->Count);
	puntosController->Clear();
	puntosController->AddRange(Puntos);

	if (Flags[FLAG_OPENGL]) {
		if (puntosController->Count > 2000) {
			Dibujador->modificarPuntos(puntosController);
			Dibujador->listo = true;
		}
	}
	//Controller de colision
	if (!Flags[FLAG_TRATAMIENTO] && Flags[FLAG_ANALISYS]) {
		Flags[FLAG_WARNING] = true;
		//mensaje pantalla
	}
	Flags[FLAG_ANALIZAR] = true;
	Flags[FLAG_TRATAMIENTO] = false;
	Puntos->Clear();
}
void DataReader::Informar(String ^ Entrada)
{

	ArrayDataReader[INFORME] += "[" + DateTime::Now.ToString("HH - mm - ss") + "]" + Entrada + "\r\n";
}