//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(const int &width, const int &height) : Camera(vect3D(0,0,0), 1, width, height) {
    std::cout << "[C] Scene" << std::endl;
    
    //https://uigradients.com/#Portrait
    skyGradient.push_back( ( colour(238, 242, 243) ).normalizeRGB() );
    skyGradient.push_back( ( colour(142, 158, 171) ).normalizeRGB() );
    
    std::shared_ptr<Material> Material1 ( new Metallic( colour(1.0, 1.0, 1.0), 1.0 ) );
    std::shared_ptr<Material> Black ( new Diffused( colour(0, 0, 0)) );
    std::shared_ptr<Material> Material2 ( new Metallic( colour (0.85, 0.85, 0.85), 0.1 ) );
    
    sceneObjects.push_back( std::unique_ptr<Sphere> ( new Sphere (vect3D(0, -0.3, 0.75), 0.2, Material2)));
    //sceneObjects.push_back( std::unique_ptr<Sphere> ( new Sphere (vect3D(0, 0, 0), 4, Black)));
    
    sceneObjects.push_back( std::unique_ptr<Cube> ( new Cube (  vect3D(0, 0, -0.5),
                                                                1.0,
                                                                Material1)));
    
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

