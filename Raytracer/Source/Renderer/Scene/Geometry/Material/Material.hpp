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
/// It can be reflected, diffused (scattered randomly) or completely absorbed.
/// @note Behaviour of material is defined by Reflect method.
class Material {
public:
    
    /// Base Material constructor
    /// @discussion Initialises _colour using initialiser list
    /// @param rgbColour Value defining 3-component colour with normalised RGB partials <0,1>
    /// @warning Provided colour must have normalised partials, no checks are performed. Unnormalised values lead to oversaturation (white image).
    Material(const Colour &rgbColour);
    
    /// Virtual destructor of Material class
    virtual ~Material();
    
    /// Method used to define reflected ray based on internal material logic.
    /// @warning Needs to be overloaded. Base class does not produce reflected ray.
    /// @param inputRay Ray object defining ray which hit the material surface.
    /// @param reflRay Ray object which is going to be transformed into reflected ray.
    /// @param recInter Intersection structure containing data about last collision.
    /// @param reflColour Colour object passed by reference which will be given information about material colour.
    virtual bool reflect(const Ray &inputRay, Ray &reflRay,
                         const Intersection &recInter, Colour &reflColour ) const;
    
protected:
    Colour _colour;
};

/// @brief Diffused material based on Lambertian Diffuse Model.
/// @discussion Lambertian diffuse model defines "ideal matte" surface, where ray gets scattered at many different angles.
/// At the POINT OF INTERSECTION, random non-negative (with respect to normal vector at the intersection point) unit vector is generated.
/// Newly generated vector becomes the direction of scattered ray.
class Diffused : public Material {
public:
    
    /// Diffused material constructor. Uses Base class constructor to initialise colour.
    /// @param rgbColour Value defining 3-component colour with normalised RGB partials <0,1>
    Diffused(const Colour &rgbColour);
    
    /// Override of default destructor of base Material class to properly destruct the object.
    ~Diffused() override;
    
    /// Method used to define reflected ray based on internal material logic.
    /// @param inputRay Ray object defining ray which hit the material surface.
    /// @param reflRay Ray object which is going to be transformed into reflected ray.
    /// @param recInter Intersection structure containing data about last collision.
    /// @param reflColour Colour object passed by reference which will be given information about material colour.
    virtual bool reflect(const Ray &inputRay, Ray &reflRay,
                         const Intersection &recInter, Colour &reflColour ) const override;
};

/// @brief Metallic material which reflects the ray with angle equal to the collision angle.
/// @discussion The ray is reflected at the same angle at which it collided with the surface.
/// Angle is defined with respect to the normal vector of the surface at the point of intersection.
/// To replicate roughness of metal surfaces, additional parameter is available.
/// Roughness is achieved, by altering perfect DIRECTION (end) of reflected ray by random unit vector (a fraction of it defined by roughness).
/// @warning Rougness needs to be in range <0,1>. Incorrect roughness value will be clamped to maximum of 1.0
/// @note Formula for reflected ray is Reflected = Direction - 2 (Direction * Normal) * Normal
/// Source: https://math.stackexchange.com/questions/13261/how-to-get-a-reflection-vector
class Metallic : public Material {
public:
    
    /// Diffused material constructor. Uses Base class constructor to initialise colour.
    /// @param rgbColour Value defining 3-component colour with normalised RGB partials <0,1>
    /// @param roughness Value defining fraction by which reflected ray is going to be altered (simulation of surface roughness).
    Metallic(const Colour &rgbColour, const double &roughness);
    
    /// Override of default destructor of base Material class to properly destruct the object.
    virtual ~Metallic() override;
    
    /// Method used to define reflected ray based on internal material logic.
    /// @param inputRay Ray object defining ray which hit the material surface.
    /// @param reflRay Ray object which is going to be transformed into reflected ray.
    /// @param recInter Intersection structure containing data about last collision.
    /// @param reflColour Colour object passed by reference which will be given information about material colour.
    virtual bool reflect(const Ray &inputRay, Ray &reflRay,
                         const Intersection &recInter, Colour &reflColour ) const override;
private:
    double _rough;
};

#endif /* Material_hpp */
