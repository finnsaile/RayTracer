#include "SceneEntity.hpp"

SceneEntity::SceneEntity(Point location) : location{location} {}

SceneEntity::~SceneEntity() {}

Point SceneEntity::getLoc() const {
    return location;
}

void SceneEntity::setLoc(Vector3d location) {
    this->location = location;
}