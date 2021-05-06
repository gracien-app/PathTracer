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
    
    Window();
    ~Window();
    
    // MARK: Utilities
    void Initialise(const uint &width, const uint &height);
    bool isOpen();
    void Display();

private:
    
    bool rendering;
    
    sf::RenderWindow _renderWindow;
    
    std::unique_ptr<Renderer> _appRenderer;
};

#endif /* Window_hpp */
