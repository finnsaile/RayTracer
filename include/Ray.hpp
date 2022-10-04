#ifndef RAY_H
#define RAY_H

#include <limits>
#include <eigen3/Eigen/Dense>

#include "Scene.hpp"
#include "LightIntensity.hpp"

using Eigen::Matrix4d, Eigen::Vector4d;
using Vec = Vector3d;
using Point = Vector3d;
using RGB = Vector3d;

class Scene;

class Ray {
private:
    Vec direction;
    Point origin;
    Scene* scene;
    const size_t recursionDepth;
public:
    Ray(Vec direction, Point origin, Scene* scene, const size_t recDepth);

    /**
     * @brief Calculates the color at the impact Point of the ray.
     * If no object is hit the ambient color is returned, 
     * otherwise the object color is calculated
     * 
     * @return RGB 
     */
    RGB getIntersectionColor();
    Vec getDir();
    Point getOri();

    /**
     * @brief Returns a copy of the current ray after it has been 
     * transformed by a given matrix
     * 
     * @param invMatrix 
     * @return Ray 
     */
    Ray getTransformedRay(Matrix4d& invMatrix);
};

#endif