//
//  Disc.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Disc_hpp
#define Disc_hpp

#include "Plane.hpp"

class Disc : public Solid {
public:
    
    /// Disc constructor for creation of finite (limited by radius) one-sided disc object.
    /// @param centerPoint Vector point defining position of the central point of the geometry
    /// @param normalDirection Normal vector of the geometry, defines direction towards which geometry is oriented.
    /// @param discRadius Radius of the disc
    /// @param colour Colour object defining colour of the geometry
    Disc(const vect3D &centerPoint,
         const vect3D &normalDirection,
         const double discRadius,
         std::shared_ptr<Material> &materialPtr);
    
    /// @brief Overloaded method checking if passed ray can intersect with disc geometry.
    /// @param ray Reference to object of type Ray
    /// @param recent_Inter Reference to Recent structure which keeps track of recent intersections performed.
    /// @param timeMin Specifies minimum time when the intersection can occur.
    /// @param timeMax Specifies maximum time when the intersection can occur.
    /// @return - True if ray INTERSECTS the geometry.
    /// @return - False if no intersections occur.
    /// @warning Disc is one-sided, only rays coming from correct direction (opposite to Normal vector of geometry) can intersect with it.
    /// @discussion Disc intersection function is Plane intersection function, with one additional if statement.
    /// @ref if ( distance.length() > (_radius/2) )
    /// For more in-depth explanation, one shoud refer to the infinite Plane intersection first.
    /// Additional statement: Length of vector defined as vector from center of geometry to the point of intersection, cannot be greater than radius.
    bool Intersect (const Ray &ray,
                    collision &recent_Inter,
                    const double &timeMin,
                    const double &timeMax) const override;
    
private:
    double _radius;
    vect3D _normal;
};


#endif /* Disc_hpp */
