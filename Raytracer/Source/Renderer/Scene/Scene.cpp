//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene(const int &width, const int &height, int &variant) : Camera(vect3D(0.0,0.0,0.0), 1.0, width, height) {
    
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
            
        case 4:
            lightScene();
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
    
    Intersection recentInter;
    
    if (rayBounces == 0) return Colour(0,0,0);
    
    if (intersectScene(r, recentInter, 0.0001, infinity<double>)) {
        
        Colour totalColour;
        Ray reflectedRay;
        
        if (recentInter.material->reflect(r, reflectedRay, recentInter, totalColour)) {
            return totalColour * colourRay(reflectedRay, rayBounces-1);
        }
        
        if (recentInter.material->emit(recentInter, totalColour)) return totalColour;
        
        else return Colour(0,0,0);
        
    }
    
    else {
        
        auto unit_R = r.getDir(); //MARK:: Y can be between <-1,1> (projection plane height = 2)
        auto t = (unit_R.y()+1) * 0.5; //MARK: Limiting the range to <0,1>
        return Colour(_skyGradient[1]*(1-t) + _skyGradient[0]*t); //MARK: Horizontal gradient formula (header)
        
    }
}

Colour Scene::colourDistance(const Ray &r) const {
    
    Intersection recentInter;
    
    if (intersectScene(r, recentInter, 0.0001, infinity<double>)) {
        
        auto differVec = recentInter.position - r.getOrigin();
        auto distance = differVec.lengthSquared() * 0.5;
        
        distance = clamp(distance, 0.05, 0.996);
        
        return Colour(1.0-distance, 1.0-distance, 1.0-distance);
        
    }
    
    return Colour(0.0, 0.0, 0.0);
    
}

Colour Scene::colourNormals(const Ray &r) const {
    
    Intersection recentInter;
    
    if (intersectScene(r, recentInter, 0.0001, infinity<double>)) {
        
        auto temp = recentInter.outNormal;
        
        return 0.5*Colour(temp.x()+1, temp.y()+1 , temp.z()+1 );
        
    }
    
    return Colour(0.0, 0.0, 0.0);
    
}

Colour Scene::colourTurbo(const Ray &r, const float (&turbo_map)[256][3]) const {
    
    Intersection recentInter;
    
    if (intersectScene(r, recentInter, 0.0001, infinity<double>)) {
        
        auto depth = clamp(recentInter.time, 0.0, 1.0);
        auto index = int((1.0-depth)*256);
        
        return Colour(turbo_map[index][0], turbo_map[index][1], turbo_map[index][2]);
        
    }
    
    return Colour(0.0, 0.0, 0.0);
    
}

bool Scene::intersectScene (const Ray &ray, Intersection &recent_Inter, const double &tMin, const double &tMax) const {
    Intersection tempRecent;
    bool didIntersect = false;
    auto closestIntersect = tMax;

    for (const auto& object : _sceneObjects) {
        if ( object->Intersect(ray, tempRecent, tMin, closestIntersect) ) {
            didIntersect = true;
            closestIntersect = tempRecent.time;
            recent_Inter = tempRecent;
        }
    }
    return didIntersect;
}

void Scene::setupCornell(const bool &reflective) {
    
    std::string message = "[C] Scene: Cornell Box";
    if (reflective) message += " (Reflective)";
    else message += " (Matte)";
    std::cout << message << std::endl;
    
    const double rectSide = 1;
    
    _skyGradient.push_back( ( Colour(1.0, 1.0, 1.0) ) );
    _skyGradient.push_back( ( Colour(1.0, 1.0, 1.0) ) );
    
    std::shared_ptr<Material> leftWallMat, rightWallMat, wallMat, objectsMat;
    
    if (reflective) {
        leftWallMat =   std::make_shared<Metallic>    ( Colour (252,70, 107).normalizeRGB(), 1.0 );
        rightWallMat =  std::make_shared<Metallic>    ( Colour (63, 94, 251).normalizeRGB(), 1.0 );
        wallMat =       std::make_shared<Metallic>    ( Colour (255,255,255).normalizeRGB(), 0.2 );
        objectsMat =    std::make_shared<Metallic>    ( Colour (255,255,255).normalizeRGB(), 0.05);
    }
    else {
        leftWallMat =   std::make_shared<Diffused>    ( Colour (252,70, 107).normalizeRGB() );
        rightWallMat =  std::make_shared<Diffused>    ( Colour (63, 94, 251).normalizeRGB() );
        wallMat =       std::make_shared<Diffused>    ( Colour (255,255,255).normalizeRGB() );
        objectsMat =    std::make_shared<Diffused>    ( Colour (255,255,255).normalizeRGB() );
    }
    
    /* ITEMS */
    _sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.2, -0.3, -0.8), 0.2, objectsMat));
    _sceneObjects.push_back( std::make_unique<Cube>   (vect3D(-0.2, -0.35, -0.8), 0.3, objectsMat, true));
    
    
    /* LEFT  */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(-0.5, 0, -0.5), vect3D(1, 0, 0),
                                                          rectSide, leftWallMat));
    /* RIGHT */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0.5, 0, -0.5), vect3D(-1, 0, 0),
                                                          rectSide, rightWallMat));
    /* TOP */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0.5, -0.5), vect3D(0, -1, 0),
                                                          rectSide, wallMat));
    /* BOTTOM */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, -0.5, -0.5), vect3D(0, 1, 0),
                                                          rectSide, wallMat));
    /* FRONT BOTTOM */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, -0.6, 0), vect3D(0, 0, -1),
                                                          rectSide, wallMat));
    /* FRONT UPPER */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0.6, 0), vect3D(0, 0, -1),
                                                          rectSide, wallMat));
    /* BACK */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0, -1), vect3D(0, 0, 1),
                                                          rectSide, objectsMat));
}

void Scene::setupSpheres() {
    std::cout << "[C] Scene: Blue Spheres" << std::endl;
    
    _skyGradient.push_back( ( Colour(142,158,171).normalizeRGB() ) );
    _skyGradient.push_back( ( Colour(238,242,243).normalizeRGB() ) );
    
    std::shared_ptr<Material> sphereMat, wallsMat;
    sphereMat = std::make_shared<Metallic>       ( Colour (150, 150, 150).normalizeRGB(), 0.05 );
    wallsMat = std::make_shared<Metallic>      ( Colour (63, 94, 251).normalizeRGB(), 0.8 );
    
    /* ITEMS */
    vect3D groupTranslation(0.0, -0.05, -0.8);
    _sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.0, 0.3, 0.0)    +groupTranslation, 0.2, sphereMat));
    _sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.0, -0.01, 0.0)  +groupTranslation, 0.1, sphereMat));
    _sceneObjects.push_back( std::make_unique<Sphere> (vect3D(0.0, -0.17, 0.0)  +groupTranslation, 0.05, sphereMat));
    
    /* LEFT  */
     _sceneObjects.push_back( std::make_unique<Rectangle> (vect3D(-0.5, 0.0, -0.5), vect3D(1, 0, 0),
                                                          1.0, wallsMat));
    /* RIGHT */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0.5, 0.0, -0.5), vect3D(-1, 0, 0),
                                                          1.0, wallsMat));
    /* TOP */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0.5, -0.5), vect3D(0, -1, 0),
                                                          1.0, wallsMat));
    /* BOTTOM */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, -0.5, -0.5), vect3D(0, 1, 0),
                                                          1.0, wallsMat));
    /* BACK */
    _sceneObjects.push_back( std::make_unique<Rectangle>  (vect3D(0, 0, 0), vect3D(0, 0, -1),
                                                          1.0, wallsMat));
    
}

void Scene::plainScene() {
    
    std::cout << "[C] Scene: Plain Scene for debugging" << std::endl;
    
    _skyGradient.push_back( ( Colour(242, 252, 254).normalizeRGB() ) );
    _skyGradient.push_back( ( Colour(28,  146, 210).normalizeRGB() ) );
    
    std::shared_ptr<Material> plainMat;
    plainMat = std::make_shared<Diffused> ( Colour (215, 210, 204).normalizeRGB() );
    
    /* ITEMS */
    _sceneObjects.push_back( std::make_unique<Sphere>   (vect3D(0.0, -0.2, -1.5), 0.3, plainMat));
    _sceneObjects.push_back( std::make_unique<Rectangle>(vect3D(0.0, -0.5, 0.0), vect3D(0, 1, 0), 10, plainMat));
    
}

void Scene::lightScene() {
    
    std::cout << "[C] Scene: Lights Scene for debugging" << std::endl;
    
    _skyGradient.push_back( Colour(0.0, 0.0, 0.0) );
    _skyGradient.push_back( Colour(0.0, 0.0, 0.0) );
    
    std::shared_ptr<Material> wallsMat, ballsMat, whiteEmit;
    
    wallsMat = std::make_shared<Diffused> ( Colour (40, 40, 40).normalizeRGB());
    ballsMat = std::make_shared<Metallic>( Colour(0.1, 0.1, 0.1), 1.0);
    
    whiteEmit = std::make_shared<EmissiveNormal> ( 1.0 );
  
    _sceneObjects.push_back( std::make_unique<Sphere>(vect3D(0.0, -0.15, -0.5), 0.1, whiteEmit) );

    /// MARK: Room - Ground at -0.3
    _sceneObjects.push_back(std::make_unique<Plane>(vect3D(0.0, -0.165, 0.0), vect3D(0.0, 1.0, 0.0), wallsMat));

    _sceneObjects.push_back(std::make_unique<Plane>(vect3D(0.0, 0.165, 0.0), vect3D(0.0, -1.0, 0.0), wallsMat));

    _sceneObjects.push_back(std::make_unique<Plane>(vect3D(-0.165, 0.0, 0.0), vect3D(1.0, 0.0, 0.0), wallsMat));

    _sceneObjects.push_back(std::make_unique<Plane>(vect3D(0.165, 0.0, 0.0), vect3D(-1.0, 0.0, 0.0), wallsMat));

    std::shared_ptr<Material> fullyRefl = std::make_shared<Metallic>(Colour(1.0, 1.0, 1.0), 0.0);

    _sceneObjects.push_back(std::make_unique<Rectangle>(vect3D(0.0, 0.0, -1.0), vect3D(0.0, 0.0, 1.0), 2, fullyRefl));

    _sceneObjects.push_back(std::make_unique<Rectangle>(vect3D(0.0, 0.0, 1.0), vect3D(0.0, 0.0, -1.0), 2, fullyRefl));

    
}

