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
#include <limits>
#include "Colour.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"

const double infinity = std::numeric_limits<double>::infinity();

class Scene : public Solid {
public:
    
    /// Default scene constructor, pre-loaded with blue sky gradient and one grey spherical object in the middle of the scene.
    /// @discussion https://uigradients.com/#AquaMarine
    Scene();
    
    std::shared_ptr<Camera> camera();
    
    vect3D colourRay(const Ray& r);
    
    virtual bool Intersect (const Ray &ray, recent &recent_Inter, double timeMin, double timeMax) const override;
    
private:
    
    std::vector<colour> skyGradient;
    std::shared_ptr<Camera> sceneCamera;
    std::vector<std::unique_ptr<Solid>> sceneObjects;
};

#endif /* Scene_hpp */
