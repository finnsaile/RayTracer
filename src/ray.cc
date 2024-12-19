#include "ray.h"

#include <iostream>

#include "box.h"
#include "halfspace.h"
#include "sphere.h"

using Eigen::Vector3d, Eigen::Vector2f;
using RGB = Eigen::Vector3d;
using std::unique_ptr, std::vector;
// used to move starting Vector3d towards ray direction to prevent colision with
// own object
#define CORRECTION 0.000001

inline Vector3d mix(const Vector3d& a, const Vector3d& b,
                    const double& mixValue) {
  return a * (1 - mixValue) + b * mixValue;
}

Ray::Ray(Vector3d direction, Vector3d origin, Scene* scene,
         const size_t recursion_depth)
    : direction_{direction.normalized()},
      origin_{origin},
      scene_{scene},
      recursion_depth_{recursion_depth + 1} {}

Vector3d Ray::GetDir() { return direction_; }

Vector3d Ray::GetOri() { return origin_; }

RGB Ray::GetIntersectionColor() {
  PrimitiveObject* closest_object = nullptr;
  unique_ptr<Vector3d> closest_intersection_point = nullptr;
  double min_d = std::numeric_limits<double>::max();
  Vector3d intersection_normal_vec;
  Vector2f texture_coordinates;

  for (auto& obj : scene_->objects_) {
    auto [P, N, tempTex] = obj->GetIntersection(this);
    if (P != nullptr) {
      double dist = Vector3d(origin_ - *P).norm();
      if (dist < min_d) {
        min_d = dist;
        closest_object = obj.get();
        closest_intersection_point = std::move(P);
        intersection_normal_vec = N.normalized();
        texture_coordinates = tempTex;
      }
    };
  }

  if (closest_object == nullptr) return *scene_->ambient_color_;

  using ULI = unique_ptr<LightIntensity>;
  vector<ULI> EVec;

  Vector3d V = origin_ - *closest_intersection_point;
  // Halfspace* halfSpaceObj = dynamic_cast<Halfspace*>(closest_object);
  // if(halfSpaceObj != NULL)
  //     EVec.push_back(ULI(new
  //     AmbientComponent(halfSpaceObj->GetColor(*closest_intersection_point),
  //     closest_object->GetLightCoefficient('a'))));
  // else
  EVec.push_back(ULI(new AmbientComponent(
      closest_object->GetColor(), closest_object->GetLightCoefficient('a'))));
  if (recursion_depth_ <= scene_->max_recursion_depth_) {
    Vector3d I = (*closest_intersection_point - origin_).normalized();
    Vector3d& N = intersection_normal_vec;
    double IN = I.dot(intersection_normal_vec);

    if (closest_object->GetLightCoefficient('r').norm() != 0) {
      Vector3d R = I - 2 * (IN * N);
      Ray reflected_ray(
          R, *closest_intersection_point + (R.normalized() * CORRECTION), scene_,
          recursion_depth_);
      EVec.push_back(
          ULI(new RefComponent(reflected_ray.GetIntersectionColor(),
                               closest_object->GetLightCoefficient('r'))));
    }

    // if(closest_object->GetLightCoefficient('t').norm() != 0) {
    //     double n = scene->refractiveIndex / closest_object->getRefi();
    //     Vector3d T = n * (I - (IN + sqrt(pow(n, 2) + pow(IN, 2) - 1)) * N);
    //     Ray refractedRay(T.normalized() , *closest_intersection_point +
    //     (T.normalized() * CORRECTION), scene, recursion_depth_);

    //     EVec.push_back(ULI(new
    //     RefComponent(refractedRay.GetIntersectionColor(),
    //     closest_object->GetLightCoefficient('t'))));
    // }
  }

  for (auto& light : scene_->light_sources_) {
    bool intersec = false;
    Vector3d light_direction = light.GetPosition() - *closest_intersection_point;
    double light_dist = light_direction.norm();
    for (auto& obj : scene_->objects_) {
      // if(obj.get() == closest_object)
      //     continue;
      Ray light_ray(light_direction,
                   *closest_intersection_point + (light_direction.normalized() * CORRECTION),
                   scene_, 0);
      unique_ptr<Vector3d> intersection = std::get<0>(obj->GetIntersection(&light_ray));
      if (intersection != nullptr &&
          (*intersection - *closest_intersection_point).norm() < light_dist) {
        intersec = true;
        break;
      }
    }
    if (!intersec) {
      unique_ptr<DiffuseComponent> dif(new DiffuseComponent(
          light.GetColor(), closest_object->GetLightCoefficient('d'),
          intersection_normal_vec, light_direction));
      if (dif->GetDotProduct() < 0) continue;
      EVec.push_back(ULI(std::move(dif)));
      unique_ptr<SpecularComponent> spec(new SpecularComponent(
          light.GetColor(), closest_object->GetLightCoefficient('s'), V,
          intersection_normal_vec, light_direction, closest_object->GetAlpha()));
      if (spec->GetDotProduct() < 0) continue;
      EVec.push_back(ULI(std::move(spec)));
    }
  }

  for (size_t i = 1; i < EVec.size(); i++) {
    (*EVec[0]) += (*EVec[i]);
  }

  auto intensity = EVec[0]->GetIntensity();
  // if (dynamic_cast<Sphere*>(closest_object)) {
  //     double scale = 80;
  //     double pattern = (fmodf(texture_coordinates.x() * scale, 1) > 0.5) ^
  //     (fmodf(texture_coordinates.y() * scale, 1) > 0.5); intensity =
  //     mix(intensity, intensity * 0.8, pattern);
  // }

  return intensity;
}

// Ray Ray::GetTransformedRay(Matrix4d& invMatrix) {
//     const Vector3d& S3 = origin, d3 = direction;
//     Vector4d S4(S3[0], S3[1], S3[2], 1);
//     Vector4d d4(d3[0], d3[1], d3[2], 0);

//     S4 = invMatrix * S4;
//     d4 = invMatrix * d4;
//     return Ray({d4[0], d4[1], d4[2]}, {S4[0], S4[1], S4[2]}, scene,
//     recursion_depth_ - 1);
// }