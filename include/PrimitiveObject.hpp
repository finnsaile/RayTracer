#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include <eigen3/Eigen/Dense>
#include <utility>
#include <map>
#include <vector>

#include "SceneEntity.hpp"
#include "Ray.hpp"

using Eigen::Matrix4d;
using std::unique_ptr;
using std::pair;
using std::map, std::vector;
using RGB = Vector3d;

class Ray;

class PrimitiveObject : public SceneEntity {
protected:
    Matrix4d transMatrix;
    Matrix4d invTransMatrix;
    RGB color;
    double alpha;
    
    map<char, Vector3d> KMap;
public:
    PrimitiveObject(Point location, Matrix4d transMatrix, Matrix4d transMatrixInv, RGB color, double alpha,
    vector<Vector3d> KVec);
    /**
     * @brief Abstract function calculates intersection between object and ray
     * 
     * @param ray 
     * @return pair<unique_ptr<Point>, Vec> 
     */
    virtual pair<unique_ptr<Point>, Vec> getIntersection(Ray* ray) = 0; 
    RGB getColor();
    double getAlpha();

    Vector3d getK(const char);

    virtual ~PrimitiveObject() = 0;
};

#endif