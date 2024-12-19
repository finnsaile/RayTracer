#ifndef SCREEN_H
#define SCREEN_H

#include <nlohmann/json.hpp>

#include "scene_entity.h"

class Screen : public SceneEntity {
  friend class Scene;

 private:
  std::pair<Eigen::Vector3d, Eigen::Vector3d> screen_vectors_;
  Eigen::Vector3d normal_vec_;
  Eigen::Vector2d screen_ratio_;
  Eigen::Vector2i resolution_;
  bool anti_aliasing_;

 public:
  Screen(Eigen::Vector3d position, Eigen::Vector3d normal_vec,
         Eigen::Vector2d screen_ratio, Eigen::Vector2i resolution,
         bool anti_aliasing);

  Eigen::Vector3d GetPixelPosition(const Eigen::Vector2i);
  Eigen::Vector3d GetPixelPosition(const size_t i, const size_t j);
  virtual ~Screen();
};

#endif