#include "scene_entity.h"

using Eigen::Vector3d;

SceneEntity::SceneEntity() {}
SceneEntity::SceneEntity(Vector3d position) : position_{position} {}

SceneEntity::~SceneEntity() {}

Vector3d SceneEntity::GetPosition() const { return position_; }

void SceneEntity::SetPosition(Vector3d position) { position_ = position; }