//
//  Scene.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "main.h"
#include "Sphere.hpp"

class Scene {
public:
    Scene();
    Scene(const vect3D &pointOfView, const vect3D &spaceColour, const double focalLength);
    
    vect3D colourRay(const Ray& r); //to not alter the ray in any way
    Camera& getCamera();
    
private:
    vect3D _sky[2];
    Camera _camera; //Point-of-view
    std::vector<Sphere> spheres;
};

#endif /* Scene_hpp */
