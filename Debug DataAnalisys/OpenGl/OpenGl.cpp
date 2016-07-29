#include "OpenGl.h"
//Librerias para las listas de puntos
using namespace System;
using namespace System::Collections::Generic;

// ----------------------------------------------------------
// Prototipos de función OpenGl
// ----------------------------------------------------------
void init();
void display(void);
void keyboard(unsigned char, int, int);
void centerOnScreen();
void trabajo();
void specialKeys(int key, int x, int y);
void timerFunc(int time);
int radio1 = 3;
int radio2 = 20;
int radio3 = 50;
// ----------------------------------------------------------
// Variables globales
// ----------------------------------------------------------
//Variables de tamaño de pantalla
int window_x;
int window_y;

int hazPerspectiva = 0;

GLint ancho = 400;
GLint alto = 400;
//  variables representing the window size
int window_width = 750;
int window_height = 750;

//  variable representing the window title
char *window_title = "Visor";


void OpenGl::Informar(String ^ Entrada)
{
	//Informe += "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t[" + DateTime::Now.ToString("HH - mm - ss") + "]" + Entrada + "\r\n";
}

void OpenGl::threadconstructor()
{
	Informar("THREAD OPENGL");
	iniciarPuntos();
	iniciarObstaculos();
	int argc = 0;
	char **argv;
	glutInit(&argc, argv);
	trabajo();
	//  Start GLUT event processing loop
	glutDisplayFunc(display);
	glutMainLoop();
}

//-------------------------------------------------------------------------
//  Program Main method.
//-------------------------------------------------------------------------
OpenGl::OpenGl(cli::array<Thread^>^ Threads)
{
	try
	{
		Informe = gcnew String("");
		this->Threads = Threads;
		Informar("CONSTRUCTOR OPENGL");
		if (!ThreadDIO)
			ThreadDIO = gcnew Thread(gcnew ThreadStart(this, &OpenGl::threadconstructor));
		ThreadDIO->Start();
		this->Threads[THREAD_OPENGL] = ThreadDIO;
	}
	catch (Exception^)
	{
		//System::Windows::Forms::MessageBox::Show(e->ToString());
	}
}
void OpenGl::modificarPuntos(List<Punto3D^>^ listEntradaPuntos)
{
	Informar("MODIFICAR PUNTOS" + listEntradaPuntos->Count);
	listo = false;
	if (listEntradaPuntos->Count < puntos->Count) {
		limpiarListas(listEntradaPuntos->Count);
	}
	for (int recorridoP = 0; recorridoP < listEntradaPuntos->Count; recorridoP++) {
		puntos[recorridoP]->setCoordinatesX(listEntradaPuntos[recorridoP]->getCoordinatesX());
		puntos[recorridoP]->setCoordinatesY(listEntradaPuntos[recorridoP]->getCoordinatesY());
		puntos[recorridoP]->setCoordinatesZ(-listEntradaPuntos[recorridoP]->getCoordinatesZ());
	}
	puntosAnterior = listEntradaPuntos->Count;
}
void OpenGl::modificarObstaculos(List<Obstaculo^>^ listEntradaObstaculos)
{
	limpiarListas();
	if (!MODO_CAJA) {
		for (int recorridoO = 0; recorridoO < listEntradaObstaculos->Count; recorridoO++) {
			if (recorridoO == NUMBER_OBSTACLES)
			{
				break;
			}
			// 2*---------*3
			//	|		  |
			//	|		  |
			// 1*---------*4
			//Punto de arriba 1
			obstaculos[(9 * recorridoO)]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto1()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO)]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto1()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO)]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto1()->getCoordinatesZ());//z1
																															 //Punto de arriba 2
			obstaculos[(9 * recorridoO) + 1]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto2()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO) + 1]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto2()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 1]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto2()->getCoordinatesZ());//z1
																																 //Punto de arriba 3
			obstaculos[(9 * recorridoO) + 2]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto3()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 2]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto3()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 2]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto3()->getCoordinatesZ());//z1
																																 //Punto de arriba 4
			obstaculos[(9 * recorridoO) + 3]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto4()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 3]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto4()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO) + 3]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto4()->getCoordinatesZ());//z1
																																 //Punto de abajo 1
			obstaculos[(9 * recorridoO) + 4]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto5()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO) + 4]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto5()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO) + 4]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto5()->getCoordinatesZ());//z2
																																 //Punto de abajo 2
			obstaculos[(9 * recorridoO) + 5]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto6()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO) + 5]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto6()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 5]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto6()->getCoordinatesZ());//z2
																																 //Punto de abajo 3
			obstaculos[(9 * recorridoO) + 6]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto7()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 6]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto7()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 6]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto7()->getCoordinatesZ());//z2
																																 //Punto de abajo 4
			obstaculos[(9 * recorridoO) + 7]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getPunto8()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 7]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getPunto8()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO) + 7]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getPunto8()->getCoordinatesZ());//z2

		//Centro
		obstaculos[(9 * recorridoO) + 8]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getCenter()->getCoordinatesX());//x2
		obstaculos[(9 * recorridoO) + 8]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getCenter()->getCoordinatesY());//y1
		obstaculos[(9 * recorridoO) + 8]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getCenter()->getCoordinatesZ());//z2

		}

	}
	else {
		for (int recorridoO = 0; recorridoO < listEntradaObstaculos->Count; recorridoO++) {
			if (recorridoO == NUMBER_OBSTACLES)
			{
				break;
			}
			// 2*---------*3
			//	|		  |
			//	|		  |
			// 1*---------*4
			//Punto de arriba 1
			obstaculos[(9 * recorridoO)]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getWest()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO)]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getCloser()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO)]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getNorth()->getCoordinatesZ());//z1
																															 //Punto de arriba 2
			obstaculos[(9 * recorridoO) + 1]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getEast()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 1]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getCloser()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO) + 1]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getNorth()->getCoordinatesZ());//z1
																																 //Punto de arriba 3
			obstaculos[(9 * recorridoO) + 2]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getEast()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 2]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getFarthest()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 2]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getNorth()->getCoordinatesZ());//z1
																																 //Punto de arriba 4
			obstaculos[(9 * recorridoO) + 3]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getWest()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO) + 3]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getFarthest()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 3]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getNorth()->getCoordinatesZ());//z1
																																 //Punto de abajo 1
			obstaculos[(9 * recorridoO) + 4]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getWest()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO) + 4]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getCloser()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO) + 4]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getSouth()->getCoordinatesZ());//z2
																																 //Punto de abajo 2
			obstaculos[(9 * recorridoO) + 5]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getEast()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 5]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getCloser()->getCoordinatesY());//y2
			obstaculos[(9 * recorridoO) + 5]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getSouth()->getCoordinatesZ());//z2
																																 //Punto de abajo 3
			obstaculos[(9 * recorridoO) + 6]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getEast()->getCoordinatesX());//x1
			obstaculos[(9 * recorridoO) + 6]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getFarthest()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 6]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getSouth()->getCoordinatesZ());//z2
																																 //Punto de abajo 4
			obstaculos[(9 * recorridoO) + 7]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getWest()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO) + 7]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getFarthest()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 7]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getSouth()->getCoordinatesZ());//z2

																																 //Centro
			obstaculos[(9 * recorridoO) + 8]->setCoordinatesX(listEntradaObstaculos[recorridoO]->getCenter()->getCoordinatesX());//x2
			obstaculos[(9 * recorridoO) + 8]->setCoordinatesY(listEntradaObstaculos[recorridoO]->getCenter()->getCoordinatesY());//y1
			obstaculos[(9 * recorridoO) + 8]->setCoordinatesZ(-listEntradaObstaculos[recorridoO]->getCenter()->getCoordinatesZ());//z2

		}
	}
}
void OpenGl::iniciarPuntos()
{
	Punto3D^ a;
	for (int llenarPuntos = 0; llenarPuntos < 250000; llenarPuntos++) {
		a = gcnew Punto3D(0, 0, 0);
		puntos->Add(a);
	}
	puntosAnterior = puntos->Count;
}
void OpenGl::iniciarObstaculos()
{
	for (int llenarObstaculos = 0; llenarObstaculos < 9 * NUMBER_OBSTACLES; llenarObstaculos++) {
		obstaculos->Add(gcnew Punto3D(0, 0, 0));
	}
}
void OpenGl::limpiarListas(int a)
{
	for (int recorrerListaPuntos = a; recorrerListaPuntos < puntosAnterior; recorrerListaPuntos++) {
		puntos[recorrerListaPuntos]->setCoordinatesX(0);
		puntos[recorrerListaPuntos]->setCoordinatesY(0);
		puntos[recorrerListaPuntos]->setCoordinatesZ(0);
	}

}
void OpenGl::limpiarListas()
{
	for (int recorrerListaObstaculos = 0; recorrerListaObstaculos < obstaculos->Count; recorrerListaObstaculos++) {
		/*if (obstaculos[recorrerListaObstaculos]->getCoordinatesX() == 0 && obstaculos[recorrerListaObstaculos]->getCoordinatesY() == 0 && obstaculos[recorrerListaObstaculos]->getCoordinatesZ() == 0)
		{
		break;
		}*/
		obstaculos[recorrerListaObstaculos]->setCoordinatesX(0);
		obstaculos[recorrerListaObstaculos]->setCoordinatesY(0);
		obstaculos[recorrerListaObstaculos]->setCoordinatesZ(0);
	}
}

void trabajo()
{
	centerOnScreen();
	glutInitWindowSize(window_width, window_height);
	glutInitWindowPosition(window_x, window_y);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(window_title);
	init();
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeys);
	glutTimerFunc(2000, timerFunc, 0);
}

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init()
{
	glEnable(GL_DEPTH_TEST);
	//  Set the frame buffer clear color to black. 
	glClearColor(0.0, 0.0, 0.0, 0.0);
}
//-------------------------------------------------------------------------
//  Funcion que se encarga de meter en el buffer de pintura las dos listas
//-------------------------------------------------------------------------
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glFlush();
#pragma region Ejes
	glPointSize(2);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.6f, 0.6f);  // activamos el color rojo claro
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glColor3f(0.6f, 1.0f, 0.6f);  // activamos el color verde claro
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);
	glColor3f(0.6f, 0.6f, 1.0f);  // activamos el color azul claro
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
#pragma endregion
	glColor3f(1.0f, 1.0f, 1.0f);      // activamos el color blanco
#pragma region Circunferencias
									  //Dibuja circunferencia 3m de diametro
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);      // activamos el color rojo
	for (int i = 0; i < 360; i++) {
		float x = (float)cos(i * 2 * PI / 360);
		float y = (float)sin(i * 2 * PI / 360);
		glVertex3f(x * radio1, y * radio1, 0);
	}
	glEnd();
	//Dibuja circunferencia 20m de diametro
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.5f, 0.0f);      // activamos el color naranja
	for (int i = 0; i < 360; i++) {
		float x = (float)cos(i * 2 * PI / 360);
		float y = (float)sin(i * 2 * PI / 360);
		glVertex3f(x * radio2, y * radio2, 0);
	}
	glEnd();
	//Dibuja circunferencia 50m de diametro
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 1.0f, 0.0f);      // activamos el color verde
	for (int i = 0; i < 360; i++) {
		float x = (float)cos(i * 2 * PI / 360);
		float y = (float)sin(i * 2 * PI / 360);
		glVertex3f(x * radio3, y * radio3, 0);
	}
	glEnd();
#pragma endregion
#pragma region Conos
	//Dibuja cono de accion 3 m
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.0f, 0.0f);      // activamos el color rojo
	glVertex3f(0, 0, 0);
	for (int i = 75; i < 105; i++) {
		float x = (float)cos(i * 2 * PI / 360);
		float y = (float)sin(i * 2 * PI / 360);
		glVertex3f(x * radio1, y * radio1, 0);
	}
	glVertex3f(0, 0, 0);
	glEnd();
	//Dibuja cono de accion 20 m
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0f, 0.5f, 0.0f);      // activamos el color naranja
	glVertex3f(0, 0, 0);
	for (int i = 75; i < 105; i++) {
		float x = (float)cos(i * 2 * PI / 360);
		float y = (float)sin(i * 2 * PI / 360);
		glVertex3f(x * radio2, y * radio2, 0);
	}
	glVertex3f(0, 0, 0);
	glEnd();
	//Dibuja cono de accion 50 m
	glBegin(GL_LINE_STRIP);
	glColor3f(0.0f, 1.0f, 0.0f);      // activamos el color verde
	glVertex3f(0, 0, 0);
	for (int i = 75; i < 105; i++) {
		float x = (float)cos(i * 2 * PI / 360);
		float y = (float)sin(i * 2 * PI / 360);
		glVertex3f(x * radio3, y * radio3, 0);
	}
	glVertex3f(0, 0, 0);
	glEnd();
#pragma endregion
#pragma region Vehiculo
	glColor3f(1.0f, 1.0f, 1.0f);      // activamos el color blanco
									  //Vehiculo
	glBegin(GL_LINE_STRIP);
	glVertex3d(1, 2, 0);
	glVertex3d(1, -2, 0);
	glVertex3d(-1, -2, 0);
	glVertex3d(-1, 2, 0);
	glVertex3d(1, 2, 0);
	glEnd();


#pragma endregion
#pragma region Dibujarpuntos

	glColor3f(1.0f, 1.0f, 1.0f);      // activamos el color blanco
									  //-------------------------------------------------------------------------
									  //  Mete en el buffer la lista de puntos
									  //-------------------------------------------------------------------------
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(0.8f, 0.6f, 1.0f);  // activamos el color rojo claro
	for (int i = 0; i < OpenGl::puntos->Count; i++) {
		glVertex3d(OpenGl::puntos[i]->getCoordinatesX(), OpenGl::puntos[i]->getCoordinatesY(), OpenGl::puntos[i]->getCoordinatesZ());
	}
	glEnd();
#pragma endregion
#pragma region Dibujarobstaculos
	//-------------------------------------------------------------------------
	//  Mete en el buffer la lista de obstaculos
	//-------------------------------------------------------------------------
	glPointSize(2);
	glColor3f(1.0f, 1.0f, 1.0f);      // activamos el color blanco
	for (int j = 0; j < OpenGl::obstaculos->Count; j = j + 9) {
		//Cuadrado de arriba
		glBegin(GL_LINE_STRIP);
		glVertex3d(OpenGl::obstaculos[j]->getCoordinatesX(), OpenGl::obstaculos[j]->getCoordinatesY(), OpenGl::obstaculos[j]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 1]->getCoordinatesX(), OpenGl::obstaculos[j + 1]->getCoordinatesY(), OpenGl::obstaculos[j + 1]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 2]->getCoordinatesX(), OpenGl::obstaculos[j + 2]->getCoordinatesY(), OpenGl::obstaculos[j + 2]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 3]->getCoordinatesX(), OpenGl::obstaculos[j + 3]->getCoordinatesY(), OpenGl::obstaculos[j + 3]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j]->getCoordinatesX(), OpenGl::obstaculos[j]->getCoordinatesY(), OpenGl::obstaculos[j]->getCoordinatesZ());
		glEnd();
		//Cuadrado de abajo
		glBegin(GL_LINE_STRIP);
		glVertex3d(OpenGl::obstaculos[j + 4]->getCoordinatesX(), OpenGl::obstaculos[j + 4]->getCoordinatesY(), OpenGl::obstaculos[j + 4]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 5]->getCoordinatesX(), OpenGl::obstaculos[j + 5]->getCoordinatesY(), OpenGl::obstaculos[j + 5]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 6]->getCoordinatesX(), OpenGl::obstaculos[j + 6]->getCoordinatesY(), OpenGl::obstaculos[j + 6]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 7]->getCoordinatesX(), OpenGl::obstaculos[j + 7]->getCoordinatesY(), OpenGl::obstaculos[j + 7]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 4]->getCoordinatesX(), OpenGl::obstaculos[j + 4]->getCoordinatesY(), OpenGl::obstaculos[j + 4]->getCoordinatesZ());
		glEnd();
		//Linea vertical 1
		glBegin(GL_LINES);
		glVertex3d(OpenGl::obstaculos[j]->getCoordinatesX(), OpenGl::obstaculos[j]->getCoordinatesY(), OpenGl::obstaculos[j]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 4]->getCoordinatesX(), OpenGl::obstaculos[j + 4]->getCoordinatesY(), OpenGl::obstaculos[j + 4]->getCoordinatesZ());
		glEnd();
		//Linea vertical 2
		glBegin(GL_LINES);
		glVertex3d(OpenGl::obstaculos[j + 1]->getCoordinatesX(), OpenGl::obstaculos[j + 1]->getCoordinatesY(), OpenGl::obstaculos[j + 1]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 5]->getCoordinatesX(), OpenGl::obstaculos[j + 5]->getCoordinatesY(), OpenGl::obstaculos[j + 5]->getCoordinatesZ());
		glEnd();
		//Linea vertical 3
		glBegin(GL_LINES);
		glVertex3d(OpenGl::obstaculos[j + 2]->getCoordinatesX(), OpenGl::obstaculos[j + 2]->getCoordinatesY(), OpenGl::obstaculos[j + 2]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 6]->getCoordinatesX(), OpenGl::obstaculos[j + 6]->getCoordinatesY(), OpenGl::obstaculos[j + 6]->getCoordinatesZ());
		glEnd();
		//Linea vertical 4
		glBegin(GL_LINES);
		glVertex3d(OpenGl::obstaculos[j + 3]->getCoordinatesX(), OpenGl::obstaculos[j + 3]->getCoordinatesY(), OpenGl::obstaculos[j + 3]->getCoordinatesZ());
		glVertex3d(OpenGl::obstaculos[j + 7]->getCoordinatesX(), OpenGl::obstaculos[j + 7]->getCoordinatesY(), OpenGl::obstaculos[j + 7]->getCoordinatesZ());
		glEnd();



		glPointSize(7);
		glColor3f(1.0f, 0.0f, 0.0f);      // activamos el color blanco
		glBegin(GL_POINTS);
		glVertex3d(OpenGl::obstaculos[j + 8]->getCoordinatesX(), OpenGl::obstaculos[j + 8]->getCoordinatesY(), OpenGl::obstaculos[j + 8]->getCoordinatesZ());
		glEnd();
		glPointSize(2);
		glColor3f(1.0f, 1.0f, 1.0f);      // activamos el color blanco
	}

#pragma endregion
	glFlush();
	glutSwapBuffers();
}
//Funcion inhabilitada
void timerFunc(int time) {
	if (OpenGl::listo) {
		glutPostRedisplay();
		glFlush();
	}
	glutTimerFunc(100, timerFunc, 0);
}
//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen()
{
	window_x = (glutGet(GLUT_SCREEN_WIDTH) - window_width) / 2;
	window_y = (glutGet(GLUT_SCREEN_HEIGHT) - window_height) / 2;
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
		/*case 'p':
		case 'P':
		hazPerspectiva = 1;
		reshape(ancho, alto);
		break;

		case 'o':
		case 'O':
		hazPerspectiva = 0;
		reshape(ancho, alto);
		break;*/
	case 'h':
		printf("o = Perspectiva ortogonal");
		printf("p = perspectiva de proyeccion");
		printf("c - Toggle culling\n");
		printf("ESC = escape");
		break;
	case '5':
		glRotatef(1.0, 0., 0., 1.);
		break;
	case '6':
		glRotatef(1.0, 0., 0., -1.);
		break;
	case '7':
		glScalef(0.5, 0.5, 0.5);
		break;
	case '8':
		glScalef(2, 2, 2);
		break;
	case 'a':
		gluLookAt(-0.1, 0, 0, 0, 0, 0, 0, 1, 0);
		break;
	case 'r':
		glScalef(1.0, 1.0, 1.0);
		break;
	case '9':
		OpenGl::puntos[1]->setCoordinatesX(2);
		break;
	case 27:
		exit(0);
		break;
	case 43:
		glScalef((GLfloat)1.1, (GLfloat) 1.1, (GLfloat) 1.1);
		break;
	case 45:
		glScalef((GLfloat)0.9, (GLfloat) 0.9, (GLfloat) 0.9);
		break;
	case 32:
		glLoadIdentity();
		glScalef((GLfloat)0.05, (GLfloat) 0.05, (GLfloat) 0.05);
		break;
	}
	glutPostRedisplay();
}
void specialKeys(int key, int x, int y) {
	//glLoadIdentity();
	if (key == GLUT_KEY_RIGHT) {
		glRotatef(1, 0.0, 1.0, 0.0);
	}
	else if (key == GLUT_KEY_LEFT) {
		glRotatef(-1, 0.0, 1.0, 0.0);
	}
	else if (key == GLUT_KEY_UP)
		glRotatef(1, 1.0, 0.0, 0.0);

	else if (key == GLUT_KEY_DOWN)
		glRotatef(-1, 1.0, 0.0, 0.0);
	//  Solicitud para actualizar la pantalla
	glutPostRedisplay();
}