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
    vect3D outNormal; //MARK: Normal is always outward (points from center of sphere to position of collision)
};

/// Base class for all Solid (hitable by rays) objects.
/// @discussion [POLYMORPHIC] [COLLISIONS]
class Solid {
public:
    
    /// Base constructor used in all deriving classes to initialise object with two shared parameters: center point of geometry and colour.
    /// @param centerPoint Vector point defining position of the central point of the geometry
    /// @param colour Colour object defining colour of the geometry
    Solid(const vect3D &centerPoint, const colour &colour);
    
    /// Sets the position according to the XYZ of vect3D object passed.
    /// @param vector Reference to vect3D object
    /// @warning Inverts Z to compensate the right handed coordinate system, so that objects with positive Z are in front of "camera".
    void setPosition(const vect3D &vector);
    
    /// Sets the colour of object
    /// @param rgb Reference to object of type Colour with RGB parameters specified.
    /// @warning Provided object should contain standard RGB parameter values (0-255). Normalization is performed by the method itself.
    void setColour(const colour &rgb);
    
    /// Virtual empty method for Deriving classes.
    /// @param ray Ray object with specified origin and destination direction.
    /// @param recent_Inter Structure containing information about recent intersection.
    /// @param timeMin Value defining minimum time at which intersection can occur.
    /// @param timeMax Value defining maximum time at which intersection can occur.
    /// @warning [ NEEDS TO BE OVERLOADED ]
    virtual bool Intersect (const Ray &ray, recent &recent_Inter, double timeMin, double timeMax) const;
    
protected:
    colour _colour;
    vect3D _center;
};

#endif /* Solid_hpp */
