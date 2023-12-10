//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <PathTracer/Renderer/Renderer.hpp>
#include <PathTracer/Renderer/Scene/Scene.hpp>
#include <PathTracer/Renderer/Utilities/Vectors.hpp>
#include <PathTracer/Renderer/Utilities/Colour.hpp>


#include <iostream>
#include <map>

// MARK: - Constructors & Destructors

Renderer::Renderer(const uint &windowWidth, const uint &windowHeight) : _resolution(windowWidth, windowHeight) {
    std::cout << "[C] Renderer: Created" << std::endl;
}


Renderer::~Renderer() {
    for (auto &scene : _presetScenes) scene.reset();
    std::cout << "[D] Renderer: Destructed" << std::endl;
}


// MARK: - Methods

void Renderer::Initialise(std::shared_ptr<std::vector<std::map<std::string, int>>> &userPresets,
                          const int &nThreads) {

    _outTexture.reset(new sf::Texture);

    _workerThreads.reserve(nThreads);
    
    // Each pixel split into R G B A channels.
    _outPixels.reserve(_resolution.x * _resolution.y * 4);
    
    if ( _outTexture && _outTexture->create(_resolution) ) {

        _outSprite = std::make_shared<sf::Sprite>(*_outTexture);
        
        for (auto &preset : *userPresets) {
            _presetScenes.push_back(std::make_unique<Scene>(_resolution.x, _resolution.y, preset.at("ID")));
        }
        
        distributeChunks(nThreads, 64);
    }
    
    else throw "RENDERER Initialise - Can't allocate memory";
}

    // MARK: -

void Renderer::distributeChunks(const int &nThreads, const int &bucketSize) {
    
    for (int j=0; j<_resolution.y; j+=bucketSize) {
        for (int i=0; i<_resolution.x; i+=bucketSize) {
            Range temp;
            
            temp.start.first = i;
            temp.end.first = i+bucketSize-1;
        
            temp.start.second = j;
            temp.end.second = j+bucketSize-1;
            
            _chunksVector.push_back(temp);
        }
    }
    
    for (int i=0; i < nThreads; i++) _workerThreads.emplace_back();
    
    std::cout << " [R] Multi-threaded rendering on " << nThreads << " concurrent threads" << std::endl;
}


void Renderer::runChunks(const int &nPreset, const int &samples, const int &bounces, const Mode render_mode, bool preview) {
    
    _chunkIndex = 0;
    _samples = samples;
    _bounces = bounces;
    _stopExecution = false;
    
    for (auto &worker : _workerThreads) {
        if (preview) worker.run(std::thread(&Renderer::renderChunkPreview, this, worker.getID(), nPreset));
        else worker.run(std::thread(&Renderer::renderChunk, this, worker.getID(), nPreset, render_mode));
        worker.busy = true;
    }
    
}


bool Renderer::acquireChunk(Worker &thread) {
    
    acquireMtx.lock();
    
    if (_chunkIndex <= (_chunksVector.size()-1)) {
        thread.busy = true;
        thread.workerRange = _chunksVector[_chunkIndex++];
        acquireMtx.unlock();
        return true;
    }
    
    else {
        _chunkIndex = -1;
        thread.busy = false;
        acquireMtx.unlock();
        return false;
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


// MARK: -

void Renderer::moveCamera(const vect3D& offset, const int &sceneID) {
    _presetScenes[sceneID]->Move(offset);
}


void Renderer::renderChunkPreview(const int &chunkID, const int &sceneID) {
    
    int loopOffset = 1;
    auto wRatio = 1.0 / (_resolution.x-1);
    auto hRatio = 1.0 / (_resolution.y-1);
    
    while (acquireChunk(_workerThreads[chunkID])) {
        
        auto chunkEnd = _workerThreads[chunkID].workerRange.end;
        auto chunkStart = _workerThreads[chunkID].workerRange.start;
        
        for (int j = chunkStart.second; j <= chunkEnd.second; j += loopOffset) {
            for (int i = chunkStart.first; i <= chunkEnd.first; i += loopOffset) {
                
                if (_stopExecution)
                {
                    _workerThreads[chunkID].busy = false;
                    return;
                }
                
                int gridPos = i+(j*_resolution.x);
                auto outputPixel = Colour(0, 0, 0);
                    
                auto x = i * wRatio;
                auto y = j * hRatio;
                    
                auto pixelRay = _presetScenes[sceneID]->prepRay(x, y);
                    
                outputPixel += _presetScenes[sceneID]->traverseTurbo(pixelRay, turbo_srgb_floats);

                outputPixel.standardiseOutputPreview(_outPixels, gridPos);
                
            }
        }
    }
}


void Renderer::renderChunk(const int &chunkID, const int &sceneID, const Mode render_mode) {
    
    while (acquireChunk(_workerThreads[chunkID])) {
        
        auto chunkEnd = _workerThreads[chunkID].workerRange.end;
        auto chunkStart = _workerThreads[chunkID].workerRange.start;
        
        for (int j=chunkStart.second; j<=chunkEnd.second; j+=1) {
            for (int i=chunkStart.first; i<=chunkEnd.first; i+=1) {
                
                if (_stopExecution) {
                    _workerThreads[chunkID].busy = false;
                    return;
                }
                
                int gridPos = i+(j*_resolution.x);

                auto outputPixel = Colour(0, 0, 0);
                
                for (int s = 0; s < _samples; s++) {
                    
                    auto x = ( double(i)+randomNumber<double>() ) / (_resolution.x-1);
                    auto y = ( double(j)+randomNumber<double>() ) / (_resolution.y-1);
                    
                    auto pixelRay = _presetScenes[sceneID]->prepRay(x, y);
                    
                    switch (render_mode) {
                        case STANDARD:
                            outputPixel += _presetScenes[sceneID]->traverseRegular(pixelRay, _bounces);
                            break;
                            
                        case DEPTH:
                            outputPixel += _presetScenes[sceneID]->traverseDepth(pixelRay);
                            break;
                            
                        case NORMALS:
                            outputPixel += _presetScenes[sceneID]->traverseNormal(pixelRay);
                            break;
                            
                        case THERMOGRAPHY:
                            outputPixel += _presetScenes[sceneID]->traverseTurbo(pixelRay, turbo_srgb_floats);
                            break;
                    }    
                }
                
                outputPixel.standardiseOutput(_outPixels, gridPos, _samples);
            }
        }
    }
}


void Renderer::updateTexture() {
    _outTexture->update((&_outPixels[0]));
}


std::shared_ptr<sf::Sprite> &Renderer::refSprite () {
    return _outSprite;
}
