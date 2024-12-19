#include "scene.h"

#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <thread>

#include "box.h"
#include "disk.h"
#include "halfspace.h"
#include "json_serialization.h"
#include "sphere.h"
#include "statusbar.hpp"

using Eigen::Vector2d, Eigen::Vector3d;
using std::ifstream, std::string, std::cout, std::endl;
using std::stod;
// using vecTrans::getTransformationMatrix;
// using vecTrans::getVecFromFile;
using nlohmann::json;
using std::array, std::unique_ptr, std::vector;
using std::cos, std::sin;
using RGB = Eigen::Vector3d;
using Camera = Eigen::Vector3d;

Scene::Scene() {}

RGB Scene::CalculateColor(Vector3d pixel_position, Vector3d cam_position) {
  Vector3d output(0, 0, 0);

  Ray original_ray(pixel_position - cam_position, cam_position, this, 0);
  output += original_ray.GetIntersectionColor();

  if (!screen_->anti_aliasing_) return output;

  auto v1 = screen_->screen_vectors_.first;
  auto v2 = screen_->screen_vectors_.second;

  auto xRes = screen_->resolution_.x();
  auto yRes = screen_->resolution_.y();

  size_t counter = 1;
  for (int i = -1; i <= 1; i += 2) {
    Vector3d iLoc =
        pixel_position - ((i * ((double)xRes / 4000)) * v1) - cam_position;
    for (int j = -1; j <= 1; j += 2) {
      counter++;
      Ray temp_ray(iLoc + ((j * ((double)yRes / 4000)) * v2), cam_position,
                   this, 0);
      output += temp_ray.GetIntersectionColor();
    }
  }

  output /= counter;
  return output;
}

void Scene::CreatePicture(string picture_name) {
  // Check if all necessary Objects have been declared
  assert(screen_ != nullptr);
  assert(camera_ != nullptr);
  assert(ambient_color_ != nullptr);

  // Create output Matrix
  // unique_ptr<RGB> &ac = ambientColor;
  cv::Mat output_image(screen_->resolution_.y(), screen_->resolution_.x(),
                       CV_8UC3, cv::Scalar(0, 0, 0));

  Statusbar bar(1000, true);
  // Loop over every pixel
  for (int i = 0; i < output_image.rows; i++) {
    auto t = (double(i) / (output_image.rows - 1));
    // Vector3d col = (1 - (1 - t)) * Vector3d({255, 255, 255}) + (1 - t) *
    // Vector3d(ac->getValues());
    bar.setProgress(t * 100);
    for (int j = 0; j < output_image.cols; j++) {
      Vector3d pixel_position = screen_->GetPixelPosition(i, j);
      // Calculate vector coming from camera to current pixel
      RGB pixel_col = CalculateColor(pixel_position, *camera_);
      output_image.at<cv::Vec3b>(cv::Point(j, i)) =
          cv::Vec3b(pixel_col.z(), pixel_col.y(), pixel_col.x());
    }
  }
  imwrite(picture_name, output_image);
}

void Scene::ReadEntities(string filename) {
  ifstream file(filename);
  assert(file.is_open());
  string line;
  json data = json::parse(file);

  this->max_recursion_depth_ = data.at("max_recursion_depth").get<size_t>();

  auto camera_json = data.at("camera");
  this->camera_ =
      unique_ptr<Camera>(new Camera(camera_json.at("pos").get<Camera>()));

  auto screen_json = data.at("screen");
  this->screen_ = unique_ptr<Screen>(new Screen(screen_json.get<Screen>()));

  auto ambient_light_json = data.at("ambient_light");
  this->ambient_color_ =
      unique_ptr<RGB>(new RGB(ambient_light_json.at("rgb").get<RGB>()));

  auto light_sources_json = data.at("light_sources");
  this->light_sources_ = light_sources_json.get<vector<LightSource>>();

  auto halfspace_json = data.at("halfspaces");
  auto halfspaces = halfspace_json.get<vector<Halfspace>>();
  for (auto& halfspace : halfspaces) {
    this->objects_.push_back(std::move(std::make_unique<Halfspace>(halfspace)));
  }

  auto disk_json = data.at("disks");
  auto disks = disk_json.get<vector<Disk>>();
  for (auto& disk : disks) {
    this->objects_.push_back(std::move(std::make_unique<Disk>(disk)));
  }

  auto spheres_json = data.at("spheres");
  auto spheres = spheres_json.get<vector<Sphere>>();
  for (auto& sphere : spheres) {
    this->objects_.push_back(std::move(std::make_unique<Sphere>(sphere)));
  }

  auto boxes_json = data.at("boxes");
  auto boxes = boxes_json.get<vector<Box>>();
  for (auto& box : boxes) {
    this->objects_.push_back(std::move(std::make_unique<Box>(box)));
  }
}
