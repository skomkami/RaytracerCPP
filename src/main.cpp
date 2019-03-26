#include "../include/raytracer.h"
#include "../include/obj.h"

using namespace std;

int main(int argc, char* argv[]) {
	RayTracer rt;
	const Vector3f campos(5, 5, -20);
	const Vector3f look_at(0,1,0);
	rt.setCamera(campos, look_at);
	rt.setBackground(Color(0, 0.7, 1, 0));
	
	Color white_light(1.0, 1.0, 1.0, 0);
	Color green(0.5, 1.0, 0.5, 0);
	Color maroon_special(0.5, 0.25, 0.25, 2);
	Color orange(0.94, 0.75, 0.31, 0.4);

	Vector3f light_position(-7, 10, -10);
	Light scene_light(light_position, white_light);
	rt.addLight(dynamic_cast<Source*>(&scene_light));

	// scene objects
	Plane scene_plane(Vector3f(0, 1, 0), Vector3f(0,-3.63704,0), green);
	Sphere scene_sphere(Vector3f(-10, -0.63704, 2), 3, orange);

	rt.addObject(dynamic_cast<Object*>(&scene_plane));
	rt.addObject(dynamic_cast<Object*>(&scene_sphere));
	Obj obj;
	try {
		obj.read_file(argv[1]);
	} catch (Exceptions* e) {
			e->print_exception();
	}
	
	vector<Triangle> triangles = obj.getTriangles();
	for(int i = 0; i<triangles.size(); ++i)
		rt.addObject(dynamic_cast<Object*>(&triangles[i]));

	rt.render("cow");
	
	return 0;
}
