//
//  Renderer.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer(const uint &width, const uint &height) : _width(width), _height(height) {
    
    outTexture.reset(new sf::Texture);
    outSprite.reset(new sf::Sprite);
    
    
    preScenes.push_back(std::shared_ptr<Scene>(new Scene(width,height)));
    
    std::cout << "[C] Renderer: Created" << std::endl;
};

Renderer::~Renderer() {
    std::cout << "[D] Renderer: Terminated" << std::endl;
}

void Renderer::init() {
    
    busy = true;
    
    outPixels.reserve(_width*_height*4); //MARK: because each pixel is stored as partials R G B A.
     
    if (outTexture && outTexture->create(_width, _height)) {
        outTexture->setSmooth(false);
        outSprite->setTexture(*outTexture);
    }
    else throw "Can't initialize - sf::Texture::Create failure";
    
    busy = false;
}

void Renderer::render() {
    
    busy = true;
    
    auto currentScene = preScenes.at(0);
    
    int samplesPerPixel = 10;
    int rayBounces = 5;
    
    //MARK: Origin of renderer = camera position from which we see the scene
    
    
    for (int j=0; j<(_height); j++) {
        for (int i=0; i<(_width); i++) {
            
            int gridPos = i+(j*_width);
            //MARK: CRUCIAL CUSTOM RESOLUTION FIX - gridPos = i+(j x width) not (j x height)
            //MARK: Pixels are transfered from continuous array of data, not by coordinates

            auto outputPixel = colour(0, 0, 0);
            
            for (int s=0; s<samplesPerPixel; s++) {
                
                auto x = ( double(i)+randomNumber<double>() ) / (_width-1);
                auto y = ( double(j)+randomNumber<double>() ) / (_height-1);
                //MARK: x and y are to multiply the vertical and horizontal projection vectors to the correct pixel.
                
                auto pixelRay = currentScene->prepRay(x, y);
                outputPixel += currentScene->colourRay(pixelRay, rayBounces);
            }
            outputPixel.standardizeOutput(outPixels, gridPos, samplesPerPixel);
        }
    
        if (j % 100 == 0) {
            std::cout << "PROGRESS: " << int((j/(_height-1))*100) << "%" << std::endl;
        }
    }
    std::cout << "PROGRESS: 100%\n  Render FINISHED" << std::endl;
    updateTexture();
}

void Renderer::updateTexture() {
    outTexture->update(&outPixels[0]);
}

bool Renderer::isBusy() const {
    return busy;
}

std::shared_ptr<sf::Sprite> &Renderer::Sprite () {
    return outSprite;
}
