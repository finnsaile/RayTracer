#include "Sphere.hpp"

#include <iostream>

using std::min;

int intercount = 0;
Sphere::Sphere(Vector3d location, double radius, RGB color, double alpha,
vector<Vector3d> KVec) : 
PrimitiveObject(location, color, alpha, KVec),
radius{radius} {}

pair<unique_ptr<Vector3d>, Vector3d> Sphere::getIntersection(Ray* ray) {
    Ray transRay = ray->getTransformedRay(Matrix4d().setIdentity());

    Vector3d C = getPosition(), S = transRay.getOri(), d = transRay.getDir();
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

    return {unique_ptr<Vector3d>(new Vector3d(p)), (p - this->getPosition()).normalized()};
}

Sphere::~Sphere() {}