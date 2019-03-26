#include <sstream>
#include <string>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/ray.h"
#include "../include/raytracer.h"


RayTracer::RayTracer(): width(640), height(480), bmp(640, 480), aadepth(1), aathreshold(0.1), ambientlight(0.2), accuracy(0.000001) {
	aspectratio = (double)width/(double)height;
}

RayTracer::RayTracer(int w, int h): width(w), height(h), bmp(w,h), aadepth(1), aathreshold(0.1), ambientlight(0.2), accuracy(0.000001) {
	aspectratio = (double)width/(double)height;
}

void RayTracer::setCamera(const Vector3f& campos, const Vector3f& look_at) {
	scene_cam = Camera(campos, look_at);
}

void RayTracer::setAntiAliasing(int aa) { aadepth = aa; }
void RayTracer::setThreshold(double t) { aathreshold = t; }
void RayTracer::setAmbientLight(double al) { ambientlight = al; }
void RayTracer::setAccuracy(double ac) { accuracy = ac; }
void RayTracer::setBackground(const Color& col) { background = col; }

int RayTracer::winningObjectIndex(std::vector<double> object_intersections) const {
	
	if (object_intersections.size() == 0) return -1;
	
	int index_of_minimum_value = 0;
	for(int i=0; i<object_intersections.size(); ++i)
		if(object_intersections.at(i) > 0 && object_intersections.at(i) < object_intersections.at(index_of_minimum_value))
			index_of_minimum_value = i;

	if(object_intersections.at(	index_of_minimum_value) < 0) return -1;

	return index_of_minimum_value;

}

Color RayTracer::getColorAt(Vector3f intersection_position, Vector3f intersecting_ray_direction, int index_of_winning_object) const
{
	Color winning_object_color = scene_objects.at(index_of_winning_object)->getColor();
	Vector3f winning_object_normal = scene_objects.at(index_of_winning_object)->getNormalAt(intersection_position);
	
	if(winning_object_color.getS() == 2) {
		//checkered tile floor pattern

		int square = (int)floor(intersection_position.getX() + (int)floor(intersection_position.getZ()));

		if((square % 2) == 0) {
			//black tile
			winning_object_color.setR(0);
			winning_object_color.setG(0);
			winning_object_color.setB(0);
		} else {
			winning_object_color.setR(1);
			winning_object_color.setG(1);
			winning_object_color.setB(1);
		}
	}

	Color final_color = winning_object_color * ambientlight;

	if (winning_object_color.getS() > 0 && winning_object_color.getS() <= 1) {
		//reflection from objects with specular intensity
		double dot1 = winning_object_normal.Dot(intersecting_ray_direction.Negative());
		Vector3f scalar1 = winning_object_normal*dot1;
		Vector3f add1 = scalar1 + intersecting_ray_direction;
		Vector3f scalar2 = add1 * 2;
		Vector3f add2 = intersecting_ray_direction.Negative() + scalar2;
		Vector3f reflection_direction = add2.Normalised();

		Ray reflection_ray(intersection_position, reflection_direction);

		// determine what the ray intersects with first

		std::vector<double> reflection_intersections;

		for( int reflection_index = 0; reflection_index < scene_objects.size(); ++reflection_index) {
			reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
		}

		int index_of_winning_object_with_reflection = winningObjectIndex(reflection_intersections);

		if (index_of_winning_object_with_reflection != -1) {
			//reflection ray missed everthing else
			if (reflection_intersections.at(index_of_winning_object_with_reflection) > accuracy) {
				// determin the position and direction at the point of intersection with the reflection ray
				// the ray only affects the color if it reflected off something 

				Vector3f reflection_intersection_position = intersection_position + (reflection_direction * reflection_intersections.at(index_of_winning_object_with_reflection));
				Vector3f reflection_intersecting_ray_direction = reflection_direction;

				Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersecting_ray_direction, index_of_winning_object_with_reflection);
				final_color = final_color + reflection_intersection_color * winning_object_color.getS();
			}

		}

	}

	for(int light_index=0; light_index<light_sources.size(); ++light_index)
	{
		Vector3f light_direction = (light_sources.at(light_index)->getLightPosition() - intersection_position).Normalised();

		float cosine_angle = winning_object_normal.Dot(light_direction);

		if(cosine_angle > 0) {
			// test for shadows
			bool shadowed = false;

			Vector3f distance_to_light = (light_sources.at(light_index)->getLightPosition() - intersection_position);
			float distance_to_light_magnitude = distance_to_light.Length();

			Ray shadow_ray(intersection_position, (light_sources.at(light_index)->getLightPosition() - intersection_position).Normalised());

			std::vector<double> secondary_intersections;
			for(int object_index=0; object_index<scene_objects.size() && !shadowed; ++object_index) {
				secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));

			}

			for(int c=0; c<secondary_intersections.size(); ++c) {
				if(secondary_intersections.at(c)>accuracy) {
					if(secondary_intersections.at(c) <= distance_to_light_magnitude) {
						shadowed = true;
					}
					break;
				}
			}

			if(!shadowed) {
				final_color += winning_object_color * (light_sources.at(light_index)->getLightColor() * cosine_angle);

				if(winning_object_color.getS() > 0 && winning_object_color.getS() <= 1) {
					// special 0-1
					double dot1 = winning_object_normal.Dot(intersecting_ray_direction.Negative());
					Vector3f scalar1 = winning_object_normal * dot1;
					Vector3f add1 = scalar1 + intersecting_ray_direction;
					Vector3f scalar2 = add1 * 2;
					Vector3f add2 = intersecting_ray_direction.Negative() + scalar2;
					Vector3f reflection_direction = add2.Normalised();

					double specular = reflection_direction.Dot(light_direction);
					if(specular > 0) {
						specular = pow(specular, 10);
						final_color = final_color + (light_sources.at(light_index)->getLightColor() * specular * winning_object_color.getS());
					}	
				}
			}
		}

	}
	return final_color.clip();
}

void RayTracer::addLight(Source *src) {
	light_sources.push_back(src);
}

void RayTracer::addObject(Object *obj) {
	scene_objects.push_back(obj);
}

void RayTracer::render(std::string filename) {

	std::cout << "rendering ..." << std::endl;

	int aa_index;
	double xamnt, yamnt;
	// double tempRed, tempGreen, tempBlue;
	
	for(int x=0; x<width; ++x) {
		for(int y=0; y<height; ++y) {

			// start with a blank pixel
			double tempRed[aadepth * aadepth];
			double tempGreen[aadepth * aadepth];
			double tempBlue[aadepth * aadepth];

			for(int aax = 0; aax < aadepth; ++aax) {
				for(int aay = 0; aay < aadepth; ++aay) {

					aa_index = aay*aadepth + aax;
					srand(time(0));

					//create the ray from the camera to this pixel
					if(aadepth == 1) {

						// start with no anti-aliasing
						if(width > height) {
							xamnt = ((x+0.5)/width)*aspectratio - (((width - height)/(double)height/2));
							yamnt = (y + 0.5)/height;

						} else if(height > width) {
							xamnt = (x + 0.5)/width;
							yamnt = ((y + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
						} else {
							xamnt = (x + 0.5)/width;
							yamnt = (y + 0.5)/height;
						}
					} else {
						// anti-aliasing
						// start with no anti-aliasing
						if(width > height) {
							xamnt = ((x + (double)aax/((double)aadepth-1))/width)*aspectratio - (((width - height)/(double)height/2));
							yamnt = (y + (double)aax/((double)aadepth-1))/height;

						} else if(height > width) {
							xamnt = (x + (double)aax/((double)aadepth-1))/width;
							yamnt = ((y + (double)aax/((double)aadepth-1))/height)/aspectratio - (((height - width)/(double)width)/2);
						} else {
							xamnt = (x + (double)aax/((double)aadepth-1))/width;
							yamnt = (y + (double)aax/((double)aadepth-1))/height;
						}
					}

					Vector3f cam_ray_origin = scene_cam.getCameraPosition();
					Vector3f cam_ray_direction = (scene_cam.getCameraDirection() + (scene_cam.getCameraRight() * (xamnt - 0.5) + scene_cam.getCameraDown() * (yamnt - 0.5))).Normalised();

					Ray cam_ray(cam_ray_origin, cam_ray_direction);

					std::vector<double> intersections;

					for(int index=0; index<scene_objects.size(); ++index) {
						intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));
					}

					int index_of_winning_object = winningObjectIndex(intersections);

					if(index_of_winning_object == -1) {
						tempRed[aa_index] = background.getR();
						tempGreen[aa_index] = background.getG();
						tempBlue[aa_index] = background.getB();
					} else {
						if(intersections.at(index_of_winning_object) > accuracy) {
							// determine the position and direction vectors at the point of intersection

							Vector3f intersection_position = cam_ray_origin + (cam_ray_direction * intersections.at(index_of_winning_object));
							Vector3f intersecting_ray_direction = cam_ray_direction;
							Color intersection_color = getColorAt(intersection_position, intersecting_ray_direction, index_of_winning_object);

							tempRed[aa_index] = intersection_color.getR();
							tempGreen[aa_index] = intersection_color.getG();
							tempBlue[aa_index] = intersection_color.getB();
						}
					}
				}
			}

			double totalRed = 0;
			double totalGreen = 0;
			double totalBlue = 0;

			for(int iRed = 0; iRed < aadepth*aadepth; ++iRed) {
				totalRed = totalRed + tempRed[iRed];
			}
			for(int iGreen = 0; iGreen < aadepth*aadepth; ++iGreen) {
				totalGreen = totalGreen + tempGreen[iGreen];	
			}
			for(int iBlue = 0; iBlue < aadepth*aadepth; ++iBlue) {
				totalBlue = totalBlue + tempBlue[iBlue];
			}

			double avgRed = totalRed/(aadepth*aadepth);
			double avgGreen = totalGreen/(aadepth*aadepth);
			double avgBlue= totalBlue/(aadepth*aadepth);

			bmp.setPixel(x+1, y+1, 255*avgRed, 255*avgGreen, 255*avgBlue);
		}
	}

	std::ofstream outfile(filename+".bmp", std::ofstream::binary);
	outfile<<bmp;
}