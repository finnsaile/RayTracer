#ifndef HALFSPACE_H
#define HALFSPACE_H

#include "PrimitiveObject.hpp"

using Vec = Vector3d;

class HalfSpace : public PrimitiveObject {
private:
    Vec normalVec;
public:
    HalfSpace(Point location, Vec normalVec, Matrix4d transMatrix, Matrix4d transMatrixInv, RGB color, double alpha,
    vector<Vector3d> KVec);
    /**
     * @brief Get the Point of intersection and the Normal Vector 
     * at said Point between the Half Space and a give Ray. 
     * Returns nullptr and the zero vector when no intersection happens
     * 
     * @param ray Pointer to the ray 
     * @return pair<unique_ptr<Point>, Vector3d> 
     */
    virtual pair<unique_ptr<Point>, Vector3d> getIntersection(Ray* ray);
    /**
     * @brief Get the Color of Half Space at certain Point
     * (usefull for chessboard)
     * 
     * @param intersection 
     * @return RGB 
     */
    RGB getColor(Point intersection);
    virtual ~HalfSpace();
};

#endif