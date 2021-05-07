//
//  Window.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Window.hpp"

Window::Window() { 
    std::cout << "[C] Window: Created" << std::endl;
}

Window::~Window() {
    std::cout << "[D] Window: Terminated" << std::endl;
}

void Window::Initialise(const uint &width, const uint &height) {
    
    try {
        
        // RENDERER INIT //
        _appRenderer.reset( new Renderer(width, height) );
        _appRenderer->Initialise();
        
        // RENDER WINDOW //
        sf::VideoMode _videoMode(width, height, 32);
        _renderWindow.create(_videoMode, "RAYTRACER", sf::Style::Default);
        _renderWindow.setFramerateLimit(60);
        
    }
    catch(const char* &err) {
        throw;
    }
    catch (const std::bad_alloc &err) {
        throw;
    }
    
}

void Window::Display() {
    
    auto renderSprite = _appRenderer->Sprite();
    _appRenderer->runMultiThreading();
    
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
        _appRenderer->updateTexture();
        _renderWindow.draw(*renderSprite);
        _renderWindow.display();
        
    }
    
    _appRenderer->joinAll();
}

bool Window::isOpen() {
    return _renderWindow.isOpen();
}


