//
//  Plane.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include "Sphere.hpp"


/// Class defining infinite one-sided plane object.
/// @discussion [POLYMORPHIC] [COLLISIONS]
class Plane : public Solid {
public:
    
    ~Plane() override;
    
    /// Plane constructor for creation of infinite one-sided plane object.
    /// @param centerPoint Vector point defining position of the central point of the geometry
    /// @param normalDirection Normal vector of the geometry, defines direction towards which geometry is oriented.
    /// @param colour Colour object defining colour of the geometry
    Plane(const vect3D &centerPoint, const vect3D &normalDirection, std::shared_ptr<Material> &materialPtr);
    
    /// Overloaded method checking if passed ray can intersect with infinite one-sided plane geometry.
    /// @param ray Reference to object of type Ray
    /// @param recent_Inter Reference to Recent structure which keeps track of recent intersections performed.
    /// @param timeMin Specifies minimum time when the intersection can occur.
    /// @param timeMax Specifies maximum time when the intersection can occur.
    /// @return - True if ray INTERSECTS the geometry.
    /// @return - False if no intersections occur.
    /// @warning Plane is one-sided, only rays coming from correct direction (opposite to Normal vector of geometry) can intersect with it properly (Reflect).
    /// @discussion Normal vector is what defines the geometry. All vectors which have their Dot product with normal vector equal 0, lie on the plane.
    /// @discussion That is because if Dot product is 0, it means that two vectors are perpendicular (lie on the same "plane").
    /// @discussion Function tries to find time t in range (timeMin, timeMax) where ray.pos(t) is perpendicular to Normal vector of the geometry.
    /// @note Source: https://www.sciencedirect.com/topics/computer-science/intersection-routine
    bool Intersect (const Ray &ray, Intersection &recent_Inter, const double &timeMin, const double &timeMax) const override;
    
private:
    vect3D _normal;
};

#endif /* Plane_hpp */
