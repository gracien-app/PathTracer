//
//  Material.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 28/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Material.hpp"

// MARK: Constructors

Material::Material(const Colour &rgbColour) : _colour(rgbColour) {}

Diffused::Diffused(const Colour &rgbColour) : Material(rgbColour) {}

Metallic::Metallic(const Colour &rgbColour, const double &roughness) : Material(rgbColour) {
    if (roughness <= 1.0 || roughness >= 0) _rough = roughness;
    else _rough = 1.0;
}

// MARK: Destructors
Material::~Material() {}
Diffused::~Diffused() {}
Metallic::~Metallic() {}

// MARK: Methods

bool Material::reflect(
                       const Ray &inputRay,
                             Ray &reflRay, const Intersection &recInter, Colour &reflColour ) const {
    return false;
}

bool Diffused::reflect(const Ray &inputRay,
                             Ray &reflRay, const Intersection &recInter, Colour &reflColour ) const {
    
    auto nextDir = randUnitDir(recInter.outNormal);
    
    reflRay = Ray(recInter.position, nextDir);
    
    //MARK: Random unit vector (length=1) is generated on the same side of the geometry (OUTWARD normal).
    //MARK: Reflected ray is given origin at intersection point, and new direction defined by nextDir.
    
    reflColour = _colour;
    
    return true;
}

bool Metallic::reflect(const Ray &inputRay,
                             Ray &reflRay, const Intersection &recInter, Colour &reflColour ) const {
    
    auto unitDir = Normalise( inputRay.getDir() );
    
    reflRay = Ray(recInter.position,
                  unitDir - 2 * recInter.outNormal * unitDir.Dot(recInter.outNormal) + (randUnitVect() * _rough));
    
    // MARK: Reflected ray is given starting point at the point of intersection.
    // MARK: New direction is created using mathematical formula for reflection ray with normal vector (header comment).
    // MARK: Perfect reflection direction is then altered by some fraction (_rough) of randomly generated unit vector.
    
    reflColour = _colour;
    
    //MARK: Checks if direction is correct (on the outside of geometry - positive dot product) after applying roughness.
    if (reflRay.getDir().Dot(recInter.outNormal)) return true;
    else return false;
}




