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

void Renderer::Initialise(std::shared_ptr<std::vector<std::map<std::string, int>>> &userPresets,
                          const int &nThreads) {
    
    _outSprite.reset(new sf::Sprite);
    _outTexture.reset(new sf::Texture);
    
    _workerThreads.reserve(nThreads);
    _outPixels.reserve(_width*_height*4); //MARK: Each pixel = R G B A separately.
    
    if ( _outTexture && _outSprite && _outTexture->create(_width, _height) ) {
        
        _outSprite->setTexture(*_outTexture);
        
        for (auto &preset : *userPresets) {
            _presetScenes.push_back(std::make_unique<Scene>(_width, _height, preset.at("ID")));
        }
        
        distributeChunks(nThreads, 64);
            
    }
    
    else throw "RENDERER Initialise - Can't allocate memory";
}

void Renderer::distributeChunks(const int &nThreads, const int &bucketSize) {
    
    _chunkIndex = 0;
    
    for (int j=0; j<_height; j+=bucketSize) {
        for (int i=0; i<_width; i+=bucketSize) {
            Range temp;
            
            temp.start.first = i;
            temp.end.first = i+bucketSize-1;
        
            temp.start.second = j;
            temp.end.second = j+bucketSize-1;
            
            _chunksVector.push_back(temp);
        }
    }
    
//    int chunkSize = _height / nThreads;
    
    for (int i=0; i < nThreads; i++) {
    
//        int yStart = i*chunkSize;
//        int yEnd;
//        if (i == (nThreads-1) ) yEnd = _height-1;
//        else yEnd = yStart + chunkSize-1;
    
        _workerThreads.push_back(Worker());
    }
    
    std::cout << " [R] Multi-threaded rendering on " << nThreads << " concurrent threads" << std::endl;
}

void Renderer::runChunks(const int &nPreset, const int &samples, const int &bounces) {
    
    _samples = samples;
    _bounces = bounces;
    _stopExecution = false;
    
    for (auto &worker : _workerThreads) {
        worker.Thread = std::thread(&Renderer::renderChunk, this, worker.getID(), nPreset );
        worker.busy = true;
    }
    
}

bool Renderer::joinAll() {
    for (auto &worker : _workerThreads) {
        if( !worker.joinWorker() ) return false;
    }
    return true;
}

void Renderer::stopAll() {
    _stopExecution = true;
}

bool Renderer::allFinished() {
    for (auto &worker : _workerThreads) {
        if (worker.isWorking()) return false;
    }
    return true;
}
void Renderer::acquireChunk(Worker &thread) {
    acquireMtx.lock();
    
    if (_chunkIndex <= (_chunksVector.size()-1)) {
        thread.busy = true;
        thread.workerRange = _chunksVector[_chunkIndex];
        _chunkIndex++;
        
        acquireMtx.unlock();
        return;
    }
    
    else {
        _chunkIndex = -1;
        thread.busy = false;
        acquireMtx.unlock();
        return;
    }
}

void Renderer::resetChunksIndex() {
    _chunkIndex = 0;
}

void Renderer::renderChunk(const int &chunkID, const int &presetID) {
    
    while (true) {
        
        acquireChunk(_workerThreads[chunkID]);
        
        auto chunkEnd = _workerThreads[chunkID].workerRange.end;
        auto chunkStart = _workerThreads[chunkID].workerRange.start;
        
        for (int j=chunkStart.second; j<=chunkEnd.second; j++) {
            for (int i=chunkStart.first; i<=chunkEnd.first; i++) {
                
                if (_stopExecution || !_workerThreads[chunkID].isWorking()) {
                    _workerThreads[chunkID].busy = false;
                    return;
                }
                
                int gridPos = i+(j*_width);
                //MARK: NON-SQUARE RESOLUTION FIX gridPos = i+(j x width) not (j x height)
                //MARK: Pixels are transfered from continuous RGBA data, not by rows & columns

                auto outputPixel = Colour(0, 0, 0);
                
                for (int s=0; s<_samples; s++) {
                    
                    auto x = ( double(i)+randomNumber<double>() ) / (_width-1);
                    auto y = ( double(j)+randomNumber<double>() ) / (_height-1);
                    //MARK: x and y are to multiply the vertical and horizontal projection vectors to the correct pixel.
                    
                    auto pixelRay = _presetScenes[presetID]->prepRay(x, y);
                    outputPixel += _presetScenes[presetID]->colourRay(pixelRay, _bounces);
                    
                }
                
                outputPixel.standardiseOutput(_outPixels, gridPos, _samples);
                
            }
        }
    }
}

void Renderer::updateTexture() {
    _outTexture->update(&_outPixels[0]);
}

std::shared_ptr<sf::Sprite> &Renderer::refSprite () {
    return _outSprite;
}
