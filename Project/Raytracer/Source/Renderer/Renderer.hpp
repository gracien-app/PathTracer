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
    void Initialise();
    void Render(const uint &Y, const uint &chunkSize);
    void runMultiThreading();
    void joinAll();
    void updateTexture();
    
    bool isBusy() const;
    
    std::shared_ptr<sf::Sprite> &Sprite ();
    
private:
    
    bool busy;
    double _width;
    double _height;
    
    std::thread t1, t2, t3, t4;
    
    
    std::vector<sf::Uint8> outPixels;
    std::shared_ptr<sf::Sprite> outSprite;
    std::unique_ptr<sf::Texture> outTexture;
    std::vector<std::shared_ptr<Scene>> preScenes;
    
};

#endif /* Renderer_hpp */
