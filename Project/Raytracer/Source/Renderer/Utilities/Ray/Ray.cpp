//
//  Ray.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Ray.hpp"

// MARK: Constructors
Ray::Ray() {}

Ray::Ray(const vect3D &origin, const vect3D &destination) : orig(origin), dest(destination) {}

// MARK: Private data access
vect3D Ray::getOrigin() const {
    return orig;
}

vect3D Ray::getDest() const {
    return dest;
}

// MARK: Utility methods
vect3D Ray::pos(const double &time) const {
    return dest*time + orig;
    //MARK: Ray is a linear function Ax+B where A is destination, x is time, B is origin, so it goes towards dest with time.
}

// MARK: Debug
void Ray::printInfo() const {
    std::cout << "  Origin: "<< orig;
    std::cout << "  Dest:   "<< dest <<std::endl;
    
}



