#include "SceneEntity.hpp"

using Eigen::Vector3d;

SceneEntity::SceneEntity() {}
SceneEntity::SceneEntity(Vector3d position) : position{position} {}

SceneEntity::~SceneEntity() {}

Vector3d SceneEntity::getPosition() const { return position; }

void SceneEntity::setPosition(Vector3d position) { this->position = position; }