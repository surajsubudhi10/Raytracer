#ifndef _COLOR_H
#define _COLOR_H


class Color{
	double red, green, blue, special;

	public:

		Color();
		Color(double, double, double);
		Color(double, double, double, double);

		double GetColorRed() {return red;}
		double GetColorGreen() {return green;}
		double GetColorBlue() {return blue;}
		double GetColorSpecial() {return special;}

		double SetColorRed(double r) {red = r;}
		double SetColorGreen(double g) {green = g;}
		double SetColorBlue(double b) {blue = b;}
		double SetColorSpecial(double a) {special = a;}

        double Brightness(){
            return (red + green + blue)/3;
        }

        Color colorScalar(double scalar){
            return Color(red * scalar, green * scalar, blue * scalar, special);
        }

        Color colorAdd(Color col){
            return Color(red + col.GetColorRed(), green + col.GetColorGreen(), blue + col.GetColorBlue());
        }

        Color colorMult(Color col){
            return Color(red * col.GetColorRed(), green * col.GetColorGreen(), blue * col.GetColorBlue());
        }

        Color colorAvg(Color col){
            return Color((red + col.GetColorRed())/2, (green + col.GetColorGreen())/2, (blue + col.GetColorBlue())/2);
        }

        Color clipColor(){
            double totalColor = red + green + blue;
            double excessColor = totalColor - 3;
            if(excessColor > 0){

                red = red + excessColor*(red/totalColor);
                green = green + excessColor*(green/totalColor);
                blue = blue + excessColor*(blue/totalColor);
            }

            if(red > 1){red = 1;}
            if(green > 1){green = 1;}
            if(blue > 1){blue = 1;}
            if(red < 0){red = 0;}
            if(green < 0){green = 0;}
            if(blue < 0){blue = 0;}

            return Color(red, green, blue, special);
        }

};

Color :: Color(){
	red 	= 0.5;
	green 	= 0.5;
	blue 	= 0.5;
	special 	= 1.0;
}

Color :: Color(double r, double g, double b){
	red 	= r;
	green 	= g;
	blue 	= b;
	special 	= 0.0;
}

Color :: Color(double r, double g, double b, double a){
	red 	= r;
	green 	= g;
	blue 	= b;
	special 	= a;
}

#endif
