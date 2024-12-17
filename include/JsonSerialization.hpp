#ifndef JSONSERIALIZATION_H
#define JSONSERIALIZATION_H

#include <Eigen/Dense>
#include <nlohmann/json.hpp>

#include "HalfSpace.hpp"
#include "Sphere.hpp"
#include "LightSource.hpp"
#include "Screen.hpp"

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
struct nlohmann::adl_serializer<HalfSpace> {
    static HalfSpace from_json(const nlohmann::json& j) {
        Eigen::Vector3d position = j.at("pos").get<Eigen::Vector3d>();
        Eigen::Vector3d rgb = j.at("rgb").get<Eigen::Vector3d>();
        Eigen::Vector3d N = j.at("N").get<Eigen::Vector3d>();
        double alpha = j.at("alpha").get<double>();

        std::vector<Eigen::Vector3d> KVec;

        KVec.push_back(j.at("Ka").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Kd").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Ks").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Kr").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Kt").get<Eigen::Vector3d>());

        return {position, N, rgb, alpha, KVec};
    }
};

template <>
struct nlohmann::adl_serializer<Sphere> {
    static Sphere from_json(const nlohmann::json& j) {
        Eigen::Vector3d position = j.at("pos").get<Eigen::Vector3d>();
        Eigen::Vector3d rgb = j.at("rgb").get<Eigen::Vector3d>();
        double alpha = j.at("alpha").get<double>();
        double radius = j.at("radius").get<double>();

        std::vector<Eigen::Vector3d> KVec;

        KVec.push_back(j.at("Ka").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Kd").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Ks").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Kr").get<Eigen::Vector3d>());
        KVec.push_back(j.at("Kt").get<Eigen::Vector3d>());

        return {position, radius, rgb, alpha, KVec};
    }
};
// void from_json(const json& j, std::unique_ptr<HalfSpace>& ptr) {
//     ptr = std::make_unique<HalfSpace>(j.get<HalfSpace>());
// }
#endif