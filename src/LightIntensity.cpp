#include "LightIntensity.hpp"
#include <cmath>
#include <iostream>

using std::cout, std::endl;

using std::pow;

LightIntensity::LightIntensity(RGB I_, Vector3d K_) : I{I_/ 255}, K{K_} {}

LightIntensity& LightIntensity::operator+=(LightIntensity& other) {

    E[0] = 1 - (1 - E[0]) * (1 - other.E[0]);
    E[1] = 1 - (1 - E[1]) * (1 - other.E[1]);
    E[2] = 1 - (1 - E[2]) * (1 - other.E[2]);

    return *this;
}

Vector3d LightIntensity::getIntensity() {
    return E * 255;
}

LightIntensity::~LightIntensity() {}

AmbientComponent::AmbientComponent(RGB I_, Vector3d K_) : LightIntensity(I_, K_) {
    E = K.cwiseProduct(I);
}

AmbientComponent::~AmbientComponent() {}

DiffuseComponent::DiffuseComponent(RGB I_, Vector3d K_, Vector3d N_, Vector3d L_) : LightIntensity(I_, K_), N{N_.normalized()}, L{L_.normalized()} {
    dotProd = L.dot(N);
    E = K.cwiseProduct(I) * dotProd;
}

double DiffuseComponent::getDotProd() const {
    return dotProd;
}

DiffuseComponent::~DiffuseComponent() {}

SpecularComponent::SpecularComponent(RGB I_, Vector3d K_, Vector3d V_, Vector3d N_, Vector3d L_, double alpha_) : LightIntensity(I_, K_), V{V_.normalized()}, alpha{alpha_} {
    L_.normalize();
    N_.normalize();
    R = 2 * (L_.dot(N_)) * N_ - L_;

    dotProd = R.dot(V);

    E = K.cwiseProduct(I) * pow(dotProd, alpha);
}

double SpecularComponent::getDotProd() const {
    return dotProd;
}

SpecularComponent::~SpecularComponent() {}

RefComponent::RefComponent(RGB I_, Vector3d K_) : LightIntensity(I_, K_) {
    E = K.cwiseProduct(I);
}

RefComponent::~RefComponent() {}
