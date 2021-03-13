//
//  Window.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Window.hpp"

Window::Window(const uint &width, const uint &height) {
    
    _event.reset(new sf::Event);
    _renderWindow.reset(new sf::RenderWindow);
    _videoMode.reset(new sf::VideoMode(width,height,32));
    
    _renderWindow->create(*_videoMode, "RAYTRACER", sf::Style::Default);
    _renderWindow->setVerticalSyncEnabled(true);
    
    std::cout << "[C] Window: Created" << std::endl;
}

Window::~Window() {
    std::cout << "[D] Window: Terminated" << std::endl;
}

void Window::Display(const sf::Sprite &drawable_Sprite) {
    while (_renderWindow->isOpen()) {
        while (_renderWindow->pollEvent(*_event)) {
            if (_event->type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                _renderWindow->close();
            }
        }
        _renderWindow->clear(sf::Color(0, 0, 0));
        _renderWindow->draw(drawable_Sprite);
        _renderWindow->display();
    }
}

bool Window::isOpen() {
    return _renderWindow->isOpen();
}

sf::Vector2u Window::getResolution() {
    return _renderWindow->getSize();
}

