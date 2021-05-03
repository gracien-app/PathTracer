//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(const int &width, const int &height, const int &variant) : Camera(vect3D(0,0,0), 1.0, width, height) {
    
    switch (variant) {
        case 1:
            setupCornell();
            break;
            
        case 2:
            setupTest();
            break;
            
        case 3:
            setupHole();
            break;
    }
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

void Scene::setupCornell() {
    std::cout << "[C] Scene: Cornell Box" << std::endl;
    
    const double rectSide = 1;
    
    skyGradient.push_back( ( colour(1.0, 1.0, 1.0) ) );
    skyGradient.push_back( ( colour(1.0, 1.0, 1.0) ) );
    
    std::shared_ptr<Material> leftWall  ( new Metallic( colour (252,70,107).normalizeRGB(), 1.0 ) );
    std::shared_ptr<Material> topWall  ( new Metallic( colour (159,89,170).normalizeRGB(), 1.0 ) );
    std::shared_ptr<Material> rightWall ( new Metallic( colour (63,94,251).normalizeRGB(), 1.0 ) );
    std::shared_ptr<Material> whiteWall ( new Metallic( colour (255, 255, 255).normalizeRGB(), 0.2) );
    std::shared_ptr<Material> ballMaterial ( new Metallic( colour (255, 255, 255).normalizeRGB(), 0.05 ) );
    std::shared_ptr<Material> cubeMaterial ( new Metallic( colour (255, 255, 255).normalizeRGB(), 0.05 ) );
    
    sceneObjects.push_back( std::unique_ptr<Sphere> ( new Sphere (vect3D(0.2, -0.3, 0.8),
                                                                  0.2,
                                                                  ballMaterial)));
    
    sceneObjects.push_back( std::unique_ptr<Cube> ( new Cube (vect3D(-0.2, -0.35, 0.8),
                                                                  0.3,
                                                                  cubeMaterial)));
    
    
    /* LEFT */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(-0.5, 0, 0.5),
                                                                         vect3D(1, 0, 0),
                                                                         rectSide,
                                                                         leftWall)));
    /* RIGHT */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0.5, 0, 0.5),
                                                                         vect3D(-1, 0, 0),
                                                                         rectSide,
                                                                         rightWall)));

    /* TOP */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, 0.5, 0.5),
                                                                         vect3D(0, -1, 0),
                                                                         rectSide,
                                                                         whiteWall)));

    /* BOTTOM */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, -0.5, 0.5),
                                                                         vect3D(0, 1, 0),
                                                                         rectSide,
                                                                         whiteWall)));

    /* FRONT BOTTOM */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, -0.6, 0),
                                                                         vect3D(0, 0, -1),
                                                                         rectSide,
                                                                         whiteWall)));
    
    /* FRONT UPPER */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, 0.6, 0),
                                                                         vect3D(0, 0, -1),
                                                                         rectSide,
                                                                         whiteWall)));

    /* BACK */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, 0, 1),
                                                                         vect3D(0, 0, 1),
                                                                         rectSide,
                                                                         ballMaterial)));
}

void Scene::setupTest() {
    std::cout << "[C] Scene: Test" << std::endl;
    
    const double rectSide = 1;
    
    skyGradient.push_back( ( colour(142,158,171).normalizeRGB() ) );
    skyGradient.push_back( ( colour(238,242,243).normalizeRGB() ) );
    
    std::shared_ptr<Material> whiteWall ( new Metallic( colour (238, 242, 243).normalizeRGB(), 0.9 ) );
    std::shared_ptr<Material> ball ( new Metallic( colour (238, 242, 243).normalizeRGB(), 0 ) );
    
    sceneObjects.push_back( std::unique_ptr<Sphere> ( new Sphere (vect3D(0, 0.0, 0.80),
                                                                  0.2,
                                                                  ball)));
    
    /* LEFT */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(-0.5, 0, 0.5),
                                                                         vect3D(1, 0, 0),
                                                                         rectSide,
                                                                         whiteWall)));
    /* RIGHT */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0.5, 0, 0.5),
                                                                         vect3D(-1, 0, 0),
                                                                         rectSide,
                                                                         whiteWall)));

    /* TOP */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, 0.5, 0.5),
                                                                         vect3D(0, -1, 0),
                                                                         rectSide,
                                                                         whiteWall)));

    /* BOTTOM */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, -0.5, 0.5),
                                                                         vect3D(0, 1, 0),
                                                                         rectSide,
                                                                         whiteWall)));

    /* FRONT */
     sceneObjects.push_back( std::unique_ptr<Rectangle> ( new Rectangle (vect3D(0, 0, 0),
                                                                         vect3D(0, 0, -1),
                                                                         rectSide,
                                                                         whiteWall)));
    
}

void Scene::setupHole() {
    
    std::cout << "[C] Scene: Random Spheres" << std::endl;
    
    skyGradient.push_back( ( colour(24,90,157).normalizeRGB() ) );
    skyGradient.push_back( ( colour(67,206,162).normalizeRGB() ) );
    
}

