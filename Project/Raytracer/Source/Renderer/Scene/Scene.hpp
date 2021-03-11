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
    
private:
    
    vect3D _skyColour;
    vect3D _origin;
    
    Camera _eye;
    
};

#endif /* Scene_hpp */
