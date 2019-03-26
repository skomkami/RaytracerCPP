#ifndef VECTOR3F_H
#define VECTOR3F_H

struct Vector3f
{
    double x;
    double y;
    double z;

    Vector3f();
    Vector3f(const double &_x, const double &_y, const double &_z);
    Vector3f(const Vector3f &v);
    void setX(const double &x);
    void setY(const double &y);
    void setZ(const double &z);
    double getX()const;
    double getY()const;
    double getZ()const;
    double Length()const;
    double LengthSq()const;
    Vector3f operator+(const Vector3f &v)const;
    Vector3f operator-(const Vector3f &v)const;
    Vector3f Cross(const Vector3f &v)const;
    Vector3f operator*(double scalar)const;
    Vector3f operator/(double scalar)const;
    Vector3f Normalised()const;
    double Dot(const Vector3f &v)const;
    bool operator==(const Vector3f &v)const;
    bool operator!=(const Vector3f &v)const;
    void operator-();
    Vector3f Negative()const;
    Vector3f& operator=(const Vector3f &v);
    ~Vector3f();
};

void printVec(const Vector3f& vec);

#endif
