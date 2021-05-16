//
//  Cube.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 29/04/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Cube.hpp"

Cube::~Cube() {
    std::cout << "  [D] Cube: Destructed" << std::endl;
}

Cube::Cube(     const vect3D &centerPoint,
                const double sideLength,
                std::shared_ptr<Material> &materialPtr) : Solid(centerPoint, materialPtr) {
    
    auto halfSide = sideLength/2;
    
    vect3D frontCenter = _center + vect3D(0, 0, halfSide);
    vect3D backCenter = _center + vect3D(0, 0, -halfSide);
    
    vect3D leftCenter = _center + vect3D(halfSide, 0, 0);
    vect3D rightCenter = _center + vect3D(-halfSide, 0, 0);
    
    vect3D topCenter = _center + vect3D(0, halfSide, 0);
    vect3D bottomCenter = _center + vect3D(0, -halfSide, 0);
    
    cubeSides.push_back( std::unique_ptr<Rectangle> ( new Rectangle (   frontCenter,
                                                                        vect3D(0, 0, -1),
                                                                        sideLength,
                                                                        _material)));
    
    cubeSides.push_back( std::unique_ptr<Rectangle> ( new Rectangle (   backCenter,
                                                                        vect3D(0, 0, 1),
                                                                        sideLength,
                                                                        _material)));
    
    cubeSides.push_back( std::unique_ptr<Rectangle> ( new Rectangle (   topCenter,
                                                                        vect3D(0, 1, 0),
                                                                        sideLength,
                                                                        _material)));
    
    cubeSides.push_back( std::unique_ptr<Rectangle> ( new Rectangle (   bottomCenter,
                                                                        vect3D(0, -1, 0),
                                                                        sideLength,
                                                                        _material)));
    
    cubeSides.push_back( std::unique_ptr<Rectangle> ( new Rectangle (   leftCenter,
                                                                        vect3D(1, 0, 0),
                                                                        sideLength,
                                                                        _material)));
    
    cubeSides.push_back( std::unique_ptr<Rectangle> ( new Rectangle (   rightCenter,
                                                                        vect3D(-1, 0, 0),
                                                                        sideLength,
                                                                        _material)));
}

bool Cube::Intersect (const Ray &ray, intersection &recInter, const double &timeMin, const double &timeMax) const {
    
    intersection tempRecent;
    bool didIntersect = false;
    auto closestIntersect = timeMax;

    for (const auto& side : cubeSides) {
        if ( side->Intersect(ray, tempRecent, timeMin, closestIntersect) ) {
            didIntersect = true;
            closestIntersect = tempRecent.time;
            recInter = tempRecent;
        }
    }
    return didIntersect;
}
