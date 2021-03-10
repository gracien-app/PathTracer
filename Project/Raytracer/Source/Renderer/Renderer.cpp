//
//  Renderer.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer() {
    outTexture.reset(new sf::Texture);
    outSprite.reset(new sf::Sprite);
    
    std::cout << "[C] Renderer: Created" << std::endl;
};
Renderer::~Renderer() {
    std::cout << "[D] Renderer: Terminated" << std::endl;
}

void Renderer::init(sf::Vector2u resolution) {
    res.reset(new sf::Vector2u(resolution.x, resolution.y));
    if (!res) throw "Can't inherit resolution to Renderer";
    
    outPixels.reserve(res->x*res->y*4); //because we store RGBA separately, that's why 4x
    if (!outTexture->create(res->x, res->y)) throw "Can't sf::Texture::Create";
    
    int width = res->x;
    int height = res->y;
    
    for (int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
    
            auto r = float(i) / width;
            auto g = float(j) / height;
            auto b = 0.8;
    
            int gridPos = i+(j*height);
            outPixels[4*gridPos+0] = int(r*255.999);
            outPixels[4*gridPos+1] = int(g*255.999);
            outPixels[4*gridPos+2] = int(b*255.999);
            outPixels[4*gridPos+3] = int(255);
            //4* because one pixel consists of RGBA color components
            //+x to access specific component
            //.999 to compensate lack of <= width, height
        }
    }
    
    outTexture->update(&outPixels[0]);
    outSprite->setTexture(*outTexture);
}

sf::Sprite* Renderer::getSprite() {
    return outSprite.get();
}
