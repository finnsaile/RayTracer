#ifndef SCREEN_H
#define SCREEN_H

#include <nlohmann/json.hpp>
#include "SceneEntity.hpp"

class Screen : public SceneEntity {
    friend class Scene;

   private:
    std::pair<Eigen::Vector3d, Eigen::Vector3d> screenVectors;
    Eigen::Vector3d normalVec;
    Eigen::Vector2d screenRatio;
    Eigen::Vector2i resolution;
    bool antiAliasing;

   public:
    Screen(Eigen::Vector3d position, Eigen::Vector3d normalVec,
           Eigen::Vector2d screenRatio, Eigen::Vector2i resolution,
           bool antiAliasing);

    Eigen::Vector3d getPixelPosition(const Eigen::Vector2i);
    Eigen::Vector3d getPixelPosition(const size_t i, const size_t j);
    virtual ~Screen();
};

#endif