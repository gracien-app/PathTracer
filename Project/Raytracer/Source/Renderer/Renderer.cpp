//
//  Renderer.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer(const uint &windowWidth, const uint &windowHeight) : _width(windowWidth), _height(windowHeight) {
    
    std::cout << "[C] Renderer: Created" << std::endl;
    
}

Renderer::~Renderer() {
    
    std::cout << "[D] Renderer: Terminated" << std::endl;
    
}

void Renderer::Initialise() {
    
    outSprite.reset(new sf::Sprite);
    outTexture.reset(new sf::Texture);
    outPixels.reserve(_width*_height*4); //MARK: Each pixel is stored as R G B A separately.
    
    if ( outTexture && outSprite && outTexture->create(_width, _height) ) {
        
        outTexture->setSmooth(false);
        outSprite->setTexture(*outTexture);
        preScenes.push_back( std::unique_ptr<Scene>( new Scene(_width, _height, 99) ) );
        
    }
    
    else throw "RENDERER Initialise - Can't allocate memory";
    
}

void Renderer::Render() {
    
    busy = true;
    
    int sceneID = 0;
    
    int samplesPerPixel = 3;
    int rayBounces = 5;
    
    sf::Clock renderTime;
    renderTime.restart();
    
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
                
                auto pixelRay = preScenes[sceneID]->prepRay(x, y);
                outputPixel += preScenes[sceneID]->colourRay(pixelRay, rayBounces);
            }
            outputPixel.standardizeOutput(outPixels, gridPos, samplesPerPixel);
        }
    
        if (j % 100 == 0) {
            std::cout << "PROGRESS: " << int((j/(_height-1))*100) << "%" << std::endl;
        }
    }
    std::cout << "PROGRESS: 100%" << std::endl;
    std::cout << "EXECUTION TIME: " << renderTime.getElapsedTime().asSeconds() << " sec" << std::endl;
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
