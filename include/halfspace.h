#ifndef HALFSPACE_H
#define HALFSPACE_H

#include "primitive_object.h"

class Halfspace : public PrimitiveObject {
 protected:
  Eigen::Vector3d normal_vec_;

 public:
  Halfspace(Eigen::Vector3d position, Eigen::Vector3d normal_vec,
            Eigen::Vector3d color, double alpha,
            std::vector<Eigen::Vector3d> k_vec);
  /**
   * @brief Get the Eigen::Vector3d of intersection and the Normal Vector
   * at said Eigen::Vector3d between the Half Space and a give Ray.
   * Returns nullptr and the zero vector when no intersection happens
   *
   * @param ray Pointer to the ray
   * @return pair<std::unique_ptr<Eigen::Vector3d>, Eigen::Vector3d>
   */
  virtual std::tuple<std::unique_ptr<Eigen::Vector3d>, Eigen::Vector3d,
                     Eigen::Vector2f>
  GetIntersection(Ray* ray);
  /**
   * @brief Get the Color of Half Space at certain Eigen::Vector3d
   * (usefull for chessboard)
   *
   * @param intersection
   * @return RGB
   */
  Eigen::Vector3d GetColor(Eigen::Vector3d intersection);
  virtual ~Halfspace();
};

#endif