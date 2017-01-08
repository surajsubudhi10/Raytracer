#ifndef _OBJECTS_H
#define _OBJECTS_H

#include "Ray.h"
#include "Vect.h"
#include "Color.h"

class Objects{
	public:
		Objects();
		virtual Color GetColor() {return Color(0.0, 0.0, 0.0, 0.0);}
        virtual Vect GetNormalAtIntersection(Vect point){return Vect();}
        virtual double FindInterSection(Ray ray){
            return 0;
        }

};

Objects :: Objects(){

}


#endif


