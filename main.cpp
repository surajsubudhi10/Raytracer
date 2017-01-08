#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <limits>
#include <algorithm>
#include <string>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Vect.h"
#include "Ray.h"
#include "Camera.h"
#include "Color.h"
#include "Light.h"
#include "Objects.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

using namespace std;

# define M_PI           3.14159265358979323846  /* pi */
# define NO_OF_FRAMES   360
# define WIDTH          1280
# define HEIGHT         720

struct RGBType
{
	double r;
	double g;
	double b;
};

void Savebmp(const char *filename, int w, int h, int dpi, RGBType *data){
	FILE *f;
	int k = w * h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi * m;

	unsigned char bmpfileheader[14] = {'B', 'M',  0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0,  1,0,24,0};

	bmpfileheader[ 2] = (unsigned char )(filesize);
	bmpfileheader[ 3] = (unsigned char )(filesize >>  8);
	bmpfileheader[ 4] = (unsigned char )(filesize >> 16);
	bmpfileheader[ 5] = (unsigned char )(filesize >> 24);

	bmpinfoheader[ 4]  = (unsigned char )(w);
	bmpinfoheader[ 5]  = (unsigned char )(w >>  8);
	bmpinfoheader[ 6]  = (unsigned char )(w >> 16);
	bmpinfoheader[ 7]  = (unsigned char )(w >> 24);

	bmpinfoheader[ 8]  = (unsigned char )(h);
	bmpinfoheader[ 9]  = (unsigned char )(h >>  8);
	bmpinfoheader[10]  = (unsigned char )(h >> 16);
	bmpinfoheader[11]  = (unsigned char )(h >> 24);

	bmpinfoheader[21]  = (unsigned char )(s);
	bmpinfoheader[22]  = (unsigned char )(s >>  8);
	bmpinfoheader[23]  = (unsigned char )(s >> 16);
	bmpinfoheader[24]  = (unsigned char )(s >> 24);

	bmpinfoheader[25]  = (unsigned char )(ppm);
	bmpinfoheader[26]  = (unsigned char )(ppm >>  8);
	bmpinfoheader[27]  = (unsigned char )(ppm >> 16);
	bmpinfoheader[28]  = (unsigned char )(ppm >> 24);

	bmpinfoheader[29]  = (unsigned char )(ppm);
	bmpinfoheader[30]  = (unsigned char )(ppm >>  8);
	bmpinfoheader[31]  = (unsigned char )(ppm >> 16);
	bmpinfoheader[32]  = (unsigned char )(ppm >> 24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for(int i = 0; i < k; i++){
		RGBType rgb = data[i];

		double red   = (data[i].r) * 255;
		double green = (data[i].g) * 255;
		double blue  = (data[i].b) * 255;

		unsigned char color[3] = {(int)floor(blue), (int)floor(green), (int)floor(red)};
		fwrite(color, 1, 3, f);
	}

	fclose(f);
}

int FrontObjectIndex(vector<double>object_intersection){

    int IndexValueOfMinValue;


    if(object_intersection.size() == 0){
        return -1;
    }
    if(object_intersection.size() == 1){
        if(object_intersection.at(0) > 0){
            return 0;
        }else{
            ///if the only index value present in the list is negative then it means ray mised the object.
            return -1;
        }
    }else{

        double max = 0;
		for (int i = 0; i < object_intersection.size(); i++) {
			if (max < object_intersection.at(i)) {
				max = object_intersection.at(i);
			}
		}
		if (max > 0) {
			for (int index = 0; index < object_intersection.size(); index++) {
				if (object_intersection.at(index) > 0 && object_intersection.at(index) <= max) {
					max = object_intersection.at(index);
					IndexValueOfMinValue = index;
				}
			}

			return IndexValueOfMinValue;
		}
		else {
			return -1;
		}

    }


}

Color GetColorAt(Vect intersection_position, Vect intersecting_ray_direction, vector<Objects*>scene_objects, vector<Source*>light_sources, int index_of_front_object, double accuracy, double ambientLight){

    Color front_object_color = scene_objects.at(index_of_front_object)->GetColor();
    Vect front_object_normal = scene_objects.at(index_of_front_object)->GetNormalAtIntersection(intersection_position);

    if(front_object_color.GetColorSpecial() == 2.0){
        int square = (int)floor(intersection_position.GetVectX()) + (int)floor(intersection_position.GetVectZ());
        if(square % 2 == 0){
            front_object_color.SetColorRed(1.0);
            front_object_color.SetColorGreen(1.0);
            front_object_color.SetColorBlue(1.0);
        }else{
            front_object_color.SetColorRed(0.0);
            front_object_color.SetColorGreen(0.0);
            front_object_color.SetColorBlue(0.0);
        }

    }

    Color finalColor = front_object_color.colorScalar(ambientLight);

    if(front_object_color.GetColorSpecial() > 0 && front_object_color.GetColorSpecial() <= 1.0){

        Vect reflectionVec = intersecting_ray_direction.VectSub(front_object_normal.VectMultScalar(2 * (intersecting_ray_direction.DotProduct(front_object_normal)))).NormalizeVect();
        Ray reflectionRay(intersection_position, reflectionVec);

        vector<double>reflection_intersections;
        for(int ref_index = 0; ref_index < scene_objects.size(); ref_index++){

            reflection_intersections.push_back(scene_objects.at(ref_index)->FindInterSection(reflectionRay));
        }

        int index_of_first_contact_of_ray = FrontObjectIndex(reflection_intersections);
        if(index_of_first_contact_of_ray != -1){
            if(reflection_intersections.at(index_of_first_contact_of_ray) > accuracy){
                Vect reflec_intersection_position = intersection_position.VectAdd(reflectionVec.VectMultScalar(reflection_intersections.at(index_of_first_contact_of_ray)));
                Vect reflec_intersection_ray_direc = reflectionVec;

                Color reflec_intersection_color = GetColorAt(reflec_intersection_position, reflec_intersection_ray_direc,scene_objects, light_sources, index_of_first_contact_of_ray,accuracy, ambientLight);

                finalColor = finalColor.colorAdd(reflec_intersection_color.colorScalar(front_object_color.GetColorSpecial()));
            }
        }
    }


    for(int i = 0; i < light_sources.size(); i++){
        Vect light_ray_direction = light_sources.at(i)->GetLightPos().VectSub(intersection_position).NormalizeVect();

        float cosine_angle = front_object_normal.DotProduct(light_ray_direction);

        if(cosine_angle > 0){
            bool shadow = false;

            Vect distance_to_light = light_sources.at(i)->GetLightPos().VectSub(intersection_position);
            double distance_to_light_magnitude = distance_to_light.GetMagnitude();

            /// Ray from intersection point to the light.
            Ray intersection_point_to_light(intersection_position, light_sources.at(i)->GetLightPos().VectSub(intersection_position).NormalizeVect());
            vector<double>secondary_intersection;

            /// Looping through all the scene objects for finding intersection.
            for(int object_index = 0; object_index < scene_objects.size() && shadow == false; object_index++){
                secondary_intersection.push_back(scene_objects.at(object_index)->FindInterSection(intersection_point_to_light));
            }

            for(int j = 0; j < secondary_intersection.size(); j++){
                if(secondary_intersection.at(j) > accuracy){
                    if(secondary_intersection.at(j) <= distance_to_light_magnitude){
                        shadow = true;
                    }
                    break;
                }

            }

            if(shadow == false){
                finalColor = finalColor.colorAdd(front_object_color.colorMult(light_sources.at(i)->GetColor()).colorScalar(cosine_angle));
            }

            if(front_object_color.GetColorSpecial() > 0 && front_object_color.GetColorSpecial() <= 1){

                double x = front_object_normal.DotProduct(intersecting_ray_direction);
                Vect scalar_one = front_object_normal.VectMultScalar(x);
                Vect add_one = scalar_one.VectAdd(intersecting_ray_direction);
                Vect scalar_two = add_one.VectMultScalar(2);
                Vect add_two = intersecting_ray_direction.Negative().VectAdd(scalar_two);
                Vect reflection_direction = add_two.NormalizeVect();

                double specular = reflection_direction.DotProduct(light_ray_direction);
                if(specular > 0){
                    specular = pow(specular, 10);
                    finalColor = finalColor.colorAdd(light_sources.at(i)->GetColor().colorScalar(specular*front_object_color.GetColorSpecial()));
                }

            }

        }
    }


    return finalColor.clipColor();
}


int thisone;

int main(int argc, char *argv[]){

	cout << "rendering.." << endl;

	clock_t t_start, t_end;

	t_start = clock();

	int width  = WIDTH;
	int height =  HEIGHT;
	double aspectRatio = (double)width / (double)height;
	int dpi    =  72;
	int n = width * height;
	RGBType *pixels = new RGBType[n];

	double accuracy = 0.00000001;

    Vect O(0, 0, 0);
	Vect X(1, 0, 0);
	Vect Y(0, 1, 0);
	Vect Z(0, 0, 1);

	int theta = 1;
	double rad = 4;

    /// Camera Data
    Vect camPos (15, 10, 0);
    for(int a = 0; a < NO_OF_FRAMES; a++){
        Vect lookAt(0, 0, 0);
        Vect diffBetween(camPos.GetVectX() - lookAt.GetVectX(), camPos.GetVectY() - lookAt.GetVectY(), camPos.GetVectZ() - lookAt.GetVectZ());

        Vect camdir = diffBetween.Negative().NormalizeVect();
        Vect camRight = Y.CrossProduct(camdir).NormalizeVect();
        Vect camDown = camRight.CrossProduct(camdir);
        Camera sceneCam (camPos, camdir, camRight, camDown);

        /// Color Data
        Color white(1.0, 1.0, 1.0, 2.0);
        Color red  (1.0, 0.0, 0.0, 0.0);
        Color green(0.0, 1.0, 0.0, 0.8);
        Color blue (0.0, 0.0, 1.0, 0.5);
        Color pink (1.0, 0.0, 1.0, 2.0);
        Color random_col (0.32, 0.56, 0.13, 0.0);
        Color black(0.0, 0.0, 0.0, 0.0);
        Color yellow(1.0, 1.0, 0.0, 0.2);

        ///Light Data
        double ambientLight = 0.2;
        Vect lightPos(7,10,-10);
        Light whiteLight(lightPos, red);
        vector<Source*>light_sources;
        light_sources.clear();
        light_sources.push_back(dynamic_cast<Source*>(&whiteLight));

        ///Scene Objects
        ///Spheres


        Vect sphere_one_pos(rad * (double)cos(M_PI * theta/180), 0, rad * (double)sin(M_PI * theta/180));
        theta += 1;
        Vect sphere_two_pos(0, 0, 0);
        //Vect sphere_three_pos(-8, 3.0, 0);

        Sphere sphere_one (sphere_one_pos, 2, green);
        Sphere sphere_two (sphere_two_pos, 1.5, yellow);
        //Sphere sphere_three (sphere_three_pos, 1, blue);

        /// Plane
        Vect plane_normal(0, 1, 0);
        Plane plane_one (Y, -1, white);

        /// Triangle
        //Triangle triangle_one(Vect(-3, 0, 2), O, Vect(-8, 3.0, 0), random_col);

        vector<Objects*>scene_objects;
        scene_objects.clear();
        scene_objects.push_back(dynamic_cast<Objects*>(&sphere_one));
        scene_objects.push_back(dynamic_cast<Objects*>(&sphere_two));
        scene_objects.push_back(dynamic_cast<Objects*>(&plane_one));
        //scene_objects.push_back(dynamic_cast<Objects*>(&sphere_three));
        //scene_objects.push_back(dynamic_cast<Objects*>(&triangle_one));




        double xAmnt, yAmnt;

        for(int i = 0; i < width; i++){
            for(int j = 0; j < height; j++){
                thisone = j*width + i;

                ///Start with no anti-aliasing
                if(width > height){
                    xAmnt = ((i + 0.5)/width)*aspectRatio - (((width - height)/(double)height)/2);
                    yAmnt = ((height - j) + 0.5)/height;
                }else if(height > width){
                    xAmnt = (i + 0.5)/width;
                    yAmnt = (((height - j) + 0.5)/height)/aspectRatio - (((height - width)/(double)width)/2);
                }else{
                    xAmnt = (i + 0.5)/width;
                    yAmnt = ((height - j) + 0.5)/height;
                }

                /// Camera Ray
                Vect camera_ray_origin = sceneCam.GetCamPos();
                Vect camera_ray_direction = sceneCam.GetCamDirection().VectAdd(sceneCam.GetCamRight().VectMultScalar(xAmnt - 0.5).VectAdd(sceneCam.GetCamDown().VectMultScalar(yAmnt - 0.5))).NormalizeVect();
                Ray cam_ray(camera_ray_origin, camera_ray_direction);

                vector<double>intersections;
                for(int index = 0; index < scene_objects.size(); index++){
                    intersections.push_back(scene_objects.at(index)->FindInterSection(cam_ray));
                }

                int index_of_front_object = FrontObjectIndex(intersections);
                ///cout << index_of_front_object;

                if(index_of_front_object == -1){
                //if((i > 270 && i < 370) && (j > 190 && j < 290)){
                    pixels[thisone].r = 0.0;
                    pixels[thisone].g = 0.0;
                    pixels[thisone].b = 0.0;
                }else{
                    if(intersections.at(index_of_front_object) > accuracy){

                        Vect intersection_position = camera_ray_origin.VectAdd(camera_ray_direction.VectMultScalar(intersections.at(index_of_front_object)));
                        Vect intersecting_ray_direction = camera_ray_direction;

                        /// Render Function
                        Color pixel_color = GetColorAt(intersection_position, intersecting_ray_direction, scene_objects, light_sources, index_of_front_object, accuracy, ambientLight);

                        pixels[thisone].r = pixel_color.GetColorRed();
                        pixels[thisone].g = pixel_color.GetColorGreen();
                        pixels[thisone].b = pixel_color.GetColorBlue();
                    }
                }
            }
        }
        int frame_num = a;
        ostringstream ss;
        ss << frame_num;
        //return ss.str();
        string new_name = ss.str() + "_name.bmp" ;
        cout << new_name << endl;
        const char *cstr = new_name.c_str();
        Savebmp(cstr, width, height, dpi, pixels);
        cout << "Image number : " << a << endl;
        cout << cos(M_PI/3) << endl;
	}

    delete pixels;
    t_end = clock();

    float totalTime = (float)t_end - (float)t_start;
    cout << "Total Render time : " << totalTime/1000 << " sec." << endl;

	return 0;
}


