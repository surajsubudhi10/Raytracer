#ifndef _RAY_H
#define _RAY_H

#include "Vect.h"

class Ray{
	Vect origin, direction;

	public:

		Ray();
		Ray(Vect, Vect);

		Vect GetOrigin() 	{return origin;	  }
		Vect GetDirection() {return direction;}
		
};

Ray :: Ray(){
	origin = Vect(0, 0, 0);
	direction = Vect(1, 0, 0);
}

Ray :: Ray(Vect orig, Vect dir){
	origin = orig;
	direction = dir;
}

#endif
