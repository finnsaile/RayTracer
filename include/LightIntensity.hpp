#ifndef LIGHTINTENSITY_H
#define LIGHTINTENSITY_H

#include <eigen3/Eigen/Dense>

using Eigen::Vector3d;
using RGB = Vector3d;
using Vec = Vector3d;

class LightIntensity {
protected:
    RGB I; //Light intensity (color)
    Vector3d K; //reflection coefficient
    Vector3d E; //light intensity
public:
    LightIntensity(RGB I, Vector3d K);

    /**
     * @brief Combines the own light intensity wiht another one
     * 
     * @param other 
     * @return LightIntensity& 
     */
    LightIntensity& operator+=(LightIntensity& other);

    /**
     * @brief Return the light intensity in RGB values from 0-255
     * 
     * @return RGB 
     */
    RGB getIntensity();
    virtual ~LightIntensity() = 0;
};

class AmbientComponent : public LightIntensity {
public:
    AmbientComponent(RGB I, Vector3d K);
    virtual ~AmbientComponent();
};

class DiffuseComponent : public LightIntensity {
protected:
    Vec N; //Normal Vector at point
    Vec L; //Diredction Vector towards light
    double dotProd;
public:
    DiffuseComponent(RGB I, Vector3d K, Vec N, Vec L);
    double getDotProd() const;
    virtual ~DiffuseComponent();
};

class SpecularComponent : public LightIntensity {
protected:
    Vec V; //-Incoming Vector
    Vec R; //Reflection Vector from Light source
    double alpha; //shiny nt
    double dotProd;
public:
    SpecularComponent(RGB I, Vector3d K, Vec V, Vec N, Vec L, double alpha);
    double getDotProd() const;
    virtual ~SpecularComponent();
};

class RefComponent : public LightIntensity {
public:
    RefComponent(RGB I, Vector3d K);
    virtual ~RefComponent();
};

#endif