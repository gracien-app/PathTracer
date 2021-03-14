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
    
protected:
    vect3D _colour;
    vect3D _center;
};

/// Sphere object which inherits from Solid (is hitable by ray)
/// @note [POLYMORPHIC] [HITABLE]
class Sphere : public Solid {
public:
    
    /// Sphere constructor with specifiable object parameters.
    /// @param center Center of mass of sphere
    /// @param radius Radius of sphere <0,1>
    /// @param colour RGB colour of the sphere
    /// @discussion Careful when initialising, choose radius and center point with respect
    /// to the world size (<1). Remember to specify colour as RGB, it's going to be normalized.
    Sphere(const vect3D& center, const double radius, const vect3D &colour);
    
    /// Checks if passed ray intersects with the geometrical figure of type Sphere.
    /// @param ray Reference to object of type Ray
    /// @return - True if ray intersects with object at least once.
    /// @return - False if no intersections occur.
    /// @discussion To obtain the final intersection formula, transform the (x-Cx)+(y-Cy)+(z-Cz) = r^2
    /// @discussion For point P, and center of sphere C, the difference is (Px-Cx)+(Py-Cy)+(Pz-Cz)
    /// @note Ray is a P(time) = Origin + time * Destination
    /// @note Final formula F(t) = t^2*Destination^2 + t*2*Destination*(Origin-C)+ Origin^2-R^2 = 0
    /// @warning Multiplication of vectors - Dot product!
    virtual bool Intersects(const Ray &ray) const;
    
private:
    
    double _radius;
};

#endif /* Solid_hpp */
