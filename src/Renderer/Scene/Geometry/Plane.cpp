//
//  Plane.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include <PathTracer/Renderer/Scene/Geometry/Plane.hpp>

Plane::~Plane() {}

Plane::Plane(const vect3D &centerPoint,
             const vect3D &normalDirection,
             std::shared_ptr<Material> &materialPtr) : _normal(normalDirection), Solid(centerPoint, materialPtr) {}

bool Plane::Intersect (const Ray &ray, Intersection &recInter, const double &timeMin, const double &timeMax) const {
    
    const auto nominator = (_center - ray.origin()).Dot(_normal);
    const auto denominator = ray.direction().Dot(_normal);
    
    if(denominator == 0) return false; // Prevent division by 0
    auto t = nominator / denominator;
    
    if (t > timeMax || t < timeMin ) return false;
    else {
        recInter.time       = t;
        recInter.position   = ray.position(t);
        recInter.outNormal  = _normal;
        recInter.material   = _material;
        return true;
    }
}
