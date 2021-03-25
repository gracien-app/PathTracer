//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(const int &width, const int &height) : Camera(vect3D(0,0,0), 1.0, width, height) {
    std::cout << "[C] Scene" << std::endl;
    skyGradient.push_back( ( colour(255, 255, 255) ).normalizeRGB() );
    skyGradient.push_back( ( colour(101, 199, 247) ).normalizeRGB() );
    
    
    sceneObjects.push_back( std::unique_ptr<Sphere>( new Sphere( vect3D(0, -100.5, 1), 100.0f, colour(0, 0, 0) ) ) );
    sceneObjects.push_back( std::unique_ptr<Sphere>( new Sphere( vect3D(0.0f, 0.0f, 1.5f), 0.5f, colour(30, 30, 30) ) ) );

}

bool Scene::intersectScene (const Ray &ray, recent &recent_Inter, double timeMin, double timeMax) const {
    recent tempRecent;
    bool didIntersect = false;
    auto closestIntersect = timeMax;

    for (const auto& object : sceneObjects) {
        if ( object->Intersect(ray, tempRecent, timeMin, closestIntersect) ) {
            didIntersect = true;
            closestIntersect = tempRecent.time;
//            std::cout << closestIntersect << std::endl;
            recent_Inter = tempRecent;
        }
    }
    return didIntersect;
}

vect3D Scene::colourRay(const Ray& r, int rayBounces) {
    
    recent recInter;
    
    if (rayBounces == 0) return vect3D(0,0,0);
    
    if ( intersectScene ( r, recInter, 0, infinity ) ) {
        auto nextDir = recInter.position + recInter.outNormal + randInSphere();
        return colourRay(Ray(recInter.position, nextDir - recInter.position), rayBounces-1) * 0.5 ;
    }
    
    else {
        auto unit_R = r.getDest(); // Y can be between <-1,1> because of constant projectionHeight=2
        auto t = (unit_R.y()+1) * 0.5; // To make it go from <0, 1>
        return vect3D ( skyGradient[1]*(1-t) + skyGradient[0]*t );
    }
    // MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top
  }

