#include "Ray.hpp"
#include "HalfSpace.hpp"

#include <iostream>

// used to move starting point towards ray direction to prevent colision with own object 
#define CORRECTION 0.000001

Ray::Ray(Vec direction, Point origin, Scene* scene, const size_t recDepth) : 
direction{direction.normalized()}, origin{origin}, scene{scene}, recursionDepth{recDepth + 1} {}

Vec Ray::getDir() {
    return direction;
}

Point Ray::getOri() {
    return origin;
}

RGB Ray::getIntersectionColor() {
    PrimitiveObject* closestObj = nullptr;
    unique_ptr<Point> minP = nullptr;
    double minD = std::numeric_limits<double>::max();
    Vec NP;

    for(auto& obj : scene->objects) {
        auto [P, N] = obj->getIntersection(this);
        if(P != nullptr) {
            double dist = Vector3d(origin - *P).norm();
            if(dist < minD) {
                minD = dist;
                closestObj = obj.get();
                minP = std::move(P);
                NP = N.normalized();
            }
        };
    }

    if(closestObj == nullptr) 
        return *scene->ambientColor;
    
    using ULI = unique_ptr<LightIntensity>; 
    vector<ULI> EVec;
    
    Vec V = origin - *minP;
    // HalfSpace* halfSpaceObj = dynamic_cast<HalfSpace*>(closestObj);
    // if(halfSpaceObj != NULL)
    //     EVec.push_back(ULI(new AmbientComponent(halfSpaceObj->getColor(*minP), closestObj->getK('a'))));
    // else
    EVec.push_back(ULI(new AmbientComponent(closestObj->getColor(), closestObj->getK('a'))));
    if(recursionDepth <= scene->maxRecursionDepth) {
        Vec I = (*minP - origin).normalized();
        Vec& N = NP;
        double IN = I.dot(NP);

        if(closestObj->getK('r').norm() != 0) {
            Vec R = I - 2*(IN*N);
            Ray reflectedRay(R , *minP + (R.normalized() * CORRECTION), scene, recursionDepth);
            EVec.push_back(ULI(new RefComponent(reflectedRay.getIntersectionColor(), closestObj->getK('r'))));
        }

        // if(closestObj->getK('t').norm() != 0) {
        //     double n = scene->refractiveIndex / closestObj->getRefi();
        //     Vec T = n * (I - (IN + sqrt(pow(n, 2) + pow(IN, 2) - 1)) * N);
        //     Ray refractedRay(T.normalized() , *minP + (T.normalized() * CORRECTION), scene, recursionDepth);

        //     EVec.push_back(ULI(new RefComponent(refractedRay.getIntersectionColor(), closestObj->getK('t'))));
        // }
    }


    for(auto& light : scene->lightSources) {
        bool intersec = false;
        Vector3d L = light.getLoc() - *minP;
        double lightDist = L.norm();
        for(auto& obj : scene->objects) {
            // if(obj.get() == closestObj)
            //     continue;
            
            Ray lightRay(L, *minP + (L.normalized() * CORRECTION), scene, 0);
            unique_ptr<Point> P = obj->getIntersection(&lightRay).first; 
            if(P != nullptr && (*P - *minP).norm() < lightDist) {
                intersec = true;
                break;
            }
        }
        if(!intersec) {
            unique_ptr<DiffuseComponent> dif(new DiffuseComponent(light.getColor(), closestObj->getK('d'), NP, L));
            if(dif->getDotProd() < 0)
                continue;
            EVec.push_back(ULI(std::move(dif)));
            unique_ptr<SpecularComponent> spec(new SpecularComponent(light.getColor(), closestObj->getK('s'), V, NP, L, closestObj->getAlpha()));
            if(spec->getDotProd() < 0)
                continue;
            EVec.push_back(ULI(std::move(spec)));
        }
    }

    for(size_t i = 1; i < EVec.size(); i++) {
        (*EVec[0]) += (*EVec[i]);
    }

    return EVec[0]->getIntensity();
}

Ray Ray::getTransformedRay(Matrix4d& invMatrix) {
    const Vector3d& S3 = origin, d3 = direction;
    Vector4d S4(S3[0], S3[1], S3[2], 1);
    Vector4d d4(d3[0], d3[1], d3[2], 0);

    S4 = invMatrix * S4;
    d4 = invMatrix * d4;
    return Ray({d4[0], d4[1], d4[2]}, {S4[0], S4[1], S4[2]}, scene, recursionDepth - 1);
}