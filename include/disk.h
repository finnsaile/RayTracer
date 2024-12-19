#ifndef DISK_H
#define DISK_H

#include "halfspace.h"

class Disk : public Halfspace {
 private:
  double radius_;

 public:
  Disk(Eigen::Vector3d position, double radius, Eigen::Vector3d normal_vec,
       Eigen::Vector3d color, double alpha, std::vector<Eigen::Vector3d> k_vec);
  virtual std::tuple<std::unique_ptr<Eigen::Vector3d>, Eigen::Vector3d,
                     Eigen::Vector2f>
  GetIntersection(Ray* ray);
  virtual ~Disk();
};

#endif