#include "Scene.hpp"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <nlohmann/json.hpp>
#include <Eigen/Dense>
#include <fstream>
#include <thread>

#include "HalfSpace.hpp"
#include "statusbar.hpp"
#include "Sphere.hpp"
#include "JsonSerialization.hpp"

using std::ifstream, std::cout, std::endl;
using std::stod;
using Eigen::Vector2d;
using vecTrans::getTransformationMatrix;
using vecTrans::getVecFromFile;
using std::cos, std::sin;
using std::array;
using nlohmann::json;

Scene::Scene() {}

RGB Scene::calculateColor(Vector3d pixelLocation, Vector3d camLoc) {
    Vector3d output(0, 0, 0);

    Ray originalRay(pixelLocation - camLoc, camLoc, this, 0);
    output += originalRay.getIntersectionColor();

    if(!screen->antiAliasing) 
        return output;
    auto v1 = screen->screenVectors.first;
    auto v2 = screen->screenVectors.second;

    auto xRes = screen->resolution.x();
    auto yRes = screen->resolution.y();

    size_t counter = 1;
    for(int i = -1; i <= 1; i += 2) {
        Vector3d iLoc = pixelLocation - ((i * ((double)xRes / 4000)) * v1) - camLoc;
        for(int j = -1; j <= 1; j += 2) {
            counter++;
            Ray tempRay(iLoc + ((j * ((double)yRes / 4000)) * v2), camLoc, this, 0);
            output += tempRay.getIntersectionColor();
        }
    }

    output /= counter;
    return output;
}

void Scene::createPicture(string pictureName) {
    //Check if all necessary Objects have been declared
    assert(screen != nullptr);
    assert(camera != nullptr);
    assert(ambientColor != nullptr);

    //Create output Matrix
    //unique_ptr<RGB> &ac = ambientColor;
    cv::Mat outputImage(screen->resolution.y(), screen->resolution.x(), CV_8UC3, cv::Scalar(0, 0, 0));

    Statusbar bar(1000, true);
    //Loop over every pixel
    for(int i = 0; i < outputImage.rows; i++) {
        auto t = (double(i) / (outputImage.rows - 1));
        //Vector3d col = (1 - (1 - t)) * Vector3d({255, 255, 255}) + (1 - t) * Vector3d(ac->getValues());
        bar.setProgress(t * 100);
        for(int j = 0; j < outputImage.cols; j++) {
            Vector3d pixelLocation = screen->getPixelPosition(i, j);
            //Calculate vector coming from camera to current pixel
            RGB pixelCol = calculateColor(pixelLocation, *camera);
            outputImage.at<cv::Vec3b>(cv::Point(j, i)) = cv::Vec3b(pixelCol[2], pixelCol[1], pixelCol[0]);
        }
    }
    imwrite(pictureName, outputImage);
}

void Scene::readEntities(string filename) {
    ifstream file(filename);
    assert(file.is_open());
    string line;
    json data = json::parse(file);

    this->maxRecursionDepth = data.at("max_recursion_depth").get<size_t>();

    auto cameraJson = data.at("camera");
    this->camera = unique_ptr<Camera>(new Camera(cameraJson.at("pos").get<Camera>()));

    auto screenJson = data.at("screen");
    this->screen = unique_ptr<Screen>(new Screen(screenJson.get<Screen>()));

    auto ambientLightJson = data.at("ambient_light");
    this->ambientColor = unique_ptr<RGB>(new RGB(ambientLightJson.at("rgb").get<RGB>()));

    auto lightSourcesJson = data.at("light_sources");
    this->lightSources = lightSourcesJson.get<vector<LightSource>>();

    auto halfSpaceJson = data.at("halfspaces");
    auto halfSpaces = halfSpaceJson.get<vector<HalfSpace>>();
    for (auto& halfSpace : halfSpaces) {
        this->objects.push_back(std::move(std::make_unique<HalfSpace>(halfSpace)));
    }

    auto spheresJson = data.at("spheres");
    auto spheres = spheresJson.get<vector<Sphere>>();
    for (auto& sphere : spheres) {
        this->objects.push_back(std::move(std::make_unique<Sphere>(sphere)));
    }
}