//
//  Solid.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 13/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Solid.hpp"

Solid::Solid(const vect3D &centerPoint, std::shared_ptr<Material> &materialPtr) : _material(materialPtr) {
    setPosition(centerPoint);
}

void Solid::setPosition(const vect3D &newPosition) {
    _center[0] = newPosition.x();
    _center[1] = newPosition.y();
    _center[2] = -newPosition.z(); //Inverted to compensate right handed cooridinates system.
}

vect3D Solid::getPosition() {
    return _center;
}

bool Solid::Intersect (const Ray &ray, collision &recent_Inter, const double &timeMin, const double &timeMax) const {
    return false;
}
