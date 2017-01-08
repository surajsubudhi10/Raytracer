#ifndef _SOURCE_H
#define _SOURCE_H

#include "Color.h"
#include "Vect.h"

class Source{
	public:
		Source();
		virtual Vect GetLightPos(){ return Vect(0, 0, 0);}
		virtual Color GetColor(){ return Color(1.0, 1.0, 1.0);}

};

Source :: Source(){

}


#endif



