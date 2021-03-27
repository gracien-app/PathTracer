//
//  Disc.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Disc.hpp"

Disc::Disc(const vect3D &centerPoint,
             const vect3D &normalDirection,
             const double sideLength,
             const colour &colour) : _side(sideLength), _normal(normalDirection), Solid(centerPoint, colour) {}

bool Disc::Intersect (const Ray &ray, recent &recent_Inter, double timeMin, double timeMax) const {
    
    auto nominator = (_center - ray.getOrigin()).dot(_normal);
    auto denominator = ray.getDest().dot(_normal);
    
    auto t = nominator / denominator;
    auto rayAtT= ray.pos(t);
    auto distance = rayAtT - _center;
    
    if (t > timeMax || t < timeMin || (distance.length() > (_side/2)) ) return false;
    else {
        
        recent_Inter.time = t;
        recent_Inter.position = rayAtT;
        recent_Inter.outNormal = _normal;
        return true;
    }
}

