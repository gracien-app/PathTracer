//
//  Ray.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include <PathTracer/Renderer/Utilities/Ray.hpp>

// MARK: Constructors

Ray::Ray() {}
Ray::Ray(const vect3D &origin, const vect3D &direction) : orig(origin), dir(direction) {}

// MARK: Methods

vect3D Ray::origin() const {
    return orig;
}

vect3D Ray::direction() const {
    return dir;
}

vect3D Ray::position(const double &time) const {
    return orig+dir*time;
}



