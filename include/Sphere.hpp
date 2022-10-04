#ifndef SPHERE_H
#define SPHERE_H

#include <algorithm>
#include <eigen3/Eigen/Dense>

#include "PrimitiveObject.hpp"
#include "Ray.hpp"

using Eigen::Matrix4d;
using std::unique_ptr;

class Sphere : public PrimitiveObject {
private:
    double radius;
public:
    Sphere(Point location, double radius, Matrix4d transMatrix, Matrix4d transMatrixInv, RGB color, double alpha,
    vector<Vector3d> KVec);
    virtual pair<unique_ptr<Point>, Vector3d> getIntersection(Ray* ray);
    virtual ~Sphere();
};

#endif