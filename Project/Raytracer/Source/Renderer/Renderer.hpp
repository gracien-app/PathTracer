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
    
    void init(const sf::Vector2u &resolution);
    void render();
    void updateTexture();
    
    sf::Sprite* getSprite();
    
    
private:
    
    double _width;
    double _height;
    
    vect3D _origin;
    
    std::vector<sf::Uint8> outPixels;
    std::unique_ptr<sf::Sprite> outSprite;
    std::unique_ptr<sf::Texture> outTexture;
    
};

#endif /* Renderer_hpp */
