#ifndef SPHERE_H
#define SPHERE_H

#include <algorithm>
#include <Eigen/Dense>

#include "PrimitiveObject.hpp"
#include "Ray.hpp"

using std::unique_ptr;

class Sphere : public PrimitiveObject {
private:
    double radius;
public:
    Sphere(Eigen::Vector3d location, double radius, RGB color, double alpha,
    vector<Eigen::Vector3d> KVec);
    virtual pair<unique_ptr<Eigen::Vector3d>, Eigen::Vector3d> getIntersection(Ray* ray);
    virtual ~Sphere();
};

#endif