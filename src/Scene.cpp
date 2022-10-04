#include "Scene.hpp"

#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <fstream>
#include <thread>

#include "HalfSpace.hpp"
#include "statusbar.hpp"
#include "Sphere.hpp"

using std::ifstream, std::cout, std::endl;
using std::stod;
using Eigen::Vector2d;
using vecTrans::getTransformationMatrix;
using vecTrans::getVecFromFile;
using std::cos, std::sin;
using std::array;

Scene::Scene(string filename) {
    readEntities(filename);
}

RGB Scene::calculateColor(Vector3d pixelLocation, Vector3d camLoc) {
    Vector3d output(0, 0, 0);

    Ray originalRay(pixelLocation - camLoc, camLoc, this, 0);
    output += originalRay.getIntersectionColor();

    if(!screen->antiAliasing) 
        return output;
        
    size_t counter = 1;
    for(int i = -1; i <= 1; i += 2) {
        Vector3d iLoc = pixelLocation - ((i * ((double)screen->xRes / 4000)) * screen->v1) - camLoc;
        for(int j = -1; j <= 1; j += 2) {
            counter++;
            Ray tempRay(iLoc + ((j * ((double)screen->yRes / 4000)) * screen->v2), camLoc, this, 0);
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
    cv::Mat outputImage(screen->yRes, screen->xRes, CV_8UC3, cv::Scalar(0, 0, 0));

    Statusbar bar(1000, true);
    //Loop over every pixel
    for(int i = 0; i < outputImage.rows; i++) {
        auto t = (double(i) / (outputImage.rows - 1));
        //Vector3d col = (1 - (1 - t)) * Vector3d({255, 255, 255}) + (1 - t) * Vector3d(ac->getValues());
        bar.setProgress(t * 100);
        for(int j = 0; j < outputImage.cols; j++) {
            Vector3d pixelLocation = screen->getPixelLocation(i, j);
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
    
    while(getline(file, line)) {
        if(line == "camera") {
            Point pos = getVecFromFile<Vector3d>("pos:", file);

            this->camera = unique_ptr<Camera>(new Camera(pos));
        }
        else if(line == "light source") {
            Point pos = getVecFromFile<Vector3d>("pos:", file);
            RGB light = getVecFromFile<Vector3d>("rgb:", file);

            this->lightSources.push_back(LightSource(pos, light));
        }
        else if(line == "screen") {
            Point pos = getVecFromFile<Vector3d>("pos:", file);
            Vec N = getVecFromFile<Vector3d>("N:", file);
            Vector2d wh = getVecFromFile<Vector2d>("w/h:", file);
            Vector2d xy = getVecFromFile<Vector2d>("xr/yr:", file);
            Vector2d aa = getVecFromFile<Vector2d>("aa:", file);

            this->screen = unique_ptr<Screen>(new Screen(pos, N, wh[0], wh[1], xy[0], xy[1], aa[0]));
        }
        else if(line == "ambient light") {
            RGB light = getVecFromFile<Vector3d>("rgb:", file);
            maxRecursionDepth = getVecFromFile<Vector2d>("mrd:", file)[0];

            ambientColor = unique_ptr<RGB>(new RGB(light));
        }
        else if (line == "sphere") {
            string KHandles[] = {"Ka:", "Kd:", "Ks:", "Kr:", "Kt:"};
            vector<Vector3d> KVec;

            Point pos = getVecFromFile<Vector3d>("pos:", file);
            RGB light = getVecFromFile<Vector3d>("rgb:", file);
            Vector2d r = getVecFromFile<Vector2d>("r:", file);
            Vector2d alpha = getVecFromFile<Vector2d>("alpha:", file);
            for(auto& handle : KHandles) {
                KVec.push_back(getVecFromFile<Vector3d>(handle, file));
            }

            array<Matrix4d, 2> transArr = getTransformationMatrix(file);
            objects.push_back(unique_ptr<Sphere>(new Sphere(pos, r[0], transArr[0], transArr[1], light, alpha[0], KVec)));
        }
        else if(line == "halfspace") {
            string KHandles[] = {"Ka:", "Kd:", "Ks:", "Kr:", "Kt:"};
            vector<Vector3d> KVec;

            Point pos = getVecFromFile<Vector3d>("pos:", file);
            RGB light = getVecFromFile<Vector3d>("rgb:", file);
            Vec N = getVecFromFile<Vector3d>("N:", file);
            Vector2d alpha = getVecFromFile<Vector2d>("alpha:", file);
            for(auto& handle : KHandles) {
                KVec.push_back(getVecFromFile<Vector3d>(handle, file));
            }

            array<Matrix4d, 2> transArr = getTransformationMatrix(file);
            objects.push_back(unique_ptr<HalfSpace>(new HalfSpace(pos, N, transArr[0], transArr[1], light, alpha[0], KVec)));
        }
    }
}

array<Matrix4d, 2> vecTrans::getTransformationMatrix(ifstream& file) {
    vector<Matrix4d> MVector;
    vector<Matrix4d> M1Vector;

    string line;
    getline(file, line);
    while(!line.empty()) {
        string handle = line.substr(0, line.find(":"));
        line = line.substr(line.find(" ") + 1);
        int index;
        if(handle == "trans" || handle == "scal") {
            Vector3d t;
            for(size_t i = 0; i < 3; i++) {
                index = line.find(" ");
                t[i] = stod(line.substr(0, index));
                line = line.substr(index + 1);
            }

            if(handle == "trans") {
                MVector.push_back(Matrix4d());
                MVector.back() <<   1, 0, 0, t[0],
                                    0, 1, 0, t[1],
                                    0, 0, 1, t[2],
                                    0, 0, 0, 1;
                
                M1Vector.push_back(Matrix4d());
                M1Vector.back() <<  1, 0, 0, -t[0],
                                    0, 1, 0, -t[1],
                                    0, 0, 1, -t[2],
                                    0, 0, 0, 1;
            }
            else if(handle == "scal") {
                MVector.push_back(Matrix4d());
                MVector.back() <<   t[0], 0, 0, 0,
                                    0, t[1], 0, 0,
                                    0, 0, t[2], 0,
                                    0, 0, 0, 1;
                
                M1Vector.push_back(Matrix4d());
                M1Vector.back() <<  1/t[0], 0, 0, 0,
                                    0, 1/t[1], 0, 0,
                                    0, 0, 1/t[2], 0,
                                    0, 0, 0, 1;
            }
        }
        else if(handle == "rot") {
            char axis;
            double a;

            axis = line[0];
            index = line.find(" ");
            line = line.substr(index + 1);
            a = stod(line);
            cout << axis << ", " << a << endl;
            if(axis == 'z') {
                MVector.push_back(Matrix4d());
                MVector.back() <<   cos(a), -sin(a), 0, 0,
                                    sin(a), cos(a), 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1;
            
                M1Vector.push_back(Matrix4d());
                M1Vector.back() <<  cos(-a), -sin(-a), 0, 0,
                                    sin(-a), cos(-a), 0, 0,
                                    0, 0, 1, 0,
                                    0, 0, 0, 1;
            }
            else if(axis == 'x') {
                MVector.push_back(Matrix4d());
                MVector.back() <<   1, 0, 0, 0,
                                    0, cos(a), -sin(a), 0,
                                    0, sin(a), sin(a), 0,
                                    0, 0, 0, 1;
            
                M1Vector.push_back(Matrix4d());
                M1Vector.back() <<  1, 0, 0, 0,
                                    0, cos(-a), -sin(-a), 0,
                                    0, sin(-a), sin(-a), 0,
                                    0, 0, 0, 1;
            }
            else if(axis == 'y') {
                MVector.push_back(Matrix4d());
                MVector.back() <<   cos(a), 0, -sin(a), 0,
                                    0, 1, 0, 0,
                                    sin(a), 0, cos(a), 0,
                                    0, 0, 0, 1;
            
                M1Vector.push_back(Matrix4d());
                M1Vector.back() <<  cos(-a), 0, -sin(-a), 0,
                                    0, 1, 0, 0,
                                    sin(-a), 0, cos(-a), 0,
                                    0, 0, 0, 1;
            }
        }
        getline(file, line);
    }
    
    if(M1Vector.empty())
        return {Matrix4d().setIdentity(), Matrix4d().setIdentity()};

    for(size_t i = 1; i < M1Vector.size(); i++)
        M1Vector[0] *= M1Vector[i];
    for(size_t i = MVector.size() - 1; i > 0; i--)
        MVector[0] *= MVector[i];
    return {MVector[0], M1Vector[0]};
}