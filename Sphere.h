#ifndef _SPHERE_H
#define _SPHERE_H


#include "math.h"
#include "Objects.h"
#include "Vect.h"
#include "Color.h"

class Sphere : public Objects{
	Vect centerPos;
	double sphereRadius;
	Color sphereColor;

	public:

		Sphere();
		Sphere(Vect, double, Color);

		Vect GetSphereCenterPos() 	{return centerPos;}
		double GetSphereRadius() 	{return sphereRadius;}
		Color GetColor() {return sphereColor;}

		Vect GetNormalAtIntersection(Vect point){
            Vect normalVect = point.VectSub(centerPos).NormalizeVect();
            return normalVect;
		}

		double FindInterSection(Ray ray){
			Vect ray_origin    = ray.GetOrigin();
			double ray_originX = ray_origin.GetVectX();
			double ray_originY = ray_origin.GetVectY();
			double ray_originZ = ray_origin.GetVectZ();

			Vect ray_direction    = ray.GetDirection();
			double ray_directionX = ray_direction.GetVectX();
			double ray_directionY = ray_direction.GetVectY();
			double ray_directionZ = ray_direction.GetVectZ();

            Vect sphere_position    = centerPos;
			double sphere_positionX = sphere_position.GetVectX();
			double sphere_positionY = sphere_position.GetVectY();
			double sphere_positionZ = sphere_position.GetVectZ();

			double a = 1; //normalized
			double b = (2*(ray_originX - sphere_positionX)*ray_directionX) + (2*(ray_originY - sphere_positionY)*ray_directionY) + (2*(ray_originZ - sphere_positionZ)*ray_directionZ);
			double c = pow(ray_originX - sphere_positionX, 2) + pow(ray_originY - sphere_positionY, 2) + pow(ray_originZ - sphere_positionZ, 2) - (sphereRadius * sphereRadius);
            double discriminant = (b*b) - (4*a*c);

            if(discriminant > 0){
                // we have two intersection points
                double root_one = (-b - sqrt(discriminant))/2 - 0.000001;
                if(root_one > 0){
                    return root_one;
                }else{
                    double root_two = (sqrt(discriminant) - b)/2 - 0.000001;
                    return root_two;
                }

            }else if(discriminant = 0){
                /// Ray is a tangent to sphere
                return -b/2 - 0.000001;
            }else{
                ///Ray missed the sphere
                return -1;
            }

            return 0;
		}

};

Sphere :: Sphere(){
	centerPos = Vect(0, 0, 0);
	sphereRadius = 1.0;
	sphereColor = Color(0.5, 0.5, 0.5, 0);
}

Sphere :: Sphere(Vect pos, double rad, Color col){
	centerPos = pos;
	sphereRadius = rad;
	sphereColor = col;
}

#endif

