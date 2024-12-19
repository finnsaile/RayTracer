#ifndef RAY_H
#define RAY_H

#include <Eigen/Dense>
#include <limits>

#include "light_intensity.h"
#include "scene.h"

class Scene;

class Ray {
 private:
  Eigen::Vector3d direction_;
  Eigen::Vector3d origin_;
  Scene* scene_;
  const size_t recursion_depth_;

 public:
  Ray(Eigen::Vector3d direction, Eigen::Vector3d origin, Scene* scene,
      const size_t recursion_depth);

  /**
   * @brief Calculates the color at the impact Eigen::Vector3d of the ray.
   * If no object is hit the ambient color is returned,
   * otherwise the object color is calculated
   *
   * @return Eigen::Vector3d
   */
  Eigen::Vector3d GetIntersectionColor();
  Eigen::Vector3d GetDir();
  Eigen::Vector3d GetOri();

  //   /**
  //    * @brief Returns a copy of the current ray after it has been
  //    * transformed by a given matrix
  //    *
  //    * @param invMatrix
  //    * @return Ray
  //    */
  //   Ray getTransformedRay(Matrix4d& invMatrix);
};

#endif