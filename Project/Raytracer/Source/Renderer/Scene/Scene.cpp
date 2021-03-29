//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(const int &width, const int &height) : Camera(vect3D(0,0,0), 0.5, width, height) {
    std::cout << "[C] Scene" << std::endl;
    
    //https://uigradients.com/#Portrait
    skyGradient.push_back( ( colour(238, 242, 243) ).normalizeRGB() );
    skyGradient.push_back( ( colour(142, 158, 171) ).normalizeRGB() );
    
    std::shared_ptr<Material> diffMaterial ( new Diffused( colour(230, 1, 1).normalizeRGB() ) );
    std::shared_ptr<Material> diffMaterial2 ( new Diffused( colour (30, 30, 30).normalizeRGB() ) );
    
    // BASIC SPHERE SCENE
    sceneObjects.push_back( std::unique_ptr<Plane> ( new Plane (vect3D(0, -0.5, 1), vect3D(0, 1, 0), diffMaterial2)) );
    sceneObjects.push_back( std::unique_ptr<Sphere> ( new Sphere (vect3D(0, 0, 1),0.5, diffMaterial)) );
    
}

colour Scene::colourRay(const Ray& r, int rayBounces) {
    
    collision recInter;
    
    if (rayBounces == 0) return colour(0,0,0);
    
    if ( intersectScene ( r, recInter, 0.001, infinity<double> ) ) { //MARK: Small numbers error correction
        
        colour totalColour;
        Ray reflectedRay;
        
        if (recInter.material->reflect(r, reflectedRay, recInter, totalColour)) {
            return totalColour * colourRay(reflectedRay, rayBounces-1);
        }
        
        else return colour(0,0,0);
    }
    
    else {
        auto unit_R = r.getDest(); // Y can be between <-1,1> because of constant projectionHeight=2
        auto t = (unit_R.y()+1) * 0.5; // To make it go from <0, 1>
        return colour ( skyGradient[1]*(1-t) + skyGradient[0]*t );
    }
}
// MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top


bool Scene::intersectScene (const Ray &ray, collision &recent_Inter, const double &timeMin, const double &timeMax) const {
    collision tempRecent;
    bool didIntersect = false;
    auto closestIntersect = timeMax;

    for (const auto& object : sceneObjects) {
        if ( object->Intersect(ray, tempRecent, timeMin, closestIntersect) ) {
            didIntersect = true;
            closestIntersect = tempRecent.time;
            recent_Inter = tempRecent;
        }
    }
    return didIntersect;
}

