//
//  Renderer.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Chunk.hpp"


class Renderer {
public:
    
    // MARK: Constructors & Destructor
    Renderer(const uint &width, const uint &height);
    ~Renderer();
    
    // MARK: Methods
    
    bool joinAll();
    bool allFinished();
    
    void stopAll();
    void updateTexture();
    void runChunks(const int &nPreset);
    void distributeChunks(const int &nThreads);
    void renderChunk(const int &chunkID, const int &presetID, const int &samplesN, const int &bouncesN);
    void Initialise(std::shared_ptr<std::vector<std::map<std::string, int>>> &defaultPresets, const int &nThreads);
    
    std::shared_ptr<sf::Sprite> &refSprite();
    
private:
    
    double _width, _height;
    
    std::mutex printMutex;
    
    std::atomic<bool> _stopExecution;
    
    std::shared_ptr<sf::Sprite> _outSprite;
    std::unique_ptr<sf::Texture> _outTexture;
    std::shared_ptr<std::vector<std::map<std::string, int>>> _presets;
    
    std::vector<Chunk> _imageChunks;
    std::vector<sf::Uint8> _outPixels;
    std::vector<std::unique_ptr<Scene>> _presetScenes;
    
};

#endif /* Renderer_hpp */
