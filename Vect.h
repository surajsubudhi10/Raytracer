#ifndef _VECT_H
#define _VECT_H

#include "math.h"

class Vect{
	double x, y, z;

	public:

		Vect();
		Vect(double, double, double);

		double GetVectX() {return x;}
		double GetVectY() {return y;}
		double GetVectZ() {return z;}

		double GetMagnitude(){
			return sqrt((x * x) + (y * y) + (z * z));
		}

		Vect NormalizeVect(){
			double mag = this->GetMagnitude();
			return Vect(x/mag, y/mag, z/mag);
		}

		Vect Negative(){
			return Vect(-x, -y, -z);
		}

		double DotProduct(Vect v){
			return ((x * v.GetVectX()) + (y * v.GetVectY()) + (z * v.GetVectZ()));
		}

		Vect CrossProduct(Vect v){
			return Vect(y*v.GetVectZ() - z*v.GetVectY(), z*v.GetVectX() - x*v.GetVectZ(), x*v.GetVectY() - y*v.GetVectX());
		}

		Vect VectAdd(Vect v){
			return Vect(x + v.GetVectX(), y + v.GetVectY(), z + v.GetVectZ());
		}

        Vect VectSub(Vect v){
			return Vect(x - v.GetVectX(), y - v.GetVectY(), z - v.GetVectZ());
		}

		Vect VectMultScalar(double scalar){
			return Vect(scalar * x, scalar * y, scalar * z);
		}

};

Vect :: Vect(){
	x = 0;
	y = 0;
	z = 0;
}

Vect :: Vect(double i, double j, double k){
	x = i;
	y = j;
	z = k;
}

#endif
