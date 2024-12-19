#include "light_source.h"

using Eigen::Vector3d;
using RGB = Eigen::Vector3d;

LightSource::LightSource(Eigen::Vector3d position, RGB light_intensity)
    : SceneEntity(position), light_intensity_(light_intensity) {}

RGB LightSource::GetColor() { return light_intensity_; }

LightSource::~LightSource() {}