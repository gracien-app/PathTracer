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

class Renderer {
public:
    Renderer();
    ~Renderer();
    
    void init(sf::Vector2u resolution);
    sf::Sprite* getSprite();
    
    
private:
    
    std::vector<sf::Uint8> outPixels;
    
    std::unique_ptr<sf::Vector2u> res;
    std::unique_ptr<sf::Sprite> outSprite;
    std::unique_ptr<sf::Texture> outTexture;
    
    vect3D origin;
    
    
    
};

#endif /* Renderer_hpp */
