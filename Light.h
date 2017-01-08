#ifndef _LIGHT_H
#define _LIGHT_H

#include "Source.h"
#include "Vect.h"
#include "Color.h"

class Light : public Source{
	Vect position;
	Color lightColor;

	public:

		Light();
		Light(Vect, Color);

		Vect GetLightPos() 	{return position;	  }
		Color GetLightColor() {return lightColor;}

};

Light :: Light(){
	position = Vect(0, 0, 0);
	lightColor = Color(1, 0, 0, 0);
}

Light :: Light(Vect pos, Color col){
	position = pos;
	lightColor = col;
}

#endif
