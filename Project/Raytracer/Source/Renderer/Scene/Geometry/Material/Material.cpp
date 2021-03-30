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
    
    auto nextDir = randUnitDir(recInter.outNormal);
    
    reflRay = Ray(recInter.position, nextDir);
    
    reflColour = _colour;
    
    return true;
}

bool Metallic::reflect(const Ray &inputRay,
                             Ray &reflRay, const collision &recInter, colour &reflColour ) const {
    
    auto unitDir = Normalize( inputRay.getDest() );
    
    reflRay = Ray(recInter.position, unitDir - 2*recInter.outNormal*unitDir.dot(recInter.outNormal));
    
    reflColour = _colour;
    
    if (reflRay.getDest().dot(recInter.outNormal)) return true;
    else return false;
}




