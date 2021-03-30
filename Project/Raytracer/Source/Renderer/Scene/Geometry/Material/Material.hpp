//
//  Material.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 28/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

#include "Ray.hpp"
#include "Colour.hpp"

/// @brief Base class for all  materials.
/// @discussion Materials define how ray behaves after colliding with different surfaces.
/// It can be reflected, diffused (scattered randomly) or completely absorbed, and such behaviour is defined for each material separately:
/// @ref virtual bool reflect() const;
class Material {
public:
    Material(const colour &rgbColour);
    virtual bool reflect(const Ray &inputRay,
                               Ray &reflRay, const collision &recInter, colour &reflColour ) const;
    
protected:
    colour _colour;
};

/// @brief Diffused material based on Lambertian Diffuse Model.
/// @discussion Lambertian diffuse model defines "ideal matte" surface, where ray gets scattered at many different angles.
/// At the point of intersection, random non-negative (with respect to normal vector at the collision point) unit vector is generated using
/// @ref vect3D::randUnitDir(const vect3D &normal)
/// Newly generated unit vector becomes the scattered ray.
class Diffused : public Material {
public:
    Diffused(const colour &rgbColour);
    virtual bool reflect(const Ray &inputRay,
                               Ray &reflRay, const collision &recInter, colour &reflColour ) const override;
};

/// @brief Metallic material which reflects the ray with angle equal to the collision angle.
/// @discussion The reflected ray is reflected at the same angle at which it collided with the surface.
/// Angle is defined with respect to the normal vector of the surface at the point of collision.
/// To replicate roughness of metal surfaces, additional parameter is available.
/// @ref double _rough;
/// It describes strength with which the angle is randomly altered.
class Metallic : public Material {
public:
    Metallic(const colour &rgbColour, const double &roughness);
    virtual bool reflect(const Ray &inputRay,
                               Ray &reflRay, const collision &recInter, colour &reflColour ) const override;
private:
    double _rough;
};

#endif /* Material_hpp */
