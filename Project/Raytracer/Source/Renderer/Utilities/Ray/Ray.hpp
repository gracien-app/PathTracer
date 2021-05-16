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

class Material;

/// Structure used to store information about recent intersections (collisions with geometry).
/// @note Because of how small the structure is, I have decided to not make a class out of it.
/// @param time Time of intersection is used to determine position of ray.
/// @param position Ray is a linear function ax+b where x=time, storing position is useful for determining normal vector for sphere.
/// @param outNormal Outward normal at the intersection point. Inward normals are not taken into account at the current stage of program.
/// @param material Pointer to material which was intersected by ray.
struct intersection {
    double time;
    vect3D position;
    vect3D outNormal; //MARK: Normal is always outward (outside of geometry / user defined for plane, rectangle).
    std::shared_ptr<Material> material;
};

class Ray {
public:
    
    // MARK: Constructors
    
    /// Default Ray constructor
    Ray();
    
    /// Ray constructor, creates Ray object with starting, and direction defining point.
    /// According to the Path Tracing algorithm, ray is a linear function F(Time) = Origin + Direction*Time
    /// Ray is infinite (only limited during program execution using infinity template variable) thus direction defines orientation of the ray.
    /// @param origin 3-dimensional vector defining starting position of the ray.
    /// @param destination 3-dimensional vector defining direction point of the ray.
    Ray(const vect3D& origin, const vect3D& direction);
    
    // MARK: Methods
    
    /// Method used to access private ray origin data.
    /// @const Method cannot alter the data during its execution.
    /// @returns Starting point of the ray (its origin)
    vect3D getOrigin() const;
    
    /// Method used to access private ray direction data.
    /// @const Method cannot alter the data during its execution.
    /// @returns Direction defining point of the ray.
    vect3D getDir() const;
    
    /// Method used to determine position of ray using linear function formula of the ray F(Time) = Origin + Direction*Time.
    /// @param time Integer defining time for which position should be evaluated.
    /// @const Method cannot alter the data during its execution.
    /// @returns 3-dimensional vector defining position of the ray at given time.
    vect3D getPos(const double &time) const;
    
private:
    
    vect3D orig;
    vect3D dir;
    
};

#endif /* Ray_hpp */
