#pragma once
#include <math.h>
using namespace System;
using namespace std;


ref class Punto3D
{
public:
	bool valido;
	Punto3D::Punto3D(const Punto3D %copy);
#pragma region Constructors Definitions
	Punto3D(double d, double i, double r, double a, long f);
	Punto3D(double xx, double yy, double zz);
	Punto3D(long f, double a);
	Punto3D::Punto3D();
#pragma endregion

#pragma region  Setters Definitions
	void setObstacle(int Obs);
	void setCoordinatesX(double cx);
	void setCoordinatesY(double cy);
	void setCoordinatesZ(double cz);
	void setDistance(double d);
	void setIntensity(double i);
	void setAzimuth(double r);
	void setAngle(int channel);
#pragma endregion

#pragma region Getters Definitions
	int getObstacle();
	double getCoordinatesX();
	double getCoordinatesY();
	double getCoordinatesZ();
	double getDistance();
	double getIntensity();
	double getAzimuth();
	double getAngle();
	double getModule();
#pragma endregion

#pragma region Others

	Punto3D^ operator-(Punto3D^ v);
	Punto3D^ operator=(Punto3D^ v);
	Punto3D^ operator+(Punto3D^ v);
	Punto3D^ operator*(double d);
	double distanceToPoint(Punto3D^ p);
	String^ visualize();
	void CalculateCoordinates(double xx, double yy, double zz, double pitch, double roll, double yaw);
#pragma endregion

private:

#pragma region  Propierties
	int Obstacle;		// Obstacle that contains the point
	double Intensity;	// Bounced beam intensity
	double Distance;	// Distance to the point
	double Azimuth;		// Horizontal angle Y-X
	double Angle;		// Vertical angle Laser Id Z-Y
	double x;			// X coordinate of the point
	double y;			// Y coordinate of the point
	double z;			// Z coordinate of the point
	long frame;
#pragma endregion
};
