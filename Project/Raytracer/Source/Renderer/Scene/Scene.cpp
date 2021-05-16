//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(const int &width, const int &height, int &variant) : Camera(vect3D(0,0,0), 1.0, width, height) {
    
    switch (variant) {
        case 1:
            setupCornell();
            break;
            
        case 2:
            setupCornell(true);
            break;
            
        case 3:
            setupSpheres();
            break;
            
        case 99:
            plainScene();
            break;
            
        default:
            std::cout << "[!] Preset scene with ID: " << variant << " doesn't exist" << std::endl;
            std::cout << "    Using default instead " << std::endl;
            variant = 99;
            plainScene();
    }
}

Scene::~Scene() {
    std::cout << "[D] Scene: Destructed" << std::endl;
}

Colour Scene::colourRay(const Ray &r, const int &rayBounces) const {
    
    intersection recInter;
    
    if (rayBounces == 0) return Colour(0,0,0);
    
    if ( intersectScene ( r, recInter, 0.001, infinity<double> ) ) { //MARK: Small numbers error correction
        
        Colour totalColour;
        Ray reflectedRay;
        
        if (recInter.material->reflect(r, reflectedRay, recInter, totalColour)) {
            return totalColour * colourRay(reflectedRay, rayBounces-1);
        }
        
        else return Colour(0,0,0);
    }
    
    else {
        auto unit_R = r.getDir(); // Y can be between <-1,1> because of constant projectionHeight=2
        auto t = (unit_R.y()+1) * 0.5; // To make it go from <0, 1>
        return Colour ( skyGradient[1]*(1-t) + skyGradient[0]*t );
    }
}
// MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top


bool Scene::intersectScene (const Ray &ray, intersection &recent_Inter, const double &tMin, const double &tMax) const {
    intersection tempRecent;
    bool didIntersect = false;
    auto closestIntersect = tMax;

    for (const auto& object : sceneObjects) {
        if ( object->Intersect(ray, tempRecent, tMin, closestIntersect) ) {
            didIntersect = true;
            closestIntersect = tempRecent.time;
            recent_Inter = tempRecent;
        }
    }
    return didIntersect;
}

void Scene::setupCornell(const bool &reflective) {
    std::cout << "[C] Scene: Cornell Box" << std::endl;
    if (reflective) std::cout << "           Metallic version" << std::endl;
    
    const double rectSide = 1;
    
    skyGradient.push_back( ( Colour(1.0, 1.0, 1.0) ) );
    skyGradient.push_back( ( Colour(1.0, 1.0, 1.0) ) );
    
    std::shared_ptr<Material> leftWallMat, rightWallMat, wallMat, objectsMat;
    
    if (reflective) {
        leftWallMat = std::make_shared<Metallic>       ( Colour (252,70, 107).normalizeRGB(), 1.0 );
        rightWallMat = std::make_shared<Metallic>      ( Colour (63, 94, 251).normalizeRGB(), 1.0 );
        wallMat = std::make_shared<Metallic>      ( Colour (255,255,255).normalizeRGB(), 0.2 );
        objectsMat = std::make_shared<Metallic>    ( Colour (255,255,255).normalizeRGB(), 0.05);
    }
    else {
        leftWallMat = std::make_shared<Diffused>       ( Colour (252,70, 107).normalizeRGB() );
        rightWallMat = std::make_shared<Diffused>      ( Colour (63, 94, 251).normalizeRGB() );
        wallMat = std::make_shared<Diffused>      ( Colour (255,255,255).normalizeRGB() );
        objectsMat = std::make_shared<Diffused>    ( Colour (255,255,255).normalizeRGB() );
    }
    
    /* ITEMS */
    sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.2, -0.3, 0.8), 0.2, objectsMat));
    sceneObjects.push_back( std::make_unique<Cube>   (vect3D(-0.2, -0.35, 0.8), 0.3, objectsMat));
    
    
    /* LEFT  */
     sceneObjects.push_back( std::make_unique<Rectangle> (vect3D(-0.5, 0, 0.5), vect3D(1, 0, 0),
                                                          rectSide, leftWallMat));
    /* RIGHT */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0.5, 0, 0.5), vect3D(-1, 0, 0),
                                                          rectSide, rightWallMat));
    /* TOP */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0.5, 0.5), vect3D(0, -1, 0),
                                                          rectSide, wallMat));
    /* BOTTOM */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, -0.5, 0.5), vect3D(0, 1, 0),
                                                          rectSide, wallMat));
    /* FRONT BOTTOM */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, -0.6, 0), vect3D(0, 0, -1),
                                                          rectSide, wallMat));
    /* FRONT UPPER */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0.6, 0), vect3D(0, 0, -1),
                                                          rectSide, wallMat));
    /* BACK */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0, 1), vect3D(0, 0, 1),
                                                          rectSide, objectsMat));
}

void Scene::setupSpheres() {
    std::cout << "[C] Scene: Blue Spheres" << std::endl;
    
    skyGradient.push_back( ( Colour(142,158,171).normalizeRGB() ) );
    skyGradient.push_back( ( Colour(238,242,243).normalizeRGB() ) );
    
    std::shared_ptr<Material> sphereMat, wallsMat;
    sphereMat = std::make_shared<Metallic>       ( Colour (150, 150, 150).normalizeRGB(), 0.05 );
    wallsMat = std::make_shared<Metallic>      ( Colour (63, 94, 251).normalizeRGB(), 0.8 );
    
    /* ITEMS */
    vect3D groupTranslation(0.0, -0.05, 0.8);
    sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.0, 0.3, 0.0)+groupTranslation, 0.2, sphereMat));
    sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.0, 0.0, 0.0)+groupTranslation, 0.1, sphereMat));
    sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.0, -0.15, 0.0)+groupTranslation, 0.05, sphereMat));
    
    /* LEFT  */
     sceneObjects.push_back( std::make_unique<Rectangle> (vect3D(-0.5, 0.0, 0.5), vect3D(1, 0, 0),
                                                          1.0, wallsMat));
    /* RIGHT */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0.5, 0.0, 0.5), vect3D(-1, 0, 0),
                                                          1.0, wallsMat));
    /* TOP */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0.5, 0.5), vect3D(0, -1, 0),
                                                          1.0, wallsMat));
    /* BOTTOM */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, -0.5, 0.5), vect3D(0, 1, 0),
                                                          1.0, wallsMat));
    /* BACK */
    sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0, 0), vect3D(0, 0, -1),
                                                          1.0, wallsMat));
    
}

void Scene::plainScene() {
    
    std::cout << "[C] Scene: Plain Scene for debugging" << std::endl;
    
    skyGradient.push_back( ( Colour(242, 252, 254).normalizeRGB() ) );
    skyGradient.push_back( ( Colour(28,  146, 210).normalizeRGB() ) );
    
    std::shared_ptr<Material> plainMat;
    plainMat = std::make_shared<Metallic> ( Colour (215, 210, 204).normalizeRGB(), 1.0 );
    
    /* ITEMS */
    sceneObjects.push_back( std::make_unique<Sphere>   (vect3D(0.0, -0.2, 1.5), 0.3, plainMat));
    sceneObjects.push_back( std::make_unique<Plane> (vect3D(0.0, -0.5, 0.0), vect3D(0, 1, 0), plainMat));
    
}

