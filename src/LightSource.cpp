#include "LightSource.hpp"

LightSource::LightSource(Point location, RGB lightIntensity) :
SceneEntity(location),
lightIntensity(lightIntensity) {}

RGB LightSource::getColor() {
    return lightIntensity;
}

LightSource::~LightSource() {}