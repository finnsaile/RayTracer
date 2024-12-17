#ifndef HALFSPACE_H
#define HALFSPACE_H

#include "PrimitiveObject.hpp"

class HalfSpace : public PrimitiveObject {
   private:
    Eigen::Vector3d normalVec;

   public:
    HalfSpace(Eigen::Vector3d position, Eigen::Vector3d normalVec, RGB color,
              double alpha, vector<Eigen::Vector3d> KVec);
    /**
     * @brief Get the Eigen::Vector3d of intersection and the Normal Vector
     * at said Eigen::Vector3d between the Half Space and a give Ray.
     * Returns nullptr and the zero vector when no intersection happens
     *
     * @param ray Pointer to the ray
     * @return pair<unique_ptr<Eigen::Vector3d>, Eigen::Vector3d>
     */
    virtual pair<unique_ptr<Eigen::Vector3d>, Eigen::Vector3d> getIntersection(
        Ray* ray);
    /**
     * @brief Get the Color of Half Space at certain Eigen::Vector3d
     * (usefull for chessboard)
     *
     * @param intersection
     * @return RGB
     */
    RGB getColor(Eigen::Vector3d intersection);
    virtual ~HalfSpace();
};

#endif