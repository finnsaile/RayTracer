#include <Eigen/Dense>

#include "halfspace.h"

using Eigen::Vector3d, Eigen::Vector2f;
using std::tuple, std::vector, std::unique_ptr;
using RGB = Eigen::Vector3d;

Halfspace::Halfspace(Vector3d position, Vector3d normal_vec, RGB color,
                     double alpha, vector<Vector3d> k_vec)
    : PrimitiveObject(position, color, alpha, k_vec),
      normal_vec_{normal_vec.normalized()} {}

tuple<unique_ptr<Vector3d>, Vector3d, Vector2f> Halfspace::GetIntersection(
    Ray* ray) {
  Vector3d D = ray->GetDir(), O = ray->GetOri(), N = normal_vec_, S = position_;
  double DN = D.dot(N);

  if (DN == 0) return {nullptr, Vector3d(), Vector2f()};

  double SON = (S - O).dot(N);

  double t = SON / DN;
  if (t < 0) return {nullptr, Vector3d(), Vector2f()};

  Vector3d I = O + t * D;

  return {unique_ptr<Vector3d>(new Vector3d(I)), N, Vector2f()};
}

RGB Halfspace::GetColor(Vector3d intersection) {
  if ((abs((int)intersection[0] + 1) + abs((int)intersection[2])) % 2 == 0)
    return {0, 0, 0};
  else
    return color_;
}

Halfspace::~Halfspace() {}