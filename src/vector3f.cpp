#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <math.h>
#include <string.h>
#include "../include/vector3f.h"

void printVec(const Vector3f &vec)
{
    std::cout<<"[ "<<vec.getX()<<", "<<vec.getY()<<", "<<vec.getZ()<<" ]"<<std::endl;
}

Vector3f::Vector3f(): x(0), y(0), z(0)
{}

Vector3f::Vector3f(const double &_x, const double &_y, const double &_z): x(_x), y(_y), z(_z)
{}

Vector3f::Vector3f(const Vector3f &v): x(v.getX()), y(v.getY()), z(v.getZ())
{}

double Vector3f::getX()const
{
    return (this->x);
}

double Vector3f::getY()const
{
    return (this->y);
}

double Vector3f::getZ()const
{
    return (this->z);
}

void Vector3f::setX(const double &x)
{
    (this->x) = x;
}

void Vector3f::setY(const double &y)
{
    (this->y) = y;
}

void Vector3f::setZ(const double &z)
{
    (this->z) = z;
}

double Vector3f::Length()const
{
    return sqrt(this->getX()*this->getX() + this->getY()*this->getY() + this->getZ()*this->getZ());
}

double Vector3f::LengthSq()const
{
    return this->getX()*this->getX() + this->getY()*this->getY() + this->getZ()*this->getZ();
}

Vector3f Vector3f::operator+(const Vector3f &v)const
{
    Vector3f vec(this->getX()+v.getX(), this->getY()+v.getY(), this->getZ()+v.getZ());
    return vec;
}

Vector3f Vector3f::operator-(const Vector3f &v)const
{
    Vector3f vec(this->getX()-v.getX(), this->getY()-v.getY(), this->getZ()-v.getZ());
    return vec;
}

Vector3f Vector3f::Cross(const Vector3f &v)const
{
    Vector3f vec(this->getY() * v.getZ() - this->getZ() * v.getY(),
    	this->getZ() * v.getX() - this->getX() * v.getZ(),
    	this->getX() * v.getY() - this->getY() * v.getX());
    return vec;
}

Vector3f Vector3f::operator*(double scalar)const
{
	Vector3f vec(this->getX()*scalar, this->getY()*scalar, this->getZ()*scalar);
    return vec;
}

Vector3f Vector3f::operator/(double scalar)const
{
    if(abs(scalar) < 0.00001)
    {
        throw -1;
    }
    else
    {
        return (*this)*(1/scalar);
    }
}

Vector3f Vector3f::Normalised()const
{
    double len = this->Length();
    Vector3f vec(this->getX()/len, this->getY()/len, this->getZ()/len);
    return vec;
}

double Vector3f::Dot(const Vector3f &v)const
{
    return (this->getX() * v.getX() + this->getY()*v.getY() + this->getZ()*v.getZ());
}

bool Vector3f::operator==(const Vector3f &v)const
{
    return (this->getX()==v.getX() && this->getY()==v.getY() && this->getZ()==v.getZ());
}

bool Vector3f::operator!=(const Vector3f &v)const
{
    return !(*this==v);
}

void Vector3f::operator-()
{
    this->setX(-this->getX());
    this->setY(-this->getY());
    this->setZ(-this->getZ());
}

Vector3f& Vector3f::operator=(const Vector3f &v)
{
    this->setX(v.getX());
    this->setY(v.getY());
    this->setZ(v.getZ());

    return *this;
}

Vector3f Vector3f::Negative()const
{
    Vector3f vec(-this->getX(), -this->getY(), -this->getZ());
    return vec;
}

Vector3f::~Vector3f()
{}