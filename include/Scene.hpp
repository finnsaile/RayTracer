#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <Eigen/Dense>
#include <cmath>
#include <vector>
#include <fstream>
#include <array>

#include "Screen.hpp"
#include "LightSource.hpp"
#include "Ray.hpp"
#include "PrimitiveObject.hpp"

using std::string;
using std::vector, std::array;
using std::unique_ptr;
using std::ifstream;

using Camera = Eigen::Vector3d;
using RGB = Eigen::Vector3d;

class PrimitiveObject;

class Scene {
friend class Ray;
private:
    size_t maxRecursionDepth;
    unique_ptr<RGB> ambientColor;
    vector<unique_ptr<PrimitiveObject>> objects;
    vector<LightSource> lightSources;
    unique_ptr<Camera> camera;
    unique_ptr<Screen> screen;

    /**
     * @brief Calculates the color of a Pixel, 
     * given its location and the location of the camera
     * 
     * @param pixelLocation
     * @param camLoc 
     * @return RGB 
     */
    RGB calculateColor(Eigen::Vector3d pixelLocation, Eigen::Vector3d camLoc);

public: 
    Scene();

    /**
     * @brief Reads Scene entities from a given file 
     * and creates member object with the gicen information
     * 
     * @param fileName 
     */
    void readEntities(string fileName);

    /**
     * @brief Creates a picture of the scene and outputs it to the given file name
     * 
     * @param pictureName 
     */
    void createPicture(string pictureName);
};

namespace vecTrans {
/**
 * @brief Helperfunction that creates a transformation matrix 
 * and its inverse given on the parameters in the file
 * 
 * @param file 
 * @return array<Eigen::Matrix4d, 2> 
 */
array<Eigen::Matrix4d, 2> getTransformationMatrix(ifstream& file);

/**
 * @brief Helperfunction that reads a line and 
 * returns a vector with the content given on said line
 * 
 * @tparam T 
 * @param lineHandle 
 * @param file 
 * @return T 
 */
template<typename T>
T getVecFromFile(string lineHandle, ifstream& file) {
    string line;
    getline(file, line);
    if(line.find(lineHandle) == string::npos)
        throw std::runtime_error("Can't find handle: " + lineHandle + " in line: " + line);
    
    line = line.substr(line.find(" ") + 1);
    T output;
    int index;
    for(int i = 0; i < output.size(); i++) {
        index = line.find(" ");
        output[i] = stod(line.substr(0, index));
        line = line.substr(index + 1);
    }
    return output;
}

}

#endif