#ifndef SCENEENTITY_H
#define SCENEENTITY_H

#include <Eigen/Dense>

class SceneEntity {
   protected:
    Eigen::Vector3d position;

   public:
    SceneEntity();
    SceneEntity(Eigen::Vector3d position);
    virtual ~SceneEntity() = 0;

    Eigen::Vector3d getPosition() const;
    void setPosition(Eigen::Vector3d position);
};

#endif