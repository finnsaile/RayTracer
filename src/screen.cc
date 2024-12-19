#include "screen.h"

#include <iostream>
#include <nlohmann/json.hpp>

using Eigen::Vector3d, Eigen::Vector2d, Eigen::Vector2i;
using nlohmann::json, nlohmann::adl_serializer;

Screen::Screen(Vector3d position, Vector3d normal_vec, Vector2d screen_ratio,
               Vector2i resolution, bool anti_aliasing)
    : SceneEntity(position),
      normal_vec_{normal_vec},
      screen_ratio_{screen_ratio},
      resolution_{resolution},
      anti_aliasing_{anti_aliasing} {
    // calculate vectors spanning the screen plane
    const Vector3d& n = normal_vec_;
    auto& [v1, v2] = screen_vectors_;
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
    v1 = ((screen_ratio_.x() / resolution_.x()) / v1.norm()) * v1;
    v2 = ((screen_ratio_.y() / resolution_.y()) / v2.norm()) * v2;
}

// returns Vector3d with pixel position at the given index
Vector3d Screen::GetPixelPosition(const Eigen::Vector2i pixel_index) {
    return GetPixelPosition(pixel_index.x(), pixel_index.y());
}

// returns Vector3d with pixel position at the given index
Vector3d Screen::GetPixelPosition(const size_t i, const size_t j) {
    auto& [v1, v2] = screen_vectors_;
    // calculate origin by scaling v1 and v2 with i and j and subtracting them
    // from the origin
    Vector3d pixel_pos = (position_ + ((j + 0.5) * v1) - ((i + 0.5) * v2));
    return pixel_pos;
}

Screen::~Screen() {}
