//
//  Scene.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include <memory>
#include "Colour.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

class Scene {
public:
    
    /// Default scene constructor, pre-loaded with blue sky gradient and one grey spherical object in the middle of the scene.
    /// @discussion https://uigradients.com/#AquaMarine
    Scene();
    
    vect3D colourRay(const Ray& r);
    
private:
    
    std::vector<colour> skyGradient;
    std::shared_ptr<Camera> sceneCamera;
    std::vector<std::unique_ptr<Solid>> sceneObjects;
};

#endif /* Scene_hpp */
