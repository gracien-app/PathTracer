//
//  Disc.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Disc.hpp"

Disc::~Disc() {}

Disc::Disc(  const vect3D &centerPoint,
             const vect3D &normalDirection,
             const double discRadius,
             std::shared_ptr<Material> &materialPtr) : _radius(discRadius),
                                                      _normal(normalDirection),
                                                      Solid(centerPoint, materialPtr) {}

bool Disc::Intersect (const Ray &ray, Intersection &recInter, const double &timeMin, const double &timeMax) const {
    
    auto nominator = (_center - ray.origin()).Dot(_normal);
    auto denominator = ray.direction().Dot(_normal);
    
    auto t = nominator / denominator;
    auto rayAtT= ray.position(t);
    auto distance = rayAtT - _center;
    
    if (t > timeMax || t < timeMin || (distance.Length() > (_radius/2)) ) return false;
    
    else {
        
        recInter.time       = t;
        recInter.position   = rayAtT;
        recInter.outNormal  = _normal;
        recInter.material   = _material;
        return true;
    }
}

