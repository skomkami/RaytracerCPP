#include <iostream>
#include "../include/triangle.h"
#define EPSILON 0.0001

Triangle::Triangle(): A(1,0,0), B(0,1,0), C(0,0,1), color(Color(0.5, 0.5, 0.5, 0))
{
    Vector3f CA = C - A;
    Vector3f BA = B - A;
    normal = BA.Cross(CA).Normalised();
    distance = normal.Dot(A);
}

Triangle::Triangle(const Vector3f& _A, const Vector3f& _B, const Vector3f& _C, const Color& col)
: A(_A), B(_B), C(_C), color(col)
{
    Vector3f CA = C - A;
    Vector3f BA = B - A;
    normal = BA.Cross(CA).Normalised();
    distance = normal.Dot(A);
}

Triangle::~Triangle()
{}

Vector3f Triangle::getTriangleNormal() const {
    return normal;
}
double Triangle::getTriangleDistance() const {
    return distance;
}
Color Triangle::getColor() const { return color; }

Vector3f Triangle::getNormalAt(const Vector3f& point) const {
    return normal;
}

double Triangle::findIntersection(const Ray& ray) const {

    double a = ray.getDirection().Dot(normal.Negative());
    if(a==0) {
        // ray is parallel to the plane
        return -1;
    } else {
        double b = (A - ray.getOrigin()).Dot(normal.Negative());
        double distance2plane = b/a;

        Vector3f Q = ray.getDirection() * distance2plane + ray.getOrigin();
        // [CAxQA]*n >= 0
        Vector3f CA = C - A;
        Vector3f QA = Q - A;
        double test1 = (CA.Cross(QA)).Dot(normal.Negative());
        if(test1 <= 0) return -1;
        // [BCxQC]*n >= 0
        Vector3f BC = B - C;
        Vector3f QC = Q - C;
        double test2 = (BC.Cross(QC)).Dot(normal.Negative());
        if(test2 <= 0) return -1;
        // [ABxQB]*n >= 0
        Vector3f AB = A - B;
        Vector3f QB = Q - B;
        double test3 = (AB.Cross(QB)).Dot(normal.Negative());
        if(test3 <= 0) return -1;

        return b/a;
    }

}