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
#include <thread>

class Renderer {
public:
    
    // MARK: Constructors & Destructor
    Renderer(const uint &width, const uint &height);
    ~Renderer();
    
    // MARK: Methods
    
    bool joinAll();
    bool isBusy() const;
    
    void Initialise();
    void updateTexture();
    void invertContinue();
    void runMultiThreading();
    void Render(const uint &Y, const uint &chunkSize);
    
    std::shared_ptr<sf::Sprite> &refSprite();
    
private:
    
    bool busy, continueRender;
    double _width, _height;
    
    std::vector<sf::Uint8> _outPixels;
    std::shared_ptr<sf::Sprite> _outSprite;
    std::unique_ptr<sf::Texture> _outTexture;
    
    std::vector<std::thread> _concThreads;
    std::vector<std::shared_ptr<Scene>> _presetScenes;
    
};

#endif /* Renderer_hpp */
