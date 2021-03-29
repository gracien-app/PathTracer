//
//  Material.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 28/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Material.hpp"

// MARK: Constructors

Material::Material(const colour &rgbColour) : _colour(rgbColour) {};

Diffused::Diffused(const colour &rgbColour) : Material(rgbColour) {};

Metallic::Metallic(const colour &rgbColour) : Material(rgbColour) {};

// MARK: Reflect methods

bool Material::reflect(
                       const Ray &inputRay,
                             Ray &reflRay, const collision &recInter, colour &reflColour ) const {
    return false;
}

bool Diffused::reflect(const Ray &inputRay,
                             Ray &reflRay, const collision &recInter, colour &reflColour ) const {
    auto nextDir = recInter.position + randUnitDir(recInter.outNormal);
    
    reflRay = Ray(recInter.position, nextDir);
    
    reflColour = _colour;
    
    return true;
}

bool Metallic::reflect(const Ray &inputRay,
                             Ray &reflRay, const collision &recInter, colour &reflColour ) const {
    return false;
}




