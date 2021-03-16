//
//  Sphere.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 14/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Sphere.hpp"

Sphere::Sphere(const vect3D &center, const double radius, const colour &colour) {
    this->setColour(colour);
    this->setPosition(center);
    this->_radius = radius;
}

bool Sphere::Intersect (const Ray &ray, recent &recent_Intersect, double timeMin, double timeMax) const {
    
    auto OriginC = ray.getOrigin()-_center;
    auto a = ray.getDest().lengthSquared();
    auto simpler_b = ray.getDest().dot(OriginC); //simplification, b is always 2* so some 2's cancel in the delta and solution
    auto c = OriginC.lengthSquared()-(_radius*_radius);
    
    auto delta = simpler_b*simpler_b - a*c;
    
    if (delta < 0) {
        return -1;
    }
    else {
        return ( -simpler_b-sqrt(delta) ) / a; //Find SMALLER time t for which intersection occurs (the bigger one is on the back of the sphere if ray goes through the sphere
    }
}
