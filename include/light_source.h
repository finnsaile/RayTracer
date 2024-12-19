#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "scene_entity.h"

class LightSource : public SceneEntity {
 private:
  Eigen::Vector3d light_intensity_;

 public:
  LightSource(Eigen::Vector3d position, Eigen::Vector3d light_intensity);
  Eigen::Vector3d GetColor();
  virtual ~LightSource();
};

#endif