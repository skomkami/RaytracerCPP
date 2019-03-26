#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <vector>
#include "bmp.h"
#include "light.h"
#include "sphere.h"
#include "plane.h"
#include "triangle.h"
#include "camera.h"

class RayTracer
{
private:
	JiMP2::BMP bmp;
	int width, height, aadepth;
	double aathreshold, aspectratio, ambientlight, accuracy;
    Color background;
	std::vector<Object*> scene_objects;
	std::vector<Source*> light_sources;
	Camera scene_cam;
	int winningObjectIndex(std::vector<double> object_intersections) const;
	Color getColorAt(Vector3f intersection_position, Vector3f intersecting_ray_direction, int index_of_winning_object) const;
public:
    RayTracer();
    RayTracer(int w, int h);
    void setCamera(const Vector3f&, const Vector3f&);
    void setAntiAliasing(int aa);
    void setThreshold(double t);
    void setAmbientLight(double al);
    void setAccuracy(double ac);
    void setBackground(const Color& col);
    void addLight(Source *src);
    void addObject(Object *obj);
    void render(std::string filename);
};


#endif