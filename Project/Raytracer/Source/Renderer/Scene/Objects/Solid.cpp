//
//  Solid.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 13/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Solid.hpp"

void Solid::setPosition(const vect3D &vector) {
    _center[0] = vector.x();
    _center[1] = vector.y();
    _center[2] = vector.z();
}

void Solid::setColour(const vect3D &rgb) {
    _colour[0] = rgb.x();
    _colour[1] = rgb.y();
    _colour[2] = rgb.z();
    _colour.normRGB();
}

vect3D& Solid::getColour() {
    return _colour;
}

Sphere::Sphere(const vect3D &center, const double radius, const vect3D &colour) {
    this->setColour(colour);
    this->setPosition(center);
    this->_radius = radius;
}

bool Sphere::Intersects(const Ray &ray) const {
    
    auto OriginC = ray.getOrigin()-_center;
    auto a = ray.getDest().Dot(ray.getDest());
    auto b = 2*ray.getDest().Dot(OriginC);
    auto c = OriginC.Dot(OriginC)-(_radius*_radius);
    
    auto delta = b*b - 4*a*c;
    return (delta > 0);
}

