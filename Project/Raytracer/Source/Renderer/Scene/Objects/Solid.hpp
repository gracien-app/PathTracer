//
//  Solid.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 13/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Solid_hpp
#define Solid_hpp

#include "Vectors.hpp"
#include "Ray.hpp"


/// Base class for all Solid (hitable by rays) objects.
/// @note [HITABLE]
class Solid {
public:
    void setPosition(const vect3D &vector);
    void setColour(const vect3D &rgb);
    
    vect3D& getColour();
    vect3D& getCenter();
    
protected:
    vect3D _colour;
    vect3D _center;
};

#endif /* Solid_hpp */
