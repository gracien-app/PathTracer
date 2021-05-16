//
//  Scene.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Cube.hpp"
#include "Camera.hpp"

class Scene : public Camera {
public:
    
    // MARK: Constructors & Destructor
    ~Scene();
    Scene(const int &width, const int &height, int &variant);
    
    
    // MARK: Methods
    void plainScene();
    void setupSpheres();
    void setupCornell(const bool &reflective = false);
    
    Colour colourRay(const Ray& r, const int &rayBounces) const;
    
    
private:
    
    // MARK: Methods
    bool intersectScene (const Ray &ray, intersection &recent_Inter, const double &tMin, const double &tMax) const;
    
    // MARK: Data
    std::vector<Colour> skyGradient;
    std::vector<std::unique_ptr<Solid> > sceneObjects;
};

#endif /* Scene_hpp */
