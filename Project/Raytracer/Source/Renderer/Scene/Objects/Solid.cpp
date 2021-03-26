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
    _center[2] = -vector.z(); //Inverted to compensate right handed cooridinates system.
}

void Solid::setColour(const colour &rgb) {
    _colour[0] = rgb.x();
    _colour[1] = rgb.y();
    _colour[2] = rgb.z();
    _colour.normalizeRGB();
}

bool Solid::Intersect (const Ray &ray, recent &recent_Inter, double timeMin, double timeMax) const {
    return false;
}
