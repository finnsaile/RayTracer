#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include <Eigen/Dense>
#include <map>
#include <utility>
#include <vector>

#include "ray.h"
#include "scene_entity.h"

class Ray;

class PrimitiveObject : public SceneEntity {
 protected:
  Eigen::Vector3d color_;
  double alpha_;

  std::map<char, Eigen::Vector3d> light_coefficient_map_;

 public:
  PrimitiveObject(Eigen::Vector3d location, Eigen::Vector3d color, double alpha,
                  std::vector<Eigen::Vector3d> light_coefficients);
  /**
   * @brief Abstract function calculates intersection between object and ray
   *
   * @param ray
   * @retval std::tupel<std::unique_ptr<Eigen::Vector3d>, Eigen::Vector3d,
   * Eigen::Vector2f> Returns a tripplet containing a pointer to the
   * interection point, the normal std::vector and the texture coordinate of the
   * intersection
   */
  virtual std::tuple<std::unique_ptr<Eigen::Vector3d>, Eigen::Vector3d,
                     Eigen::Vector2f>
  GetIntersection(Ray* ray) = 0;
  Eigen::Vector3d GetColor();
  double GetAlpha();

  Eigen::Vector3d GetLightCoefficient(const char);

  virtual ~PrimitiveObject() = 0;
};

#endif