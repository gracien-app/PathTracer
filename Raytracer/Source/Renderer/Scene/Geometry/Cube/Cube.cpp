//
//  Cube.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 29/04/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Cube.hpp"

Cube::~Cube() {}

Cube::Cube(const vect3D &centerPoint, const double &sideLength,
           std::shared_ptr<Material> &materialPtr, const bool invertNormals) : Solid(centerPoint, materialPtr) {
    
    auto halfSide = sideLength/2;
    auto mult = invertNormals ? -1.0 : 1.0;
    
    auto frontCenter = _center + vect3D(0, 0, halfSide);
    auto backCenter = _center + vect3D(0, 0, -halfSide);
    
    auto leftCenter = _center + vect3D(halfSide, 0, 0);
    auto rightCenter = _center + vect3D(-halfSide, 0, 0);
    
    auto topCenter = _center + vect3D(0, halfSide, 0);
    auto bottomCenter = _center + vect3D(0, -halfSide, 0);
    
    if (!invertNormals)_cubeSides.push_back( std::make_unique<Rectangle> (frontCenter,  vect3D(0, 0, 1*mult), sideLength, _material) );
    _cubeSides.push_back( std::make_unique<Rectangle> (backCenter,   vect3D(0, 0, -1*mult),  sideLength, _material) );
    
    _cubeSides.push_back( std::make_unique<Rectangle> (topCenter,    vect3D(0, 1*mult, 0),  sideLength, _material) );
    _cubeSides.push_back( std::make_unique<Rectangle> (bottomCenter, vect3D(0, -1*mult, 0), sideLength, _material) );
    
    _cubeSides.push_back( std::make_unique<Rectangle> (leftCenter,   vect3D(1*mult, 0, 0),  sideLength, _material) );
    _cubeSides.push_back( std::make_unique<Rectangle> (rightCenter,  vect3D(-1*mult, 0, 0), sideLength, _material) );
    
}

bool Cube::Intersect (const Ray &ray, Intersection &recInter, const double &timeMin, const double &timeMax) const {
    
    Intersection tempIntersect;
    bool didIntersect = false;
    auto closestIntersect = timeMax;

    for (const auto& side : _cubeSides) {
        if ( side->Intersect(ray, tempIntersect, timeMin, closestIntersect) ) {
            didIntersect = true;
            closestIntersect = tempIntersect.time;
            recInter = tempIntersect;
        }
    }
    
    return didIntersect;
    
}
