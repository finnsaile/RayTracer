#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "SceneEntity.hpp"

using RGB = Eigen::Vector3d;

class LightSource : public SceneEntity {
private:
    RGB lightIntensity;
public:
    LightSource(Eigen::Vector3d location, RGB lightIntensity);
    RGB getColor();
    virtual ~LightSource();
};


#endif