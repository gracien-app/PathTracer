//
//  Rectangle.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 29/04/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Rectangle.hpp"

Rectangle::~Rectangle() {}

Rectangle::Rectangle(const vect3D &centerPoint, const vect3D &normalDirection, const double &sideLength,
                     std::shared_ptr<Material> &materialPtr) : _side(sideLength), _normal(normalDirection), Solid(centerPoint, materialPtr) {
                         
    auto half_Side = _side/2;
    _xmax = _center.x() + half_Side;
    _xmin = _center.x() - half_Side;
    
    _ymax = _center.y() + half_Side;
    _ymin = _center.y() - half_Side;
    
    _zmax = _center.z() + half_Side;
    _zmin = _center.z() - half_Side;
    
}

bool Rectangle::Intersect (const Ray &ray, Intersection &recInter, const double &timeMin, const double &timeMax) const {
    
    auto nominator = (_center - ray.origin()).Dot(_normal);
    auto denominator = ray.direction().Dot(_normal);
    
    auto t = nominator / denominator;
    if (t > timeMax || t < timeMin ) return false;
    
    auto x = ray.origin().x() + ray.direction().x()*t;
    auto y = ray.origin().y() + ray.direction().y()*t;
    auto z = ray.origin().z() + ray.direction().z()*t;
    
    if (y > _ymax || y < _ymin || x > _xmax || x < _xmin || z > _zmax || z < _zmin) return false;
    
    else {
        
        recInter.time       = t;
        recInter.position   = ray.position(t);
        recInter.outNormal  = _normal;
        recInter.material   = _material;
        return true;
    }
}
