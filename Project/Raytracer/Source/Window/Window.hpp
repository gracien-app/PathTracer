//
//  Window.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "Renderer.hpp"

class Window {
public:
    
    // MARK: Constructors & Destructor
    
    Window();
    ~Window();
    
    // MARK: Utilities
    
    void Display();
    void initPresets();
    void handleEvent();
    void restartScene();
    void startRendering();
    void changeScene(const bool &next = false);
    void Initialise(const uint &width, const uint &height, const int &threads);
   
private:
    
    int userThreads, currentScene, nOfScenes, currentSamples;
    
    sf::Clock _timer;
    sf::Event _windowEvent;
    sf::RenderWindow _renderWindow;
    
    std::unique_ptr<Renderer> _renderEngine;
    
    std::shared_ptr<std::vector<std::map<std::string, int>>> _presets;
   
};

#endif /* Window_hpp */
