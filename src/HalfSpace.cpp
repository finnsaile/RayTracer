#include "HalfSpace.hpp"

HalfSpace::HalfSpace(Vector3d position, Vector3d normalVec, RGB color,
                     double alpha, vector<Vector3d> KVec)
    : PrimitiveObject(position, color, alpha, KVec),
      normalVec{normalVec.normalized()} {}

pair<unique_ptr<Vector3d>, Vector3d> HalfSpace::getIntersection(Ray* ray) {
    Ray transRay = ray->getTransformedRay(Matrix4d().setIdentity());

    Vector3d D = transRay.getDir(), O = transRay.getOri(), N = normalVec, S = position;
    double DN = D.dot(N);

    if (DN == 0) return {nullptr, Vector3d()};

    double SON = (S - O).dot(N);

    double t = SON / DN;
    if (t < 0) return {nullptr, Vector3d()};

    Vector3d I = O + t * D;

    return {unique_ptr<Vector3d>(new Vector3d(I)), N};
}

RGB HalfSpace::getColor(Vector3d intersection) {
    if ((abs((int)intersection[0] + 1) + abs((int)intersection[2])) % 2 == 0)
        return {0, 0, 0};
    else
        return color;
}

HalfSpace::~HalfSpace() {}