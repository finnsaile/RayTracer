#ifndef JSONSERIALIZATION_H
#define JSONSERIALIZATION_H

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include "box.h"
#include "disk.h"
#include "halfspace.h"
#include "light_source.h"
#include "screen.h"
#include "sphere.h"

namespace Eigen {
static void to_json(nlohmann::json& j, const Eigen::Vector3d& v) {
  j = {v.x(), v.y(), v.z()};
}

static void from_json(const nlohmann::json& j, Eigen::Vector3d& v) {
  v.x() = j.at(0).get<double>();
  v.y() = j.at(1).get<double>();
  v.z() = j.at(2).get<double>();
}

static void to_json(nlohmann::json& j, const Eigen::Vector2d& v) {
  j = {v.x(), v.y()};
}

static void from_json(const nlohmann::json& j, Eigen::Vector2d& v) {
  v.x() = j.at(0).get<double>();
  v.y() = j.at(1).get<double>();
}

static void to_json(nlohmann::json& j, const Eigen::Vector2i& v) {
  j = {v.x(), v.y()};
}

static void from_json(const nlohmann::json& j, Eigen::Vector2i& v) {
  v.x() = j.at(0).get<double>();
  v.y() = j.at(1).get<double>();
}
}  // namespace Eigen

template <>
struct nlohmann::adl_serializer<Screen> {
  static Screen from_json(const nlohmann::json& j) {
    Eigen::Vector3d position = j.at("pos").get<Eigen::Vector3d>();
    Eigen::Vector3d N = j.at("N").get<Eigen::Vector3d>();
    Eigen::Vector2d ratio = j.at("ratio").get<Eigen::Vector2d>();
    Eigen::Vector2i resolution = j.at("size").get<Eigen::Vector2i>();
    bool aa = j.at("aa").get<bool>();
    return {position, N, ratio, resolution, aa};
  }
};

template <>
struct nlohmann::adl_serializer<LightSource> {
  static LightSource from_json(const nlohmann::json& j) {
    Eigen::Vector3d position = j.at("pos").get<Eigen::Vector3d>();
    Eigen::Vector3d rgb = j.at("rgb").get<Eigen::Vector3d>();
    return {position, rgb};
  }
};

template <>
struct nlohmann::adl_serializer<Halfspace> {
  static Halfspace from_json(const nlohmann::json& j) {
    Eigen::Vector3d position = j.at("pos").get<Eigen::Vector3d>();
    Eigen::Vector3d rgb = j.at("rgb").get<Eigen::Vector3d>();
    Eigen::Vector3d N = j.at("N").get<Eigen::Vector3d>();
    double alpha = j.at("alpha").get<double>();

    std::vector<Eigen::Vector3d> k_vec;

    k_vec.push_back(j.at("Ka").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kd").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Ks").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kr").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kt").get<Eigen::Vector3d>());

    return {position, N, rgb, alpha, k_vec};
  }
};

template <>
struct nlohmann::adl_serializer<Disk> {
  static Disk from_json(const nlohmann::json& j) {
    Eigen::Vector3d position = j.at("pos").get<Eigen::Vector3d>();
    Eigen::Vector3d rgb = j.at("rgb").get<Eigen::Vector3d>();
    Eigen::Vector3d N = j.at("N").get<Eigen::Vector3d>();
    double alpha = j.at("alpha").get<double>();
    double radius = j.at("radius").get<double>();

    std::vector<Eigen::Vector3d> k_vec;

    k_vec.push_back(j.at("Ka").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kd").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Ks").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kr").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kt").get<Eigen::Vector3d>());

    return {position, radius, N, rgb, alpha, k_vec};
  }
};

template <>
struct nlohmann::adl_serializer<Box> {
  static Box from_json(const nlohmann::json& j) {
    Eigen::Vector3d min = j.at("min").get<Eigen::Vector3d>();
    Eigen::Vector3d max = j.at("max").get<Eigen::Vector3d>();
    Eigen::Vector3d rgb = j.at("rgb").get<Eigen::Vector3d>();
    double alpha = j.at("alpha").get<double>();

    std::vector<Eigen::Vector3d> k_vec;

    k_vec.push_back(j.at("Ka").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kd").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Ks").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kr").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kt").get<Eigen::Vector3d>());

    return {min, max, rgb, alpha, k_vec};
  }
};

template <>
struct nlohmann::adl_serializer<Sphere> {
  static Sphere from_json(const nlohmann::json& j) {
    Eigen::Vector3d position = j.at("pos").get<Eigen::Vector3d>();
    Eigen::Vector3d rgb = j.at("rgb").get<Eigen::Vector3d>();
    double alpha = j.at("alpha").get<double>();
    double radius = j.at("radius").get<double>();

    std::vector<Eigen::Vector3d> k_vec;

    k_vec.push_back(j.at("Ka").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kd").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Ks").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kr").get<Eigen::Vector3d>());
    k_vec.push_back(j.at("Kt").get<Eigen::Vector3d>());

    return {position, radius, rgb, alpha, k_vec};
  }
};
// void from_json(const json& j, std::unique_ptr<Halfspace>& ptr) {
//     ptr = std::make_unique<Halfspace>(j.get<Halfspace>());
// }
#endif