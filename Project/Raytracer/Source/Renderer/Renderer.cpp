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

void Renderer::Initialise(std::shared_ptr<std::vector<std::map<std::string, int>>> &defaultPresets,
                          const int &nThreads) {
    
    _outSprite.reset(new sf::Sprite);
    _outTexture.reset(new sf::Texture);
    _presets = defaultPresets;
    
    _imageChunks.reserve(nThreads);
    _outPixels.reserve(_width*_height*4); //MARK: Each pixel = R G B A separately.
    
    if ( _outTexture && _outSprite && _outTexture->create(_width, _height) ) {
        
        _outSprite->setTexture(*_outTexture);
        
        for (auto &preset : *defaultPresets) {
            _presetScenes.push_back( std::unique_ptr<Scene>( new Scene(_width, _height, preset.at("ID")) ) );
        }
        
        distributeChunks(nThreads);
            
    }
    
    else throw "RENDERER Initialise - Can't allocate memory";
}

void Renderer::distributeChunks(const int &nThreads) {
    
    int chunkSize = _height / nThreads;
    
    for (int i=0; i < nThreads; i++) {
    
        int yStart = i*chunkSize;
        int yEnd;
        if (i == (nThreads-1) ) yEnd = _height-1;
        else yEnd = yStart + chunkSize-1;
    
        _imageChunks.push_back(Chunk(yStart, yEnd));
    }
    
    std::cout << " [R] Multi-threaded rendering on " << nThreads << " concurrent threads" << std::endl;
}

void Renderer::runChunks(const int &nPreset) {
    
    int counter = 0;
    _stopExecution = false;
    
    auto samples = _presets->at(nPreset).at("SAMPLES");
    auto bounces = _presets->at(nPreset).at("BOUNCES");
        
    for (auto &chunk : _imageChunks) {
        chunk.workerThread = std::thread(&Renderer::renderChunk, this, counter++, nPreset, samples, bounces );
        chunk._working = true;
    }
    
}

bool Renderer::joinAll() {
    
    if (_stopExecution) std::cout << " [R] Stopped manually" << std::endl;

    bool allJoined = true;

    for (auto &chunk : _imageChunks) {
        if( !chunk.joinChunk() ) allJoined = false;
    }
    
    return allJoined;
    
}

void Renderer::stopAll() {
    _stopExecution = true;
}

bool Renderer::allFinished() {
    for (auto &chunk : _imageChunks) {
        if (chunk.isWorking()) return false;
    }
    return true;
}

void Renderer::renderChunk(const int &chunkID, const int &presetID, const int &samplesN, const int &bouncesN) {
    
    auto chunkEnd = _imageChunks[chunkID].rangeEnd();
    auto chunkStart = _imageChunks[chunkID].rangeStart();
    
    sf::Clock renderTime;
    renderTime.restart();
    
    //MARK: Origin of renderer = camera position, camera is inside each scene
    
    for (int j=chunkStart; j<=chunkEnd; j++) {
        for (int i=0; i<_width; i++) {
            
            if (_stopExecution) break;
            
            int gridPos = i+(j*_width);
            //MARK: NON-SQUARE RESOLUTION FIX gridPos = i+(j x width) not (j x height)
            //MARK: Pixels are transfered from continuous RGBA data, not by rows & columns

            auto outputPixel = colour(0, 0, 0);
            
            for (int s=0; s<samplesN; s++) {
                
                auto x = ( double(i)+randomNumber<double>() ) / (_width-1);
                auto y = ( double(j)+randomNumber<double>() ) / (_height-1);
                //MARK: x and y are to multiply the vertical and horizontal projection vectors to the correct pixel.
                
                auto pixelRay = _presetScenes[presetID]->prepRay(x, y);
                outputPixel += _presetScenes[presetID]->colourRay(pixelRay, bouncesN);
            }
            outputPixel.standardizeOutput(_outPixels, gridPos, samplesN);
        }
    }
    
//    _imageChunks[chunkID].taskFinished(renderTime.getElapsedTime(), printMutex, _stopExecution);
    _imageChunks[chunkID]._working = false;
}

void Renderer::updateTexture() {
    _outTexture->update(&_outPixels[0]);
}

std::shared_ptr<sf::Sprite> &Renderer::refSprite () {
    return _outSprite;
}
