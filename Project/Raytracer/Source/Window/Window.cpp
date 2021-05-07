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
    _renderEngine.reset();
    std::cout << "[D] Window: Destructed" << std::endl;
}

void Window::Initialise(const uint &width, const uint &height) {
    
    try {
        
        // RENDERER INIT //
        _renderEngine.reset( new Renderer(width, height) );
        _renderEngine->Initialise();
        
        // RENDER WINDOW //
        sf::VideoMode _videoMode(width, height, 32);
        _renderWindow.create(_videoMode, "RAYTRACER", sf::Style::Default);
        _renderWindow.setFramerateLimit(30);
        
    }
    catch(const char* &err) {
        throw;
    }
    catch (const std::bad_alloc &err) {
        throw;
    }
    
}

void Window::Display() {
    
    auto renderSprite = _renderEngine->refSprite();
    _renderEngine->runMultiThreading();
    
    while (_renderWindow.isOpen()) {
        
        sf::Event _event;
        
        while (_renderWindow.pollEvent(_event)) {
            if (_event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _renderEngine->invertContinue();
                _renderWindow.close();
            }
            if (_event.type == sf::Event::KeyReleased && _event.key.code == sf::Keyboard::Space) {
                _renderEngine->invertContinue();
                rendering = !rendering;
            }
        }
        
        _renderWindow.clear(sf::Color(0, 0, 0));
        _renderEngine->updateTexture();
        _renderWindow.draw(*renderSprite);
        _renderWindow.display();
        
    }
    
    if ( _renderEngine->joinAll() ) std::cout << " [R] All threads joined safely." << std::endl;
    else std::cout << "[!] WARNING: Not all threads joined." << std::endl;
    
}

bool Window::isOpen() {
    return _renderWindow.isOpen();
}


