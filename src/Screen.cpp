#include "Screen.hpp"
#include <iostream>
Screen::Screen(Point location, Vec normalVec, 
                double width, double height, size_t xRes, size_t yRes, bool antiAliasing) :
SceneEntity(location),
normalVec{normalVec},
width{width},
height{height},
xRes{xRes},
yRes{yRes},
antiAliasing{antiAliasing} {
    //calculate vectors spanning the screen plane
    const Vec& n = normalVec;
    //As the screen can't be crooked, the y coordinate is 0. Chose x as 1 and 
    //calculate z using the inverse dot product with n
    if(n[0] == 0)
        v1 = {n[2], 0, (n[0]/n[2])};
    else
        v1 = {(n[2]/n[0]), 0, n[0]};
    //v2 has to be orthogonal to v1 and n, leaving only one option (calculated with crossproduct)
    v2 = n.cross(v1);
    v2[1] = abs(v2[1]);
    //normalize both vectors to the distnce between pixels
    v1 = ((width/xRes) / v1.norm()) * v1;
    v2 = ((height/yRes) / v2.norm()) * v2;
}

//returns Point with pixel location at the given index
Point Screen::getPixelLocation(const size_t i, const size_t j) {
    //calculate origin by scaling v1 and v2 with i and j and subtracting them from the origin
    Vector3d loc = (location + (j * v1) - (i * v2));
    return loc;
}

Screen::~Screen() {}