//
//  Ray.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Ray.hpp"

// MARK: Constructors
Ray::Ray() {
    //No need to pre-initialise, vect3D default constructor sets each vect3D to be 0,0,0
}

Ray::Ray(const vect3D& origin, const vect3D& destination) : orig(origin), dest(destination) {
   // TODO: Consider making point class to differentiate between vectors and just points
}

// MARK: Private data access
vect3D Ray::getOrigin() const {
    return orig;
}

vect3D Ray::getDest() const {
    return dest;
}
