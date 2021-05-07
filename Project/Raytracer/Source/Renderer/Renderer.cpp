//
//  Renderer.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer(const uint &windowWidth, const uint &windowHeight) : _width(windowWidth),
                                                                        _height(windowHeight) {
    
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
        preScenes.push_back( std::unique_ptr<Scene>( new Scene(_width, _height, 1) ) );
        
    }
    
    else throw "RENDERER Initialise - Can't allocate memory";
    
}

void Renderer::runMultiThreading() {
    
    int nThreads = 4;
    concurrentThreads.reserve(nThreads);
    int chunkSize = _height / nThreads;
    continueRender = true;
    
    for (int i=0; i < nThreads; i++) {
        
        int yStart = i*chunkSize;
        int yEnd;
        if (i == (nThreads-1) ) yEnd = _height;
        else yEnd = yStart + chunkSize-1;
        
        concurrentThreads.push_back( std::thread(&Renderer::Render, this, yStart, yEnd) );
    }
    
}

void Renderer::joinAll() {
    for (auto &thr : concurrentThreads) if (thr.joinable()) thr.join();
}

void Renderer::invertContinue() {
    continueRender = !continueRender;
}

void Renderer::Render(const uint &Y, const uint &chunkSize) {
    
    busy = true;
    
    int sceneID = 0;
    
    int samplesPerPixel = 5;
    int rayBounces = 5;
    
    sf::Clock renderTime;
    renderTime.restart();
    
    //MARK: Origin of renderer = camera position from which we see the scene
    
    for (int j=Y; j<=(chunkSize); j++) {
        for (int i=0; i<(_width); i++) {
            if (!continueRender) break;
            
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
    }
    if (!continueRender)  std::cout << "Rendering Terminated" << std::endl;
    std::cout << "THREAD: " << std::this_thread::get_id() << std::endl;
    std::cout << "|_EXECUTION TIME: " << renderTime.getElapsedTime().asSeconds() << " sec" << std::endl;
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

