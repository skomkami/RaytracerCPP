#include "../include/obj.h"
#include <iostream>
#include <sstream>

using namespace std;

Obj::Obj(): faces(0){}

void Obj::read_file(const char* file_name)
{
    fstream file;
    file.open(file_name, ios::in);
    if(!file.good()) 
        throw new Exception_file();

    stringstream ss;
    string temp;
    string line;
    double temp_double;
    unsigned temp_int;
    unsigned Vcounter=0, Fcounter=0;
    char command;
    Vertex vtemp;
    Face ftemp;
    unsigned arg_count;
    unsigned line_number=0;

    while(getline(file, line))
    {
        if(line[1]!=' ') continue;
        ss.clear();
        ss.str(line);
        arg_count=-1;
        while(ss>>temp) ++arg_count;
        ss.clear();
        ss.str(line);
        ss>>command;

        switch(command)
        {
        case 'v':
            if(arg_count!=3) throw new Exception_arg(line_number);
            ss>>temp_double;
            vtemp.x=temp_double;
            if(Vcounter==0 || vtemp.x<min_x) min_x=vtemp.x;
            if(Vcounter==0 || vtemp.x>max_x) max_x=vtemp.x;
            ss>>temp_double;
            vtemp.y=temp_double;
            if(Vcounter==0 || vtemp.y<min_y) min_y=vtemp.y;
            if(Vcounter==0 || vtemp.y>max_y) max_y=vtemp.y;
            ss>>temp_double;
            vtemp.z=temp_double;
            if(Vcounter==0 || vtemp.z<min_z) min_z=vtemp.z;
            if(Vcounter==0 || vtemp.z>max_z) max_z=vtemp.z;
            tabv.push_back(vtemp);
            ++Vcounter;
            break;
        case 'f':
            if(arg_count!=3) throw new Exception_arg(line_number);
            ss>>temp_int;
            ftemp.v1=temp_int-1;
            ss>>temp_int;
            ftemp.v2=temp_int-1;
            ss>>temp_int;
            ftemp.v3=temp_int-1;
            tabf.push_back(ftemp);
            ++Fcounter;
            break;
        default:
            continue;
        }
        ++line_number;
    }

    faces=Fcounter;
}

Obj::~Obj()
{
    tabv.clear();
    tabf.clear();
}

void Obj::show()const
{
    cout<<"faces: "<<faces<<endl;
    for(int i=0; i<100; ++i)
    {
        cout<<tabv[tabf[i].v1].x<<" "<<tabv[tabf[i].v1].y<<" "<<tabv[tabf[i].v1].z<<" ";
        cout<<tabv[tabf[i].v2].x<<" "<<tabv[tabf[i].v2].y<<" "<<tabv[tabf[i].v2].z<<" ";
        cout<<tabv[tabf[i].v3].x<<" "<<tabv[tabf[i].v3].y<<" "<<tabv[tabf[i].v3].z<<endl;
    }
}

vector<Triangle> Obj::getTriangles() const {
    vector<Triangle> vec;
    Color white(1, 1, 1, 0);
    cout<<"faces "<<faces<<endl;
    for(int i=0; i<faces; ++i)
    {
        Vector3f v1(tabv[tabf[i].v1].x, tabv[tabf[i].v1].y, tabv[tabf[i].v1].z);
        Vector3f v2(tabv[tabf[i].v2].x, tabv[tabf[i].v2].y, tabv[tabf[i].v2].z);
        Vector3f v3(tabv[tabf[i].v3].x, tabv[tabf[i].v3].y, tabv[tabf[i].v3].z);
        vec.push_back(Triangle(v1,v2,v3,white));
    }
    return vec;
}
