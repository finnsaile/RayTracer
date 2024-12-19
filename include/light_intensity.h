#ifndef LIGHTINTENSITY_H
#define LIGHTINTENSITY_H

#include <Eigen/Dense>

class LightIntensity {
 protected:
  Eigen::Vector3d color_;                   // Light intensity (color)
  Eigen::Vector3d reflection_coefficient_;  // reflection coefficient
  Eigen::Vector3d light_intensity_;         // light intensity
 public:
  LightIntensity(Eigen::Vector3d color, Eigen::Vector3d reflection_coefficient);

  /**
   * @brief Combines the own light intensity wiht another one
   *
   * @param other
   * @return LightIntensity&
   */
  LightIntensity& operator+=(LightIntensity& other);

  /**
   * @brief Return the light intensity in Eigen::Vector3d values from 0-255
   *
   * @return Eigen::Vector3d
   */
  Eigen::Vector3d GetIntensity();
  virtual ~LightIntensity() = 0;
};

class AmbientComponent : public LightIntensity {
 public:
  AmbientComponent(Eigen::Vector3d color,
                   Eigen::Vector3d reflection_coefficient);
  virtual ~AmbientComponent();
};

class DiffuseComponent : public LightIntensity {
 protected:
  Eigen::Vector3d normal_vec_;     // Normal Vector at Eigen::Vector3d
  Eigen::Vector3d light_dir_vec_;  // Diredction Vector towards light
  double dot_product_;

 public:
  DiffuseComponent(Eigen::Vector3d color,
                   Eigen::Vector3d reflection_coefficient,
                   Eigen::Vector3d normal_vec, Eigen::Vector3d light_dir_vec);
  double GetDotProduct() const;
  virtual ~DiffuseComponent();
};

class SpecularComponent : public LightIntensity {
 protected:
  Eigen::Vector3d incoming_vec_;    //-Incoming Vector
  Eigen::Vector3d reflection_vec_;  // Reflection Vector from Light source
  double alpha_;                    // shiny nt
  double dot_product_;

 public:
  SpecularComponent(Eigen::Vector3d color,
                    Eigen::Vector3d reflection_coefficient,
                    Eigen::Vector3d incoming_vec, Eigen::Vector3d normal_vec,
                    Eigen::Vector3d light_dir_vec, double alpha);
  double GetDotProduct() const;
  virtual ~SpecularComponent();
};

class RefComponent : public LightIntensity {
 public:
  RefComponent(Eigen::Vector3d color, Eigen::Vector3d reflection_coefficient);
  virtual ~RefComponent();
};

#endif