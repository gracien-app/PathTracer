//
//  Scene.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Plane.hpp"
#include "Sphere.hpp"
#include "Disc.hpp"
#include "Camera.hpp"

class Scene : public Camera {
public:
    
    /// Default scene constructor, pre-loaded with blue sky gradient and one grey spherical object in the middle of the scene.
    /// @discussion https://uigradients.com/#AquaMarine
    Scene(const int &width, const int &height);
    
    vect3D colourRay(const Ray& r, int rayBounces);
    bool intersectScene (const Ray &ray, collision &recent_Inter, const double &timeMin, const double &timeMax) const;
    
private:
    
    std::vector<colour> skyGradient;
    std::vector<std::unique_ptr<Solid>> sceneObjects;
};

#endif /* Scene_hpp */
