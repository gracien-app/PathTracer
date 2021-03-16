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
#include "Colour.hpp"


/// Base class for all Solid (hitable by rays) objects.
/// @note [HITABLE]
class Solid {
public:
    
    
    /// Sets the position according to the XYZ of vect3D object passed.
    /// @param vector Reference to vect3D object
    /// @warning Inverts Z to compensate the right handed coordinate system, so that objects with positive Z are in front of "camera".
    void setPosition(const vect3D &vector);
    void setColour(const colour &rgb);
    
    vect3D& getColour();
    vect3D& getCenter();
    
protected:
    colour _colour;
    vect3D _center;
};

#endif /* Solid_hpp */
