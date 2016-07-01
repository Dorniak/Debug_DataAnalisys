#include "Obstaculo.h"

#pragma region Constructor

Obstaculo::Obstaculo(const Obstaculo % copy)
{
	North = copy.North;
	South = copy.South;
	East = copy.East;
	West = copy.West;
	Center = copy.Center;
	Predice_Center = copy.Predice_Center;
	Direction = copy.Direction;
	Velocity = copy.Velocity;
	components = copy.components;
}

/// <summary>
/// Initializes a new instance of the <see cref="Obstaculo"/> class.
/// </summary>
Obstaculo::Obstaculo() {
	Velocity = 0;
	components = gcnew List<Punto3D^>();
	Center = gcnew Punto3D();
	North = gcnew Punto3D();
	South = gcnew Punto3D();
	East = gcnew Punto3D();
	West = gcnew Punto3D();
	Closer = gcnew Punto3D();
	Farthest = gcnew Punto3D();
	Center = gcnew Punto3D();

}

#pragma endregion

#pragma region Getters Implementation

/// <summary>
/// Gets the north.
/// </summary>
/// <returns></returns>
Punto3D^ Obstaculo::getNorth() {
	return North;
}
/// <summary>
/// Gets the south.
/// </summary>
/// <returns></returns>
Punto3D^ Obstaculo::getSouth() {
	return South;
}
/// <summary>
/// Gets the east.
/// </summary>
/// <returns></returns>
Punto3D^ Obstaculo::getEast() {
	return East;
}
/// <summary>
/// Gets the west.
/// </summary>
/// <returns></returns>
Punto3D^ Obstaculo::getWest() {
	return West;
}
Punto3D ^ Obstaculo::getCloser()
{
	return Closer;
	// TODO: insert return statement here
}

//Punto3D ^ Obstaculo::getPunto1()
//{
//	return Punto1;
//}
//Punto3D ^ Obstaculo::getPunto2()
//{
//	return Punto2;
//}
//Punto3D ^ Obstaculo::getPunto3()
//{
//	return Punto3;
//}
//Punto3D ^ Obstaculo::getPunto4()
//{
//	return Punto4;
//}
//Punto3D ^ Obstaculo::getPunto5()
//{
//	return Punto5;
//}
//Punto3D ^ Obstaculo::getPunto6()
//{
//	return Punto6;
//}
//Punto3D ^ Obstaculo::getPunto7()
//{
//	return Punto7;
//}
//Punto3D ^ Obstaculo::getPunto8()
//{
//	return Punto8;
//}

Punto3D ^ Obstaculo::getFarthest()
{
	return Farthest;
	// TODO: insert return statement here
}
/// <summary>
/// Gets the velocity.
/// </summary>
/// <returns></returns>
double Obstaculo::getVelocity()
{
	return Velocity;
}
/// <summary>
/// Gets the center of the obstacle.
/// </summary>
/// <returns></returns>
Punto3D^ Obstaculo::getCenter()
{
	return Center;
}
/// <summary>
/// Gets the predict center.
/// </summary>
/// <returns></returns>
Punto3D^ Obstaculo::getPrediceCenter()
{
	return Predice_Center;
}

#pragma endregion

#pragma region Setters Implementation

/// <summary>
/// Sets the direction of the obstacle.
/// </summary>
/// <param name="Previous_Position">The previous_ position.</param>
void Obstaculo::setDirection(Punto3D^ Previous_Position)
{
	Direction = Center - Previous_Position;
}
/// <summary>
/// Sets the velocity.
/// </summary>
/// <param name="Car_velocity">The car velocity.</param>
/// <param name="Frecuency">The frecuency of the LIDAR.</param>
void Obstaculo::setVelocity(double Car_velocity, double Frecuency)
{
	/*Punto3D^ velocity_vector = gcnew Punto3D();*/
	Punto3D^ velocity_vector;
	velocity_vector->setCoordinatesY(Car_velocity);

	Velocity = (Direction*Frecuency - velocity_vector)->getModule();//m/s
																	//TODO::Calcular el modulo del vector direccion y multiplicarlo por el tiempo de barrido v a vector, direccion - v, direciona modulo/fr
}
/// <summary>
/// Sets the north.
/// </summary>
/// <param name="p">The North.</param>
void Obstaculo::setNorth(Punto3D^ p) {
	North = p;
}
/// <summary>
/// Sets the south.
/// </summary>
/// <param name="p">The South.</param>
void Obstaculo::setSouth(Punto3D^ p) {
	South = p;
}
/// <summary>
/// Sets the east.
/// </summary>
/// <param name="p">The East.</param>
void Obstaculo::setEast(Punto3D^ p) {
	East = p;
}
/// <summary>
/// Sets the west.
/// </summary>
/// <param name="p">The West.</param>
void Obstaculo::setWest(Punto3D^ p) {
	West = p;
}

#pragma endregion

#pragma region Others

/// <summary>
/// Calculates the center of the obstacle.
/// </summary>
void  Obstaculo::calculateCenter()
{
	Center->setCoordinatesX((East->getCoordinatesX() + West->getCoordinatesX()) / 2);
	Center->setCoordinatesY((East->getCoordinatesY() + West->getCoordinatesY()) / 2);
	Center->setCoordinatesZ((North->getCoordinatesZ() + South->getCoordinatesZ()) / 2);
}
/// <summary>
/// Calculates the predict center of the obstacle.
/// </summary>
void  Obstaculo::calculatePrediceCenter()
{
	Predice_Center = Direction + Center;
}
/// <summary>
/// Calculates the time to collision.
/// </summary>
void Obstaculo::calculateTimeToCollision(double vel)
{
	Punto3D^ Morro_Coche = gcnew Punto3D(0, 0, 0);
	Punto3D^ Culo_Coche = gcnew Punto3D(0, 0, 0);
	Punto3D^ Morro_Obstaculo;
	Punto3D^ Culo_Obstaculo;
	Punto3D^ Zone_in;
	Punto3D^ Zone_out;
	double car_time_in, car_time_out, obs_time_in, obs_time_out;

	if (Center->getCoordinatesX() > 0) {
		Morro_Obstaculo = West;
		Culo_Obstaculo = East;
	}
	else {
		Morro_Obstaculo = East;
		Culo_Obstaculo = West;
	}

	car_time_in = (Zone_in - Morro_Coche)->getModule() / vel;
	car_time_out = (Zone_out - Culo_Coche)->getModule() / vel;
	obs_time_in = (Zone_in - Morro_Obstaculo)->getModule() / Velocity;
	obs_time_out = (Zone_out - Culo_Obstaculo)->getModule() / Velocity;
	//TODO::Calcular el TTC a partir de la velocidad del coche y del veector direccion del obstaculo
}

void Obstaculo::prepareObstacle()
{
	double x, y, z;
	double x2 = INT_MAX, x1 = INT_MIN, y2 = INT_MAX, y1 = INT_MIN, z2 = INT_MAX, z1 = INT_MIN;
	int n = -1, s = -1, e = -1, w = -1, cl = -1, f = -1;
	for (int i = 0; i < components->Count; i++)
	{
		x = components[i]->getCoordinatesX();
		y = components[i]->getCoordinatesY();
		z = components[i]->getCoordinatesZ();
		//Punto mas alto
		if (z > z1) {
			z1 = z;
			n = i;
		}
		//Punto mas bajo
		if (z < z2) {
			z2 = z;
			s = i;
		}
		//Punto mas a la derecha
		if (x > x1) {
			x1 = x;
			e = i;
		}
		//Punto mas a la izquierda
		if (x < x2) {
			x2 = x;
			w = i;
		}
		//Punto mas lejano
		if (y > y1) {
			y1 = y;
			f = i;
		}
		//Punto mas cercano
		if (y < y2) {
			y2 = y;
			cl = i;
		}
	}

	Center->setCoordinatesX((x1 + x2) / 2);
	Center->setCoordinatesY((y1 + y2) / 2);
	Center->setCoordinatesZ((z1 + z2) / 2);
	North = components[n];
	South = components[s];
	East = components[e];
	West = components[w];
	Farthest = components[f];
	Closer = components[cl];




	////Calculo d la caja real

	////Recta1 A=A12 B=B12 C=C1
	////Recta2 A=A12 B=B12 C=C2
	////Recta3 A=A34 B=B34 C=C3
	////Recta4 A=A34 B=B34 C=C4


	//double A12 = (Farthest->getCoordinatesX() - Closer->getCoordinatesX());
	//double B12 = -(Farthest->getCoordinatesY() - Closer->getCoordinatesY());
	//double m1 = (-B12) / A12;
	//double C1 = (-West->getCoordinatesX() / m1) + West->getCoordinatesY();
	//double C2 = (-East->getCoordinatesX() / m1) + East->getCoordinatesY();


	//double A34 = (West->getCoordinatesX() - East->getCoordinatesX());
	//double B34 = -(West->getCoordinatesY() - East->getCoordinatesY());
	//double m2 = (-B34) / A34;
	//double C3 = (-Farthest->getCoordinatesX() / m2) + Farthest->getCoordinatesY();
	//double C4 = (-Closer->getCoordinatesX() / m2) + Closer->getCoordinatesY();

	////Corte de rectas 1 y 4
	//Punto1 = Corte(A12, B12, C1, A34, B34, C4);//Arriba
	//Punto1->setCoordinatesZ(North->getCoordinatesZ());
	//Punto5 = Corte(A12, B12, C1, A34, B34, C4);//Abajo
	//Punto5->setCoordinatesZ(South->getCoordinatesZ());
	////Corte de rectas 1 y 3
	//Punto2 = Corte(A12, B12, C1, A34, B34, C3);//Arriba
	//Punto2->setCoordinatesZ(North->getCoordinatesZ());
	//Punto6 = Corte(A12, B12, C1, A34, B34, C3);//Abajo
	//Punto6->setCoordinatesZ(South->getCoordinatesZ());
	////Corte de rectas 2 y 3
	//Punto3 = Corte(A12, B12, C2, A34, B34, C3);//Arriba
	//Punto3->setCoordinatesZ(North->getCoordinatesZ());
	//Punto7 = Corte(A12, B12, C2, A34, B34, C3);//Abajo
	//Punto7->setCoordinatesZ(South->getCoordinatesZ());
	////Corte de rectas 2 y 4
	//Punto4 = Corte(A12, B12, C2, A34, B34, C4);//Arriba
	//Punto4->setCoordinatesZ(North->getCoordinatesZ());
	//Punto8 = Corte(A12, B12, C2, A34, B34, C4);//Abajo
	//Punto8->setCoordinatesZ(South->getCoordinatesZ());
}
//Punto3D^ Obstaculo::Corte(double A1, double B1, double C1, double A2, double B2, double C2) {
//	double T = ((A1*B2) - (B1*A2));
//	double X = (((C1*B2) - (C2*B1)) / T);
//	double Y = (((A1*C2) - (A2*C1)) / T);
//	Punto3D^ result = gcnew Punto3D(X, Y, 0);
//	return result;
//}
#pragma endregion