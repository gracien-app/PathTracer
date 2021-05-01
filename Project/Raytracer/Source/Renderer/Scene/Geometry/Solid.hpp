//
//  Solid.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 13/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Solid_hpp
#define Solid_hpp

#include "Material.hpp"

/// Base class for all Solid (hitable by rays) objects.
/// @discussion [POLYMORPHIC] [COLLISIONS]
class Solid {
public:
    
    /// Base constructor used in all deriving classes to initialise object with two shared parameters: center point of geometry and colour.
    /// @param centerPoint Vector point defining position of the central point of the geometry
    /// @param colour Colour object defining colour of the geometry
    Solid(const vect3D &centerPoint, std::shared_ptr<Material> &materialPtr);
    
    /// Sets the position according to the XYZ of vect3D object passed.
    /// @param vector Reference to vect3D object
    /// @warning Inverts Z to compensate the right handed coordinate system, so that objects with positive Z are in front of "camera".
    void setPosition(const vect3D &newPosition);
    
    vect3D getPosition();
    
    /// Virtual empty method for Deriving classes.
    /// @param ray Ray object with specified origin and destination direction.
    /// @param recent_Inter Structure containing information about recent intersection.
    /// @param timeMin Value defining minimum time at which intersection can occur.
    /// @param timeMax Value defining maximum time at which intersection can occur.
    /// @warning [ NEEDS TO BE OVERLOADED ]
    virtual bool Intersect (const Ray &ray, collision &recent_Inter, const double &timeMin, const double &timeMax) const;
    
protected:
    vect3D _center;
    std::shared_ptr<Material> _material;
};

#endif /* Solid_hpp */
