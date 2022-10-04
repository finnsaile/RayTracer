#ifndef SCENEENTITY_H
#define SCENEENTITY_H

#include <eigen3/Eigen/Dense>
#include <cmath>

using std::pow, std::sqrt;
using Eigen::Vector3d;
using Point = Vector3d;

class SceneEntity {
protected:
    Point location;
public:
    SceneEntity(Point location);
    virtual ~SceneEntity() = 0;

    Point getLoc() const;
    void setLoc(Point location);
};


#endif