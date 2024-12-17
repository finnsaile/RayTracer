#include "LightSource.hpp"

LightSource::LightSource(Eigen::Vector3d location, RGB lightIntensity) :
SceneEntity(location),
lightIntensity(lightIntensity) {}

RGB LightSource::getColor() {
    return lightIntensity;
}

LightSource::~LightSource() {}