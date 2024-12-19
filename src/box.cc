#include "box.h"

using Eigen::Vector3d, Eigen::Vector2f;
using std::tuple, std::vector, std::unique_ptr;
using RGB = Eigen::Vector3d;

Box::Box(Vector3d min, Vector3d max, RGB color, double alpha,
         vector<Vector3d> k_vec)
    : PrimitiveObject(min, color, alpha, k_vec), min_{min}, max_{max} {}

tuple<unique_ptr<Vector3d>, Vector3d, Vector2f> Box::GetIntersection(Ray* ray) {
  const Vector3d C = GetPosition(), S = ray->GetOri(), d = ray->GetDir();

  double tx1 = (min_.x() - S.x()) / d.x();
  double tx2 = (max_.x() - S.x()) / d.x();
  if (tx1 > tx2) std::swap(tx1, tx2);

  double ty1 = (min_.y() - S.y()) / d.y();
  double ty2 = (max_.y() - S.y()) / d.y();
  if (ty1 > ty2) std::swap(ty1, ty2);

  double tz1 = (min_.z() - S.z()) / d.z();
  double tz2 = (max_.z() - S.z()) / d.z();
  if (tz1 > tz2) std::swap(tz1, tz2);

  // Now compute tmin, tmax as before using tx1, tx2, ty1, ty2, tz1, tz2
  double tmin = tx1;
  double tmax = tx2;

  if ((tmin > ty2) || (ty1 > tmax)) return {nullptr, Vector3d(), Vector2f()};
  if (ty1 > tmin) tmin = ty1;
  if (ty2 < tmax) tmax = ty2;

  if ((tmin > tz2) || (tz1 > tmax)) return {nullptr, Vector3d(), Vector2f()};
  if (tz1 > tmin) tmin = tz1;
  if (tz2 < tmax) tmax = tz2;

  double tHit = tmin;
  // If the nearest intersection is behind the ray start, check if the other
  // intersection is in front.
  if (tHit < 0) {
    tHit = tmax;
    // If tmax is also behind the start, then no intersection in front of the
    // origin
    if (tHit < 0) {
      return {nullptr, Vector3d(), Vector2f()};
    }
  }

  Vector3d I = S + tHit * d;

  Vector3d N;
  double eps = 1e-4;

  // Determine the normal by checking which face we hit
  if (fabs(I.x() - min_.x()) < eps) {
    N = Vector3d(-1, 0, 0);
  } else if (fabs(I.x() - max_.x()) < eps) {
    N = Vector3d(1, 0, 0);
  } else if (fabs(I.y() - min_.y()) < eps) {
    N = Vector3d(0, -1, 0);
  } else if (fabs(I.y() - max_.y()) < eps) {
    N = Vector3d(0, 1, 0);
  } else if (fabs(I.z() - min_.z()) < eps) {
    N = Vector3d(0, 0, -1);
  } else if (fabs(I.z() - max_.z()) < eps) {
    N = Vector3d(0, 0, 1);
  }

  return {std::make_unique<Vector3d>(I), N, Vector2f()};
}

Box::~Box() {}
