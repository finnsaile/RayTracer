#ifndef BOX_H
#define BOX_H

#include "primitive_object.h"

class Box : public PrimitiveObject {
 private:
  Eigen::Vector3d min_, max_;

 public:
  Box(Eigen::Vector3d min, Eigen::Vector3d max, Eigen::Vector3d color,
      double alpha, std::vector<Eigen::Vector3d> k_vec);
  /**
   * @brief Get the Eigen::Vector3d of intersection and the Normal Vector
   * at said Eigen::Vector3d between the Half Space and a give Ray.
   * Returns nullptr and the zero vector when no intersection happens
   *
   * @param ray Pointer to the ray
   * @return pair<unique_ptr<Eigen::Vector3d>, Eigen::Vector3d>
   */
  virtual std::tuple<std::unique_ptr<Eigen::Vector3d>, Eigen::Vector3d,
                     Eigen::Vector2f>
  GetIntersection(Ray* ray);
  virtual ~Box();
};

#endif