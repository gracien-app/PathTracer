//
//  Created by Gracjan Jeżewski on 13/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#pragma once

#include <PathTracer/Renderer/Scene/Material.hpp>

class Ray;
class Intersection;

/// Base class for all Solid (hitable by rays) objects.
/// @discussion [POLYMORPHIC] [INTERSECTS]
class Solid {
public:
    
    /// Base constructor used in all deriving classes to initialise object with two shared parameters: center point of geometry and colour.
    /// @param centerPoint Vector point defining position of the central point of the geometry
    /// @param colour Colour object defining colour of the geometry
    Solid(const vect3D &centerPoint, std::shared_ptr<Material> &materialPtr);
   
    /// Empty Base destructor
    /// @warning [ NEEDS TO BE OVERLOADED ]
    virtual ~Solid();
    
    /// Sets the position according to the XYZ of vect3D object passed.
    /// @param vector Reference to vect3D object
    void setPosition(const vect3D &newPosition);
    
    /// Method returning position of the object.
    /// @returns Value of 3-dimensional vector defining center point of geometry.
    vect3D getPosition();
    
    /// Virtual empty method for deriving classes.
    /// @param ray Ray object with specified origin and destination direction.
    /// @param recent_Inter Structure containing information about recent intersection.
    /// @param timeMin Value defining minimum time at which intersection can occur.
    /// @param timeMax Value defining maximum time at which intersection can occur.
    /// @warning [ NEEDS TO BE OVERLOADED ]
    virtual bool Intersect (const Ray &ray, Intersection &recent_Inter, const double &timeMin, const double &timeMax) const;
    
protected:
    vect3D _center;
    std::shared_ptr<Material> _material;
};
