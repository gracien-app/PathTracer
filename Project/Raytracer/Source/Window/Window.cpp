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

void Window::Initialise(const uint &width, const uint &height, const int &threads) {
    
    try {
        
        // RENDERER INIT //
        userThreads = threads;
        _renderEngine.reset( new Renderer(width, height) );
        _renderEngine->Initialise( presetData() );
        
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

void Window::startRendering(const bool &firstRun) {
    
    if (userThreads <= 0) {
        _renderEngine->runOnThreads( std::thread::hardware_concurrency(), presetData()[currentScene], firstRun );
    }
    
    else {
        if (userThreads == 1) std::cout << "[!] Running on single thread is not advised" << std::endl;
        _renderEngine->runOnThreads(userThreads, presetData()[currentScene], firstRun );
    }
    
}

void Window::Display() {
    
    auto presets = presetData();
    auto renderSprite = _renderEngine->refSprite();
    
    nOfScenes = int(presets.size()-1);
    std::cout << nOfScenes << '\n';
    currentScene = 0;
    startRendering(1);
    
    while (_renderWindow.isOpen()) {
        
        while (_renderWindow.pollEvent(_windowEvent)) handleEvent();
        
        _renderWindow.clear(sf::Color(15, 15, 15));
        _renderEngine->updateTexture();
        _renderWindow.draw(*renderSprite);
        _renderWindow.display();
        
    }
    
    if ( _renderEngine->joinAll() ) std::cout << " [R] All threads joined safely." << std::endl;
    else std::cout << "[!] WARNING: Not all threads joined." << std::endl;
    
}

void Window::handleEvent() {
    
    if (_windowEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        _renderEngine->invertContinue();
        _renderWindow.close();
    }
    
    else if (_windowEvent.type == sf::Event::KeyReleased) {
        
        if (_windowEvent.key.code == sf::Keyboard::Space) {
            _renderEngine->invertContinue();
        }
        
        else if (_windowEvent.type == sf::Event::KeyReleased && _windowEvent.key.code == sf::Keyboard::Left) {
            if (currentScene > 0) {
                _renderEngine->invertContinue();
                _renderEngine->joinAll();
                currentScene--;
                startRendering(0);
            }
        }
        
        else  if (_windowEvent.type == sf::Event::KeyReleased && _windowEvent.key.code == sf::Keyboard::Right) {
            if (currentScene < nOfScenes) {
                _renderEngine->invertContinue();
                _renderEngine->joinAll();
                currentScene++;
                startRendering(0);
            }
        }
        
    }
    
}

std::vector<std::map<std::string, int>> Window::presetData() {
    
    return std::vector<std::map<std::string, int>> {
    
        { {"ID", 99}, {"SAMPLES", 10}, {"BOUNCES", 50}, {"COUNT", 0} },
        { {"ID", 1}, {"SAMPLES", 1}, {"BOUNCES", 50}, {"COUNT", 1} },
        { {"ID", 2}, {"SAMPLES", 5}, {"BOUNCES", 5}, {"COUNT", 2} }
        
    };
    
}
