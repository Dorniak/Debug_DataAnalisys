#include "Punto3D.h"
#define PI 3.14159265
#pragma region Constructors

Punto3D::Punto3D(const Punto3D %copy)
{
	Distance = copy.Distance;
	Obstacle = copy.Obstacle;
	Intensity = copy.Intensity;
	Azimuth = copy.Azimuth;
	Angle = copy.Angle;
	x = copy.x;
	y = copy.y;
	z = copy.z;
	frame = copy.frame;
}

Punto3D::Punto3D(double d, double i, double r, double a, long f)
{
	Distance = d;
	Intensity = i;
	Azimuth = r;
	Angle = a;
	frame = f;
	valido = true;
	Obstacle = -1;
}
Punto3D::Punto3D(double xx, double yy, double zz)
{
	x = xx;
	y = yy;
	z = zz;
	Distance = -1;
	Intensity = -1;
	Azimuth = -1;
	Angle = -1;
	frame = -1;
	valido = false;
	Obstacle = -1;
}

Punto3D::Punto3D(long f, double a)
{
	Distance = 0;
	frame = f;
	Intensity = 0;
	Azimuth = a;
	Angle = 0;
	x = 0;
	y = 0;
	z = 0;
	valido = false;
	Obstacle = -1;
}
Punto3D::Punto3D()
{
	Distance = 0;
	Intensity = 0;
	Azimuth = 0;
	Angle = 0;
	frame = -1;
	x = 0;
	y = 0;
	z = 0;
	valido = false;
	Obstacle = -1;
}

#pragma endregion

#pragma region Setters Implementations

void Punto3D::setObstacle(int Obs)
{
	Obstacle = Obs;
}

void Punto3D::setCoordinatesX(double cx)
{
	x = cx;
}

void Punto3D::setCoordinatesY(double cy)
{
	y = cy;
}

void Punto3D::setCoordinatesZ(double cz)
{
	z = cz;
}

void Punto3D::setDistance(double d) {
	Distance = d;
}

void Punto3D::setIntensity(double i)
{
	Intensity = i;
}

void Punto3D::setAzimuth(double r)
{
	Azimuth = r;
}

void Punto3D::setAngle(int channel)
{
	switch (channel % 16)
	{
	case 0: Angle = -15; break;
	case 1: Angle = 1; break;
	case 2: Angle = -13; break;
	case 3: Angle = 3; break;
	case 4: Angle = -11; break;
	case 5: Angle = 5; break;
	case 6: Angle = -9; break;
	case 7: Angle = 7; break;
	case 8: Angle = -7; break;
	case 9: Angle = 9; break;
	case 10: Angle = -5; break;
	case 11: Angle = 11; break;
	case 12: Angle = -3; break;
	case 13: Angle = 13; break;
	case 14: Angle = -1; break;
	case 15: Angle = 15; break;
	}
}

#pragma endregion

#pragma region Getters Implementation

int Punto3D::getObstacle()
{
	return  this->Obstacle;
}

double Punto3D::getCoordinatesX() {
	return  this->x;
}

double Punto3D::getCoordinatesY() {
	return this->y;
}

double Punto3D::getCoordinatesZ()
{
	return  this->z;
}

double Punto3D::getDistance()
{
	return this->Distance;
}

double Punto3D::getIntensity()
{
	return Intensity;
}

double Punto3D::getAzimuth()
{
	return Azimuth;
}

double Punto3D::getAngle()
{
	return Angle;
}

double Punto3D::getModule()
{
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

#pragma endregion

#pragma region Others Functions

String^ Punto3D::visualize()
{
	return frame + "," + Azimuth + "," + x + "," + y + "," + z + "," + Distance + "," + Intensity + "," + Angle;
}

void Punto3D::CalculateCoordinates(double xx, double yy, double zz, double pitch, double roll, double yaw)
{
	if (pitch + roll + yaw != 0) {
		pitch *= PI / 180.0;
		roll *= PI / 180.0;
		yaw *= PI / 180.0;

		double tx = (Distance * cos(Angle * PI / 180.0) * sin(Azimuth * PI / 180.0));
		double ty = (Distance * cos(Angle * PI / 180.0) * cos(Azimuth * PI / 180.0));
		double tz = (Distance * sin(Angle * PI / 180.0));

		x = (((cos(pitch)*cos(yaw))*tx) + ((cos(pitch)*sin(yaw))*ty) + ((-sin(pitch))*tz)) + xx;
		y = ((((sin(roll)*sin(pitch)*cos(yaw)) - (cos(pitch)*cos(roll)*sin(yaw)))*tx) + (((cos(pitch)*cos(roll)*cos(yaw)) + (sin(roll)*sin(pitch)*sin(yaw)))*ty) + ((sin(roll)*cos(pitch))*tz)) + yy;
		z = ((((cos(pitch)*cos(roll)*sin(pitch)*cos(yaw)) + (sin(roll)*sin(yaw)))*tx) + (((cos(pitch)*cos(roll)*sin(pitch)*sin(yaw)) - (sin(roll)*cos(yaw)))*ty) + ((cos(pitch)*cos(roll)*cos(pitch))*tz)) + zz;
	}
	else {
		x = (Distance * cos(Angle * PI / 180.0) * sin(Azimuth * PI / 180.0)) + xx;
		y = (Distance * cos(Angle * PI / 180.0) * cos(Azimuth * PI / 180.0)) + yy;
		z = (Distance * sin(Angle * PI / 180.0)) + zz;
	}
}

double Punto3D::distanceToPoint(Punto3D^ p)
{
	return (p - this)->getModule();
}
#pragma endregion

#pragma region Operators

Punto3D^ Punto3D::operator+(Punto3D^ v)
{
	Punto3D^ result = gcnew Punto3D();

	result->x = x + v->x;
	result->y = y + v->y;
	result->z = z + v->z;
	result->valido = valido;
	return result;
}
Punto3D^ Punto3D::operator*(double d)
{
	Punto3D^ result = gcnew Punto3D();

	result->x = x * d;
	result->y = y * d;
	result->z = z * d;
	result->valido = valido;
	return result;
}
Punto3D^ Punto3D::operator-(Punto3D^ v)
{
	Punto3D^ result = gcnew Punto3D();

	result->x = this->x - v->x;
	result->y = this->y - v->y;
	result->z = this->z - v->z;
	result->valido = valido;
	return result;
}
Punto3D^ Punto3D::operator=(Punto3D^ v)
{
	Punto3D^ result = gcnew Punto3D();

	result->x = v->x;
	result->y = v->y;
	result->z = v->z;
	result->Angle = v->Angle;
	result->Azimuth = v->Azimuth;
	result->Distance = v->Distance;
	result->valido = valido;
	result->frame = frame;
	return result;
}
#pragma endregion