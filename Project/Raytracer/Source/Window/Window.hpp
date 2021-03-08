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
    Window(sf::Vector2u *resolution);
    ~Window();
    
    void Display(sf::Sprite* drawable_Sprite);
    bool is_Open();

private:
    std::string window_Name;
    std::unique_ptr<sf::Event> event;
    std::unique_ptr<sf::ContextSettings> settings;
    std::unique_ptr<sf::RenderWindow> render_Window;
};

#endif /* Window_hpp */
