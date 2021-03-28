//
//  Plane.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Plane.hpp"

Plane::Plane(const vect3D &centerPoint,
             const vect3D &normalDirection,
             const colour &colour) : _normal(normalDirection), Solid(centerPoint, colour) {}

bool Plane::Intersect (const Ray &ray, collision &recent_Inter, const double &timeMin, const double &timeMax) const {
    
    auto nominator = (_center - ray.getOrigin()).dot(_normal);
    auto denominator = ray.getDest().dot(_normal);
    
    auto t = nominator / denominator;
    
    if (t > timeMax || t < timeMin ) return false;
    else {
        recent_Inter.time = t;
        recent_Inter.position = ray.pos(t);
        recent_Inter.outNormal = _normal;
        return true;
    }
}
