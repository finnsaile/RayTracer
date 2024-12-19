#ifndef SCENE_H
#define SCENE_H

#include <Eigen/Dense>
#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <vector>

#include "light_source.h"
#include "primitive_object.h"
#include "ray.h"
#include "screen.h"

class PrimitiveObject;

class Scene {
  friend class Ray;

 private:
  size_t max_recursion_depth_;
  std::unique_ptr<Eigen::Vector3d> ambient_color_;
  std::vector<std::unique_ptr<PrimitiveObject>> objects_;
  std::vector<LightSource> light_sources_;
  std::unique_ptr<Eigen::Vector3d> camera_;
  std::unique_ptr<Screen> screen_;
  std::unique_ptr<double> fov_;
  /**
   * @brief Calculates the color of a Pixel,
   * given its position and the position of the Eigen::Vector3d
   *
   * @param pixel_position
   * @param cam_position
   * @return Eigen::Vector3d
   */
  Eigen::Vector3d CalculateColor(Eigen::Vector3d pixel_position,
                                 Eigen::Vector3d cam_position);
  void CalculateCameraPosition();

 public:
  Scene();

  /**
   * @brief Reads Scene entities from a given file
   * and creates member object with the gicen information
   *
   * @param file_name
   */
  void ReadEntities(std::string file_name);

  /**
   * @brief Creates a picture of the scene and outputs it to the given file name
   *
   * @param picture_name
   */
  void CreatePicture(std::string picture_name);
};

// namespace vecTrans {
// /**
//  * @brief Helperfunction that creates a transformation matrix
//  * and its inverse given on the parameters in the file
//  *
//  * @param file
//  * @return array<Eigen::Matrix4d, 2>
//  */
// std::array<Eigen::Matrix4d, 2> GetTransformationMatrix(std::ifstream& file);

// /**
//  * @brief Helperfunction that reads a line and
//  * returns a std::vector with the content given on said line
//  *
//  * @tparam T
//  * @param lineHandle
//  * @param file
//  * @return T
//  */
// template <typename T>
// T getVecFromFile(string lineHandle, ifstream& file) {
//   string line;
//   getline(file, line);
//   if (line.find(lineHandle) == string::npos)
//     throw std::runtime_error("Can't find handle: " + lineHandle +
//                              " in line: " + line);

//   line = line.substr(line.find(" ") + 1);
//   T output;
//   int index;
//   for (int i = 0; i < output.size(); i++) {
//     index = line.find(" ");
//     output[i] = stod(line.substr(0, index));
//     line = line.substr(index + 1);
//   }
//   return output;
// }

// }  // namespace vecTrans

#endif