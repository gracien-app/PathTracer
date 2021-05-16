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

// MARK: Reflect methods

bool Material::reflect(
                       const Ray &inputRay,
                             Ray &reflRay, const intersection &recInter, Colour &reflColour ) const {
    return false;
}

bool Diffused::reflect(const Ray &inputRay,
                             Ray &reflRay, const intersection &recInter, Colour &reflColour ) const {
    
    auto nextDir = randUnitDir(recInter.outNormal);
    
    reflRay = Ray(recInter.position, nextDir);
    
    reflColour = _colour;
    
    return true;
}

bool Metallic::reflect(const Ray &inputRay,
                             Ray &reflRay, const intersection &recInter, Colour &reflColour ) const {
    
    auto unitDir = Normalize( inputRay.getDir() );
    
    reflRay = Ray(recInter.position,
                  unitDir - 2*recInter.outNormal*unitDir.dot(recInter.outNormal) + (randUnitVector()*_rough));
    
    reflColour = _colour;
    
    if (reflRay.getDir().dot(recInter.outNormal)) return true;
    else return false;
}




