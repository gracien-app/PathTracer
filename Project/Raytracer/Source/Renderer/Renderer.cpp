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
    for (auto &scene : _presetScenes) scene.reset();
    std::cout << "[D] Renderer: Destructed" << std::endl;
}

void Renderer::invertContinue() {
    continueRender = !continueRender;
}

void Renderer::updateTexture() {
    _outTexture->update(&_outPixels[0]);
}

std::shared_ptr<sf::Sprite> &Renderer::refSprite () {
    return _outSprite;
}

void Renderer::Initialise() {
    
    _outSprite.reset(new sf::Sprite);
    _outTexture.reset(new sf::Texture);
    _outPixels.reserve(_width*_height*4); //MARK: Each pixel = R G B A separately.
    
    if ( _outTexture && _outSprite && _outTexture->create(_width, _height) ) {
        
        _outTexture->setSmooth(false);
        _outSprite->setTexture(*_outTexture);
        _presetScenes.push_back( std::unique_ptr<Scene>( new Scene(_width, _height, 99) ) );
        
    }
    
    else throw "RENDERER Initialise - Can't allocate memory";
    
}

void Renderer::runMultiThreading() {
    
    int nThreads = std::thread::hardware_concurrency()-1;
    int chunkSize = _height / nThreads;
    continueRender = true;
    if (nThreads == 1) renderChunk(0, _height-1);
    else {
    _concThreads.reserve(nThreads);
    for (int i=0; i < nThreads; i++) {
        
        int yStart = i*chunkSize;
        int yEnd;
        if (i == (nThreads-1) ) yEnd = _height-1;
        else yEnd = yStart + chunkSize-1;
        
        _concThreads.push_back( std::thread(&Renderer::renderChunk, this, yStart, yEnd) );
    }
    
    std::cout << " [R] Multi-threaded rendering on " << nThreads << " concurrent threads" << std::endl;
    }
}

bool Renderer::joinAll() {
    
    if (!continueRender) std::cout << " [R] Stopped manually" << std::endl;
    
    bool allJoined = true;
    
    for (auto &thr : _concThreads) {
        if (thr.joinable()) thr.join();
        else allJoined = false;
    }
    
    return allJoined;
    
}

void Renderer::renderChunk(const int &Y, const int &chunkSize) {
    
    int sceneID = 0;
    
    int samplesPerPixel = 1;
    int rayBounces = 2;
    
    sf::Clock renderTime;
    renderTime.restart();
    
    //MARK: Origin of renderer = camera position, camera is inside each scene
    
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
                
                auto pixelRay = _presetScenes[sceneID]->prepRay(x, y);
                outputPixel += _presetScenes[sceneID]->colourRay(pixelRay, rayBounces);
            }
            outputPixel.standardizeOutput(_outPixels, gridPos, samplesPerPixel);
        }
    }
    
    printThreadInfo( renderTime.getElapsedTime() );
    
}

void Renderer::printThreadInfo(const sf::Time &execTime) {
    
    static std::mutex printMutex;
    
    std::lock_guard<std::mutex> printLock(printMutex); // Safer than mutex::lock(), unlocks when out of scope
    
    if (continueRender) {
        std::cout << "  [+] THREAD: " << std::this_thread::get_id() << std::endl;
        std::cout << "      EXECUTION TIME: " << execTime.asSeconds() << " sec" << std::endl;
    }
    
}



