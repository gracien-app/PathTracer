//
//  Ray.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp

#include "Vectors.hpp"

class Ray {
public:
    
    // MARK: Constructors
    Ray();
    Ray(const vect3D& origin, const vect3D& destination);
    
    // MARK: Private data access
    vect3D getOrigin() const;
    vect3D getDest() const;

    // MARK: Utility methods
    vect3D pos(double time) const;
    
    // MARK: Debug
    void printInfo() const;
    
private:
    vect3D orig;
    vect3D dest;
};



#endif /* Ray_hpp */
