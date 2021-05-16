//
//  Rectangle.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 29/04/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Rectangle.hpp"

Rectangle::~Rectangle() {
    std::cout << "  [D] Rectangle: Destructed" << std::endl;
}

Rectangle::Rectangle(   const vect3D &centerPoint, const vect3D &normalDirection,
                        const double &sideLength, std::shared_ptr<Material> &materialPtr) : _side(sideLength), _normal(normalDirection), Solid(centerPoint, materialPtr) {
                         
    auto half_Side = _side/2;
    _xmax = _center.x() + half_Side;
    _xmin = _center.x() - half_Side;
    
    _ymax = _center.y() + half_Side;
    _ymin = _center.y() - half_Side;
    
    _zmax = _center.z() + half_Side;
    _zmin = _center.z() - half_Side;
    
    }

bool Rectangle::Intersect (const Ray &ray, intersection &recInter, const double &timeMin, const double &timeMax) const {
    
    auto nominator = (_center - ray.getOrigin()).dot(_normal);
    auto denominator = ray.getDir().dot(_normal);
    
    auto t = nominator / denominator;
    if (t > timeMax || t < timeMin ) return false;
    
    auto x = ray.getOrigin().x() + ray.getDir().x()*t;
    auto y = ray.getOrigin().y() + ray.getDir().y()*t;
    auto z = ray.getOrigin().z() + ray.getDir().z()*t;
    
    if (y > _ymax || y < _ymin || x > _xmax || x < _xmin || z > _zmax || z < _zmin) return false;
    
    else {
        
        recInter.time       = t;
        recInter.position   = ray.getPos(t);
        recInter.outNormal  = _normal;
        recInter.material   = _material;
        return true;
    }
}
