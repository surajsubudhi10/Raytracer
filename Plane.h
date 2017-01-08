#ifndef _PLANE_H
#define _PLANE_H


#include "math.h"
#include "Objects.h"
#include "Vect.h"
#include "Color.h"

class Plane : public Objects{
	Vect normalVect;
	double distance;
	Color planeColor;

	public:

		Plane();
		Plane(Vect, double, Color);

		Vect GetPlaneNormal() 	{return normalVect;}
		double GetPlaneDistance() 	{return distance;}
		Color GetColor() {return planeColor;}

		///Normal At intersection Point
        Vect GetNormalAtIntersection(Vect point){
            return normalVect;
        }

        double FindInterSection(Ray ray){
            Vect ray_direction = ray.GetDirection();
            double deno = ray_direction.DotProduct(normalVect);
            if(deno == 0){
                ///ray direction and plane orientation are same means both are parallel
                return -1;
            }else{
                Vect c = ray.GetOrigin().VectSub(normalVect.VectMultScalar(distance));
                double num = c.DotProduct(normalVect);
                ///double b = normalVect.DotProduct(ray.GetOrigin().VectAdd(normalVect.VectMultScalar(distance).Negative()));
                return -num/deno;
            }
        }

};

Plane :: Plane(){
	normalVect = Vect(1, 0, 0);
	distance = 1.0;
	planeColor = Color(1.0, 0.5, 0.5, 0);
}

Plane :: Plane(Vect normal, double dis, Color col){
	normalVect = normal;
	distance = dis;
	planeColor = col;
}

#endif


