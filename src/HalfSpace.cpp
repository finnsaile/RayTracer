#include "HalfSpace.hpp"

HalfSpace::HalfSpace(Point location, Vec normalVec, Matrix4d transMatrix, Matrix4d transMatrixInv, RGB color, double alpha,
vector<Vector3d> KVec) :
PrimitiveObject(location, transMatrix, transMatrixInv, color, alpha, KVec), normalVec{normalVec.normalized()} {}

pair<unique_ptr<Point>, Vector3d> HalfSpace::getIntersection(Ray* ray) {
    Ray transRay = ray->getTransformedRay(invTransMatrix);

    Vector3d D = transRay.getDir(), O = transRay.getOri(), N = normalVec, S = location;
    double DN = D.dot(N);

    if(DN == 0)
        return {nullptr, Vector3d()};
    
    double SON = (S - O).dot(N);

    double t = SON / DN;
    if(t < 0)
        return {nullptr, Vector3d()};
    
    Vector3d I = O + t * D;

    return {unique_ptr<Point>(new Point(I)), N};
}

RGB HalfSpace::getColor(Point intersection) {
    if((abs((int)intersection[0] + 1) + abs((int)intersection[2])) % 2 == 0)
        return {0, 0, 0};
    else
        return color;
}

HalfSpace::~HalfSpace() {}