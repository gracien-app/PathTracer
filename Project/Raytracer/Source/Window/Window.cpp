//
//  Window.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Window.hpp"

Window::Window(const uint &width, const uint &height) {
    
    sf::VideoMode _videoMode(width,height,32);
    
    _renderWindow.create(_videoMode, "RAYTRACER", sf::Style::Default);
    _renderWindow.setFramerateLimit(60);
    
    std::cout << "[C] Window: Created" << std::endl;
}

Window::~Window() {
    std::cout << "[D] Window: Terminated" << std::endl;
}

void Window::Display(const std::shared_ptr<Renderer> &renderEngine) {
    
    auto renderSprite = renderEngine->Sprite();
    rendering = true;
    
    while (_renderWindow.isOpen()) {
        
        sf::Event _event;
        
        while (_renderWindow.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _renderWindow.close();
            }
            if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Space) {
                rendering = !rendering;
            }
        }
        
        _renderWindow.clear(sf::Color(0, 0, 0));
        _renderWindow.draw(*renderSprite);
        _renderWindow.display();
        
        if ( !renderEngine->isBusy() && rendering ) renderEngine->render();
    }
}

bool Window::isOpen() {
    return _renderWindow.isOpen();
}


