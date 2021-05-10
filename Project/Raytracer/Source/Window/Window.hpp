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
    void handleEvent();
    void startRendering(const bool &firstRun);
    void Initialise(const uint &width, const uint &height, const int &threads);
    
    std::vector<std::map<std::string, int>> presetData();

private:
    
    int userThreads;
    int currentScene;
    int nOfScenes;
    
    sf::Event _windowEvent;
    sf::RenderWindow _renderWindow;
    
    std::unique_ptr<Renderer> _renderEngine;
   
};

#endif /* Window_hpp */
