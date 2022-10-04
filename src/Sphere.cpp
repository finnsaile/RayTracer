#include "Sphere.hpp"

#include <iostream>

using std::min;

int intercount = 0;
Sphere::Sphere(Point location, double radius, Matrix4d transMatrix, Matrix4d transMatrixInv, RGB color, double alpha,
vector<Vector3d> KVec) : 
PrimitiveObject(location, transMatrix, transMatrixInv, color, alpha, KVec),
radius{radius} {}

pair<unique_ptr<Point>, Vector3d> Sphere::getIntersection(Ray* ray) {
    Ray transRay = ray->getTransformedRay(invTransMatrix);
    Vector3d C = getLoc(), S = transRay.getOri(), d = transRay.getDir();
    Vector3d SC(C - S);
    double dSC = d.dot(SC);

    double delta = pow(radius, 2) + pow(dSC, 2) - pow(SC.norm(), 2);

    if(delta < 0)
        return {nullptr, Vector3d()};

    double deltaSqrt = sqrt(delta);
    double t1 = dSC + deltaSqrt, t2 = dSC - deltaSqrt;

    if(t1 < 0)
        return {nullptr, Vector3d()};
    Vector3d p = S + min(t1, t2) * d;

    return {unique_ptr<Point>(new Point(p)), (p - getLoc()).normalized()};
}

Sphere::~Sphere() {}