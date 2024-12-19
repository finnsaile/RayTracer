#include "sphere.h"

#include <iostream>

using Eigen::Vector3d, Eigen::Vector2f;
using std::atan2, std::acosh;
using std::min;
using std::tuple, std::unique_ptr, std::vector;

using RGB = Eigen::Vector3d;

Sphere::Sphere(Vector3d position, double radius, RGB color, double alpha,
               vector<Vector3d> k_vec)
    : PrimitiveObject(position, color, alpha, k_vec), radius_{radius} {}

tuple<unique_ptr<Vector3d>, Vector3d, Vector2f> Sphere::GetIntersection(
    Ray* ray) {
  const Vector3d C = GetPosition(), S = ray->GetOri(), d = ray->GetDir();
  Vector3d SC = C - S;
  double dSC = d.dot(SC);

  double delta = pow(radius_, 2) + pow(dSC, 2) - pow(SC.norm(), 2);

  if (delta < 0) return {nullptr, Vector3d(), Vector2f()};

  double delta_sqrt = sqrt(delta);
  double t1 = dSC + delta_sqrt, t2 = dSC - delta_sqrt;

  if (t1 < 0) return {nullptr, Vector3d(), Vector2f()};
  Vector3d p = S + min(t1, t2) * d;
  Vector3d N = (p - C).normalized();

  Vector2f tex((1 + atan2(N.z(), N.x()) / M_PI) * 0.5, acos(N.y()) / M_PI);
  return {unique_ptr<Vector3d>(new Vector3d(p)), N, tex};
}

Sphere::~Sphere() {}