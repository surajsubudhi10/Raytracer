#ifndef _CAMERA_H
#define _CAMERA_H

#include "Vect.h"

class Camera{
	Vect camPosition, camDirection, camRight, camDown;

	public:

		Camera();
		Camera(Vect, Vect, Vect, Vect);

		Vect GetCamPos() {return camPosition;}
		Vect GetCamDirection() {return camDirection;}
		Vect GetCamRight() {return camRight;}
		Vect GetCamDown() {return camDown;}
};

Camera :: Camera(){
	camPosition 	= Vect(0, 0, 0);
	camDirection 	= Vect(0, 0, 1);
	camRight 		= Vect(0, 0, 0);
	camDown 		= Vect(0, 0, 0);
}

Camera :: Camera(Vect pos, Vect dir, Vect right, Vect down){
	camPosition = pos;
	camDirection = dir;
	camRight = right;
	camDown = down;
}

#endif
