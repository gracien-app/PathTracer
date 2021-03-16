//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene() {
    skyGradient.push_back( ( colour(26, 41, 128) ).normalizeRGB() );
    skyGradient.push_back( ( colour(38, 208, 206) ).normalizeRGB() );
    
    sceneCamera = std::make_shared<Camera>(1, vect3D(0,0,0));
    
    sceneObjects.push_back( std::unique_ptr<Sphere>( new Sphere( vect3D(0, 0, 1), 0.5, colour(30, 30, 30) ) ) );    
}

vect3D Scene::colourRay(const Ray& r) {
 /*
    auto t = spheres[0].Intersect(r); //Get the time of intersection
    if (t > 0) { //If time is positive then hit happened in front of camera, not behind, rays go to projection plane
        vect3D Normal = Normalize( r.pos(t) - spheres[0].getCenter() ); //Normal vector (perpendicular to the surface) for sphere is simply inverted vector from intersection point p(t) to sphere center -(C-P) = P-C.
        return vect3D ( Normal.x()+1, Normal.y()+1, Normal.z()+1 ) * 0.5 ; //same trick as below, to have <0,1> range, z is already <0,1> (front of camera and its normalised) so no need for +1 correction.
    }
    
    auto unit_R = r.getDest(); // Y can be between <-1,1> because of constant projectionHeight=2
    t = (unit_R.y()+1) * 0.5; // To make it go from <0, 1>
        
    return vect3D ( _sky[1]*(1-t) + _sky[0]*t );
    
    // MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top
  */
  }

