//
//  Window.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "main.h"

class Window {
public:
    
    // MARK: Constructors & Destructor
    
    Window(const uint &width, const uint &height);
    ~Window();
    
    // MARK: Utilities
    
    bool isOpen();
    bool initEngine();
    void Display();

private:
    
    bool rendering;
    
    sf::RenderWindow _renderWindow;
    
    std::unique_ptr<Renderer> app_Renderer;
};

#endif /* Window_hpp */
