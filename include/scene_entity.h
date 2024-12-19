#ifndef SCENEENTITY_H
#define SCENEENTITY_H

#include <Eigen/Dense>

class SceneEntity {
 protected:
  Eigen::Vector3d position_;

 public:
  SceneEntity();
  SceneEntity(Eigen::Vector3d position_);
  virtual ~SceneEntity() = 0;

  Eigen::Vector3d GetPosition() const;
  void SetPosition(Eigen::Vector3d position_);
};

#endif