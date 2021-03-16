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

struct recent {
    double time;
    vect3D position;
    vect3D normal;
};

/// Base class for all Solid (hitable by rays) objects.
/// @note [HITABLE]
class Solid {
public:
    
    /// Sets the position according to the XYZ of vect3D object passed.
    /// @param vector Reference to vect3D object
    /// @warning Inverts Z to compensate the right handed coordinate system, so that objects with positive Z are in front of "camera".
    void setPosition(const vect3D &vector);
    
    /// Sets the colour of object
    /// @param rgb Reference to object of type Colour with RGB parameters specified.
    /// @warning Provided object should contain standard RGB parameter values (0-255). Normalization is performed by the method itself.
    void setColour(const colour &rgb);
    
    vect3D& getColour();
    vect3D& getCenter();
    
    
    /// Virtual method used to check if ray with determined origin and destination direction intersects with the geometry.
    /// @param ray Reference to object of type Ray
    /// @param recent_Intersect Reference to Recent structure which keeps track of recent intersections performed.
    /// @param timeMin Specifies minimum time when the intersection can occur.
    /// @param timeMax Specifies maximum time when the intersection can occur.
    /// @returns FALSE. Solid is a base class of geometries, not geometry itself.
    virtual bool Intersect (const Ray &ray, recent &recent_Intersect, double timeMin, double timeMax) const;
    
protected:
    colour _colour;
    vect3D _center;
};

#endif /* Solid_hpp */
