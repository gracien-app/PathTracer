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
    Scene(const int &width, const int &height, const int &variant);
    ~Scene();
    
    // MARK: Methods
    void setupCornell();
    void setupTest();
    void fastTest();
    
    colour colourRay(const Ray& r, int rayBounces);
    
    
private:
    
    // MARK: Methods
    bool intersectScene (const Ray &ray, collision &recent_Inter, const double &tMin, const double &tMax) const;
    
    // MARK: Data
    std::vector<colour> skyGradient;
    std::vector<std::unique_ptr<Solid> > sceneObjects;
};

#endif /* Scene_hpp */
