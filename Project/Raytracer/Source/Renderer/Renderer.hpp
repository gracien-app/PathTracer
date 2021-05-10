//
//  Renderer.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Scene.hpp"

#include <mutex>
#include <thread>

class Renderer {
public:
    
    // MARK: Constructors & Destructor
    Renderer(const uint &width, const uint &height);
    ~Renderer();
    
    // MARK: Methods
    
    bool joinAll();
    
    void updateTexture();
    void invertContinue();
   
    void printThreadInfo(const sf::Time &execTime);
    void renderChunk(const int &chunkStart, const int &chunkEnd, const std::map<std::string, int> &data);
    void Initialise(std::vector<std::map<std::string, int>> defaultPresets);
    void runOnThreads(const int &nThreads, const std::map<std::string, int> &data, const bool &firstRun);
    
    std::shared_ptr<sf::Sprite> &refSprite();
    
private:
    
    
    double _width, _height;
    
    std::atomic<bool> _stopExecution;
    
    std::shared_ptr<sf::Sprite> _outSprite;
    std::unique_ptr<sf::Texture> _outTexture;
    
    std::vector<sf::Uint8> _outPixels;
    std::vector<std::thread> _concThreads;
    std::vector<std::unique_ptr<Scene>> _presetScenes;
    
};

#endif /* Renderer_hpp */
