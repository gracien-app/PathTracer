//
//  Created by Gracjan Jeżewski on 28/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include <PathTracer/Renderer/Scene/Material.hpp>

// MARK: Constructors

Material::Material(const Colour &rgbColour) : _colour(rgbColour) {}

Diffused::Diffused(const Colour &rgbColour) : Material(rgbColour) {}

Metallic::Metallic(const Colour &rgbColour, const double &roughness) : Material(rgbColour) {
    _rough = clamp(roughness, 0.0, 1.0);
}

EmissiveColour::EmissiveColour(const Colour &rgbColour, const double &intensity) : Material(rgbColour) {
    _intensity = clamp(intensity, 0.0, 100.0);
}

EmissiveNormal::EmissiveNormal(const double &intensity) : Material(Colour(0.0, 0.0, 0.0)) {
    _intensity = clamp(intensity, 0.0, 100.0);
}

// MARK: Destructors
Material::~Material() {}
Diffused::~Diffused() {}
Metallic::~Metallic() {}
EmissiveColour::~EmissiveColour() {}
EmissiveNormal::~EmissiveNormal() {}

// MARK: Reflect Methods

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
    
    auto unitDir = Normalise( inputRay.direction() );
    
    reflRay = Ray(recInter.position,
                  unitDir - 2 * recInter.outNormal * unitDir.Dot(recInter.outNormal) + (randUnitVect() * _rough));
    
    // MARK: Reflected ray is given starting point at the point of intersection.
    // MARK: New direction is created using mathematical formula for reflection ray with normal vector (header comment).
    // MARK: Perfect reflection direction is then altered by some fraction (_rough) of randomly generated unit vector.
    
    reflColour = _colour;
    
    //MARK: Checks if direction is correct (on the outside of geometry - positive dot product) after applying roughness.
    if (reflRay.direction().Dot(recInter.outNormal)) return true;
    else return false;
}

/// MARK: Emit Methods

bool Material::emit(const Intersection &recInter, Colour &totalColour) const {
    return false;
}

bool EmissiveColour::emit(const Intersection &recInter, Colour &totalColour) const {
    
    totalColour = _colour * _intensity;
    return true;
    
}

bool EmissiveNormal::emit(const Intersection &recInter, Colour &totalColour) const {
    
    auto unitNormal = 0.5 * Colour(recInter.outNormal.x()+1,
                                   recInter.outNormal.y()+1,
                                   recInter.outNormal.z()+1);
    
    totalColour = unitNormal * _intensity;
    
    return true;
}



