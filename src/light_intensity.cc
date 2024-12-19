#include "light_intensity.h"

#include <cmath>
#include <iostream>

using std::cout, std::endl;

using std::pow;

using Eigen::Vector3d;

using RGB = Vector3d;

LightIntensity::LightIntensity(RGB color, Vector3d reflection_coefficient)
    : color_{color / 255}, reflection_coefficient_{reflection_coefficient} {}

LightIntensity& LightIntensity::operator+=(LightIntensity& other) {
  Vector3d &l_i = light_intensity_, o_l_i = other.light_intensity_;

  l_i[0] = 1 - (1 - l_i[0]) * (1 - o_l_i[0]);
  l_i[1] = 1 - (1 - l_i[1]) * (1 - o_l_i[1]);
  l_i[2] = 1 - (1 - l_i[2]) * (1 - o_l_i[2]);

  return *this;
}

RGB LightIntensity::GetIntensity() { return light_intensity_ * 255; }

LightIntensity::~LightIntensity() {}

AmbientComponent::AmbientComponent(RGB color, Vector3d reflection_coefficient)
    : LightIntensity(color, reflection_coefficient) {
  light_intensity_ = reflection_coefficient_.cwiseProduct(color_);
}

AmbientComponent::~AmbientComponent() {}

DiffuseComponent::DiffuseComponent(RGB color, Vector3d reflection_coefficient,
                                   Vector3d normal_vec, Vector3d light_dir_vec)
    : LightIntensity(color, reflection_coefficient),
      normal_vec_{normal_vec.normalized()},
      light_dir_vec_{light_dir_vec.normalized()} {
  dot_product_ = light_dir_vec_.dot(normal_vec_);
  light_intensity_ =
      reflection_coefficient_.cwiseProduct(color_) * dot_product_;
}

double DiffuseComponent::GetDotProduct() const { return dot_product_; }

DiffuseComponent::~DiffuseComponent() {}

SpecularComponent::SpecularComponent(RGB color, Vector3d reflection_coefficient,
                                     Vector3d incoming_vec, Vector3d normal_vec,
                                     Vector3d light_dir_vec, double alpha)
    : LightIntensity(color, reflection_coefficient),
      incoming_vec_{incoming_vec.normalized()},
      alpha_{alpha} {
  light_dir_vec.normalize();
  normal_vec.normalize();
  reflection_vec_ =
      2 * (light_dir_vec.dot(normal_vec)) * normal_vec - light_dir_vec;

  dot_product_ = reflection_vec_.dot(incoming_vec_);

  light_intensity_ =
      reflection_coefficient_.cwiseProduct(color_) * pow(dot_product_, alpha_);
}

double SpecularComponent::GetDotProduct() const { return dot_product_; }

SpecularComponent::~SpecularComponent() {}

RefComponent::RefComponent(RGB color, Vector3d reflection_coefficient)
    : LightIntensity(color, reflection_coefficient) {
  light_intensity_ = reflection_coefficient_.cwiseProduct(color_);
}

RefComponent::~RefComponent() {}
