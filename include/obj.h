    #ifndef OBJ_H
#define OBJ_H
#include <vector>
#include <fstream>
#include "exceptions.h"
#include "triangle.h"


class Vertex{
public:
    double x;
    double y;
    double z;
};

class Face{
public:
    unsigned int v1;
    unsigned int v2;
    unsigned int v3;
};

class Obj{
    std::vector<Vertex> tabv;
    std::vector<Face> tabf;
    unsigned int faces;
    
public:
    double min_x, max_x, min_y, max_y, min_z, max_z;
    Obj();
    void read_file(const char* file_name);
    void show()const;
    std::vector<Triangle> getTriangles()const;
    ~Obj();
};

#endif
