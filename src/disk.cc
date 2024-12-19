#include "disk.h"

#include <Eigen/Dense>

using Eigen::Vector3d, Eigen::Vector2f;
using std::tuple, std::vector, std::unique_ptr;
using RGB = Eigen::Vector3d;

Disk::Disk(Vector3d position, double radius, Vector3d normalVec, RGB color,
           double alpha, vector<Vector3d> k_vec)
    : Halfspace(position, normalVec, color, alpha, k_vec), radius_{radius} {}

tuple<unique_ptr<Vector3d>, Vector3d, Vector2f> Disk::GetIntersection(
    Ray* ray) {
  Vector3d p = position_;

  auto [I, N, tex] = Halfspace::GetIntersection(ray);

  if (I == nullptr) return {nullptr, N, tex};

  Vector3d v = *I - p;
  double d = v.dot(v);
  if (d >= radius_ * radius_) return {nullptr, Vector3d(), Vector2f()};
  return {std::move(I), N, Vector2f()};
}

Disk::~Disk() {}