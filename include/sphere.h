#ifndef SPHERE_H
#define SPHERE_H

#include <Eigen/Dense>
#include <algorithm>

#include "primitive_object.h"
#include "ray.h"

class Sphere : public PrimitiveObject {
 private:
  double radius_;

 public:
  Sphere(Eigen::Vector3d location, double radius, Eigen::Vector3d color,
         double alpha, std::vector<Eigen::Vector3d> k_vec);
  virtual std::tuple<std::unique_ptr<Eigen::Vector3d>, Eigen::Vector3d,
                     Eigen::Vector2f>
  GetIntersection(Ray* ray);
  virtual ~Sphere();
};

#endif