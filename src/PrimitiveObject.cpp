#include "PrimitiveObject.hpp"

PrimitiveObject::PrimitiveObject(Point location, Matrix4d transMatrix, Matrix4d transMatrixInv, RGB color, double alpha,
vector<Vector3d> KVec) :
SceneEntity(location), transMatrix{transMatrix}, invTransMatrix{transMatrixInv}, color{color}, alpha{alpha} {
    char keys[] = {'a', 'd', 's', 'r', 't'};
    for(size_t i = 0; i < 5; i++) {
        KMap[keys[i]] = KVec[i];
    }
} 

RGB PrimitiveObject::getColor() {
    return color;
}

double PrimitiveObject::getAlpha() {
    return alpha;
}

Vector3d PrimitiveObject::getK(const char key) {
    auto it = KMap.find(key);
    if(it != KMap.end()) {
        return it->second;
    }
    
    return Vector3d();
}

PrimitiveObject::~PrimitiveObject() {}