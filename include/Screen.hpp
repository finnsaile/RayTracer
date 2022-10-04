#ifndef SCREEN_H
#define SCREEN_H

#include "SceneEntity.hpp"

using Vec = Vector3d;

class Screen : public SceneEntity {
friend class Scene;
private:
    Vec v1, v2;
    const Vec normalVec;
    const double width, height;
    const size_t xRes, yRes;
    const bool antiAliasing;
public:
    Screen(Point origin, Vec normalVec, double width, double height, 
            size_t xRes, size_t yRes, bool antiAliasing);
    Point getPixelLocation(size_t i, size_t j);
    
    virtual ~Screen();
};


#endif