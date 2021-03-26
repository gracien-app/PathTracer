//
//  Renderer.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "main.h"
#include "Scene.hpp"

class Renderer {
public:
    Renderer(const uint &width, const uint &height);
    ~Renderer();
    
    void init();
    void render();
    void updateTexture();
    
    bool isBusy() const;
    
    std::shared_ptr<sf::Sprite> &Sprite ();
    
private:
    
    bool busy;
    double _width;
    double _height;
    
    std::vector<sf::Uint8> outPixels;
    std::shared_ptr<sf::Sprite> outSprite;
    std::unique_ptr<sf::Texture> outTexture;
    std::vector<std::shared_ptr<Scene>> preScenes;
    
};

#endif /* Renderer_hpp */
