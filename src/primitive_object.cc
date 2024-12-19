#include "primitive_object.h"

using Eigen::Vector3d;
using std::vector;
using RGB = Eigen::Vector3d;

PrimitiveObject::PrimitiveObject(Vector3d position, RGB color, double alpha,
                                 vector<Vector3d> k_vec)
    : SceneEntity(position), color_{color}, alpha_{alpha} {
  char keys[] = {'a', 'd', 's', 'r', 't'};
  for (int i = 0; i < 5; i++) {
    light_coefficient_map_[keys[i]] = k_vec[i];
  }
}

RGB PrimitiveObject::GetColor() { return color_; }

double PrimitiveObject::GetAlpha() { return alpha_; }

Vector3d PrimitiveObject::GetLightCoefficient(const char key) {
  auto it = light_coefficient_map_.find(key);
  if (it != light_coefficient_map_.end()) {
    return it->second;
  }

  return Vector3d();
}

PrimitiveObject::~PrimitiveObject() {}