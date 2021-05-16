//
//  Plane.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Plane.hpp"

Plane::~Plane() {
    std::cout << "  [D] Plane: Destructed" << std::endl;
}

Plane::Plane(const vect3D &centerPoint,
             const vect3D &normalDirection,
             std::shared_ptr<Material> &materialPtr) : _normal(normalDirection),
                                                      Solid(centerPoint, materialPtr) {}

bool Plane::Intersect (const Ray &ray, Intersection &recInter, const double &timeMin, const double &timeMax) const {
    
    auto nominator = (_center - ray.getOrigin()).Dot(_normal);
    auto denominator = ray.getDir().Dot(_normal);
    // TODO: Needs check if denominator is very small, check performance hit with profiler.
    // MARK:: ^- Performance hit is negliglible. Remark left for future expansion.
    
    auto t = nominator / denominator;
    
    if (t > timeMax || t < timeMin ) return false;
    else {
        recInter.time       = t;
        recInter.position   = ray.getPos(t);
        recInter.outNormal  = _normal;
        recInter.material   = _material;
        return true;
    }
}
