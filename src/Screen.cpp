#include "Screen.hpp"

#include <iostream>
#include <nlohmann/json.hpp>

using Eigen::Vector3d, Eigen::Vector2d, Eigen::Vector2i;
using nlohmann::json, nlohmann::adl_serializer;

Screen::Screen(Vector3d _position, Vector3d _normalVec, Vector2d _screenRatio,
               Vector2i _resolution, bool _antiAliasing)
    : SceneEntity(_position),
      normalVec{_normalVec},
      screenRatio{_screenRatio},
      resolution{_resolution},
      antiAliasing{_antiAliasing} {
    // calculate vectors spanning the screen plane
    const Vector3d& n = this->normalVec;
    auto& [v1, v2] = this->screenVectors;
    // As the screen can't be crooked, the y coordinate is 0. Chose x as 1 and
    // calculate z using the inverse dot product with n
    if (n.x() == 0)
        v1 = {n.z(), 0, (n.x() / n.z())};
    else
        v1 = {(n.z() / n.x()), 0, n.x()};
    // v2 has to be orthogonal to v1 and n, leaving only one option (calculated
    // with crossproduct)
    v2 = n.cross(v1);
    v2.y() = abs(v2.y());
    // normalize both vectors to the distnce between pixels
    v1 = ((this->screenRatio.x() / this->resolution.x()) / v1.norm()) * v1;
    v2 = ((this->screenRatio.y() / this->resolution.y()) / v2.norm()) * v2;
}

// returns Vector3d with pixel position at the given index
Vector3d Screen::getPixelPosition(const Eigen::Vector2i pixelIndex) {
    return this->getPixelPosition(pixelIndex.x(), pixelIndex.y());
}

// returns Vector3d with pixel position at the given index
Vector3d Screen::getPixelPosition(const size_t i, const size_t j) {
    auto& [v1, v2] = this->screenVectors;
    // calculate origin by scaling v1 and v2 with i and j and subtracting them
    // from the origin
    Vector3d pixelPos = (this->position + ((j + 0.5) * v1) - ((i + 0.5) * v2));
    return pixelPos;
}

Screen::~Screen() {}
