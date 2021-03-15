//
//  Sphere.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 14/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Sphere.hpp"

Sphere::Sphere(const vect3D &center, const double radius, const vect3D &colour) {
    this->setColour(colour);
    this->setPosition(center);
    this->_radius = radius;
}

bool Sphere::Intersects(const Ray &ray) const {
    
    auto OriginC = ray.getOrigin()-_center;
    auto a = ray.getDest().lengthSquared();
    auto b = 2*ray.getDest().dot(OriginC);
    auto c = OriginC.lengthSquared()-(_radius*_radius);
    
    auto delta = b*b - 4*a*c;
    
    if (delta >= 0) {
//        return ( -b-sqrt(delta) ) / (2*a);
        return true;
    }
    else {
        return false;
    }
    
}
