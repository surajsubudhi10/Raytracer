#ifndef _TRIANGLE_H
#define _TRIANGLE_H


#include "math.h"
#include "Objects.h"
#include "Vect.h"
#include "Color.h"

class Triangle : public Objects{
	Vect point_a, point_b, point_c;
	Vect normalVect;
	double distance;
	Color triangleColor;

	public:

		Triangle();
		Triangle(Vect, Vect, Vect, Color);

		Vect GetTriangleNormal(){
                Vect ca = point_c.VectSub(point_a);
                Vect ba = point_b.VectSub(point_a);
                normalVect = ca.CrossProduct(ba).NormalizeVect();
                return normalVect;
		    }

		double GetTriangleDistance(){
                normalVect = GetTriangleNormal();
                distance = normalVect.DotProduct(point_a);
                return distance;
		    }
		Color GetColor() {
                return triangleColor;
		    }

		///Normal At intersection Point
        Vect GetNormalAtIntersection(Vect point){
                normalVect = GetTriangleNormal();
                return normalVect;
            }

        double FindInterSection(Ray ray){
                Vect ray_direction = ray.GetDirection();
                Vect ray_origin = ray.GetOrigin();

                normalVect = GetTriangleNormal();
                distance = GetTriangleDistance();

                double deno = ray_direction.DotProduct(normalVect);
                if(deno == 0){
                    ///ray direction and triangle orientation are same means both are parallel
                    return -1;
                }else{
                    Vect c = ray.GetOrigin().VectSub(normalVect.VectMultScalar(distance));
                    double num = c.DotProduct(normalVect);
                    ///double b = normalVect.DotProduct(ray.GetOrigin().VectAdd(normalVect.VectMultScalar(distance).Negative()));
                    double distance_to_triangle = -num/deno;

                    /// the point O
                    double o_x = ray_direction.VectMultScalar(distance_to_triangle).GetVectX() - ray_origin.GetVectX();
                    double o_y = ray_direction.VectMultScalar(distance_to_triangle).GetVectY() - ray_origin.GetVectY();
                    double o_z = ray_direction.VectMultScalar(distance_to_triangle).GetVectZ() - ray_origin.GetVectZ();
                    Vect point_o(o_x, o_y, o_z);

                    Vect ca = point_c.VectSub(point_a);
                    Vect oa = point_o.VectSub(point_a);
                    double test1 = (ca.CrossProduct(oa)).DotProduct(normalVect);


                    Vect ab = point_a.VectSub(point_b);
                    Vect ob = point_o.VectSub(point_b);
                    double test2 = (ab.CrossProduct(ob)).DotProduct(normalVect);


                    Vect bc = point_b.VectSub(point_c);
                    Vect oc = point_o.VectSub(point_c);
                    double test3 = (bc.CrossProduct(oc)).DotProduct(normalVect);


                    if(test1 >= 0 && test2 >= 0 && test3 >= 0){
                        /// Inside the triangle plane.
                        return distance_to_triangle;
                    }else{
                        /// Outside the triangle plane.
                        return -1;
                    }
                }
            }

};

Triangle :: Triangle(){
    point_a = Vect(1, 0, 0);
    point_b = Vect(0, 1, 0);
    point_c = Vect(0, 0, 1);

	normalVect = this->GetTriangleNormal();
	distance = this->GetTriangleDistance();
	triangleColor = Color(1.0, 0.5, 0.5, 0);
}

Triangle :: Triangle(Vect p_a, Vect p_b, Vect p_c, Color color_triangle){
	point_a = p_a;
	point_b = p_b;
	point_c = p_c;
	normalVect = this->GetTriangleNormal();
	distance = this->GetTriangleDistance();
	triangleColor = color_triangle;
}

#endif



