//
//  Ray.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Ray.hpp"
#include <iostream>
#include "Vectors.hpp"

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

// MARK: Utility methods
vect3D Ray::pos(double time) const {
    return dest*time + orig;
    //MARK: Initial idea - Ax+B where A is destination, x is time, B is origin, so it goes towards dest with time t, i can multiply dest by constant thanks to operator.
}

// MARK: Debug
void Ray::printInfo() {
    std::cout << "\nRAY Origin: "<< orig.x()<< " "<< orig.y()<< " "<< orig.z();
    std::cout << " Dest: "<< dest.x()<< " "<< dest.y()<< " "<< dest.z()<<"\n";
    
}

vect3D colourRay(const Ray& r)  {
    auto unit_R = Normalize(r.getDest()); // vector is of length 1 now and xyz are <0,1>
    return vect3D(1.0, 1.0, 1.0)*(1-abs(unit_R.y()));
    // MARK: The bigger the |Y coordinate|, the darker the colour, gradient should look like black-white-black if no mistakes are here.
}

