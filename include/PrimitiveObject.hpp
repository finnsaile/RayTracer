#ifndef PRIMITIVEOBJECT_H
#define PRIMITIVEOBJECT_H

#include <Eigen/Dense>
#include <utility>
#include <map>
#include <vector>

#include "SceneEntity.hpp"
#include "Ray.hpp"

using Eigen::Matrix4d;
using std::unique_ptr;
using std::pair;
using std::map, std::vector;
using RGB = Eigen::Vector3d;

class Ray;

class PrimitiveObject : public SceneEntity {
protected:
    RGB color;
    double alpha;
    
    map<char, Eigen::Vector3d> KMap;
public:
    PrimitiveObject(Eigen::Vector3d location, RGB color, double alpha,
    vector<Eigen::Vector3d> KVec);
    /**
     * @brief Abstract function calculates intersection between object and ray
     * 
     * @param ray 
     * @return pair<unique_ptr<Eigen::Vector3d>, Eigen::Vector3d> 
     */
    virtual pair<unique_ptr<Eigen::Vector3d>, Eigen::Vector3d> getIntersection(Ray* ray) = 0; 
    RGB getColor();
    double getAlpha();

    Eigen::Vector3d getK(const char);

    virtual ~PrimitiveObject() = 0;
};

#endif