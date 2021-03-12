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

class Scene {
public:
    Scene();
    Scene(const vect3D &pointOfView, const vect3D &spaceColour, const double focalLength);
    
    vect3D spaceColour(const Ray& r); //to not alter the ray in any way
    Camera& getCamera();
    
private:
    vect3D _space;
    Camera _pov; //Point-of-view
    
};

#endif /* Scene_hpp */
