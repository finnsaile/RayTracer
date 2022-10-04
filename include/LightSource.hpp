#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "SceneEntity.hpp"

using RGB = Vector3d;

class LightSource : public SceneEntity {
private:
    RGB lightIntensity;
public:
    LightSource(Point location, RGB lightIntensity);
    RGB getColor();
    virtual ~LightSource();
};


#endif