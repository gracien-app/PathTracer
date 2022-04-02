//
//  Sphere.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 14/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include "Solid.hpp"

/// Sphere object which inherits from Solid (is hitable by ray)
/// @discussion [POLYMORPHIC] [COLLISIONS]
class Sphere : public Solid {
public:
    
    /// Base class destructor override to correctly destruct the Sphere object.
    ~Sphere() override;
    
    /// Default Sphere constructor
    /// @discussion Uses base Solid class constructor to initialise position and material data.
    /// @param centerPoint 3-dimensional vector defining center point of the Sphere.
    /// @param radius Value defining radius of the Sphere.
    /// @param materialPtr Pointer to material for the geometry.
    Sphere(const vect3D& centerPoint, const double radius, std::shared_ptr<Material> &materialPtr);
    
    /// Checks if passed ray intersects with the geometrical figure of type Sphere.
    /// @param ray Reference to object of type Ray
    /// @param recent_Inter Reference to Recent structure which keeps track of recent intersections performed.
    /// @param timeMin Specifies minimum time when the intersection can occur.
    /// @param timeMax Specifies maximum time when the intersection can occur.
    /// @return - True if ray intersects with object at least once.
    /// @return - False if no intersections occur.
    ///
    /// @discussion To obtain the final intersection formula, transform the (x-Cx)+(y-Cy)+(z-Cz) = r^2.
    /// @discussion For point P, and center of sphere C, the difference is (Px-Cx)+(Py-Cy)+(Pz-Cz)
    /// @note Ray is a P(time) = Origin + time * Direction
    /// @note Final formula F(t) = t^2*Direction^2 + t*2*Direction*(Origin-C)+ Origin^2-R^2
    /// Method behaves accordingly to the number of roots found (quadratic equation above). Method definition contains proper comments.
    /// @warning Multiplication of vectors - Dot product!
    bool Intersect (const Ray &ray, Intersection &recent_Inter, const double &timeMin, const double &timeMax) const override;
    
private:
    double _radius;
};
#endif /* Sphere_hpp */
