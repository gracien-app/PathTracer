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
    //for both, origin and destination.
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

vect3D skyColour(const Ray& r)  {
    auto unit_R = Normalize(r.getDest()); // vector is of length 1 now and xyz are <0,1>
    double height = (unit_R.y()+1) * 0.5; //To get the height, 0 for upper part, 1 for bottom
    //For -1 the output is 0, for 1 its 1 so fits, maybe change it later
    
    return vect3D(41, 128, 185)*(1-height) + vect3D(255, 255, 255)*height;
    // MARK: Linear interpolation formula for sky gradient: blend = (1-h) x colour_up + h x colour_down
    // MARK: Colours set acordingly to the sky colour, goes from dark blue to very light blue
    // MARK: https://uigradients.com/#CoolSky
}

