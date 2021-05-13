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
        initPresets();
        userThreads = threads;
        _renderEngine.reset( new Renderer(width, height) );
        _renderEngine->Initialise( _presets, userThreads );
        
        // RENDER WINDOW //
        sf::VideoMode _videoMode(width, height, 32);
        _renderWindow.create(_videoMode, "RAYTRACER", sf::Style::Default);
        _renderWindow.setFramerateLimit(60);
        currentScene = 0;
        nOfScenes = int(_presets->size()-1);
        
    }
    
    catch(const char* &err) {
        throw;
    }
    
    catch (const std::bad_alloc &err) {
        throw;
    }
}

void Window::startRendering() {
    _renderEngine->runChunks( currentScene );
}

void Window::Display() {
    
    auto renderSprite = _renderEngine->refSprite();
    startRendering();
    _timer.restart();
    
    while (_renderWindow.isOpen()) {
        
        while (_renderWindow.pollEvent(_windowEvent)) handleEvent();
        
        if (!_renderEngine->allFinished()) {
            auto renderTime = std::to_string(float(_timer.getElapsedTime().asSeconds()));
            auto samples = std::to_string(_presets->at(currentScene).at("SAMPLES"));
            _renderWindow.setTitle("RAYTRACER - Samples: " + samples + " Time: " + renderTime);
        }
        
        _renderWindow.clear(sf::Color(15, 15, 15));
        _renderEngine->updateTexture();
        _renderWindow.draw(*renderSprite);
        _renderWindow.display();
        
    }
    
    if ( _renderEngine->joinAll() ) std::cout << " [R] All threads joined safely." << std::endl;
    else std::cout << "[!] WARNING: Not all threads joined." << std::endl;
    
}

void Window::changeScene(const bool &next) {
    
    _renderEngine->stopAll();
    _renderEngine->joinAll();
    if (next) currentScene++;
    else currentScene--;
    startRendering();
    _timer.restart();
}

void Window::restartScene() {
    _renderEngine->stopAll();
    _renderEngine->joinAll();
    startRendering();
    _timer.restart();
}

void Window::handleEvent() {
    
    if (_windowEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        _renderEngine->stopAll();
        _renderWindow.close();
    }
    
    else if (_windowEvent.type == sf::Event::KeyReleased) {
        
        if (_windowEvent.key.code == sf::Keyboard::Space) {
            _renderEngine->stopAll();
        }
        
        if (_windowEvent.key.code == sf::Keyboard::Left) {
            if (currentScene > 0) changeScene();
        }
        
        if (_windowEvent.key.code == sf::Keyboard::Right) {
            if (currentScene < nOfScenes) changeScene(true);
        }
        
        if (_windowEvent.key.code == sf::Keyboard::Up) {
            _presets->at(currentScene).at("SAMPLES") += 5;
            restartScene();
        }
        
        if (_windowEvent.key.code == sf::Keyboard::Down) {
            currentSamples = _presets->at(currentScene).at("SAMPLES");
            if (currentSamples != 5) {
                _presets->at(currentScene).at("SAMPLES") -= 5;
                restartScene();
            }
        }
        
    }
    
}

void Window::initPresets() {
    _presets.reset( new std::vector<std::map<std::string, int>> {
                            { {"ID", 99}, {"SAMPLES", 5}, {"BOUNCES", 5} },
                            { {"ID", 1}, {"SAMPLES", 5}, {"BOUNCES", 5} },
                            { {"ID", 2}, {"SAMPLES", 5}, {"BOUNCES", 5} },
                            { {"ID", 3}, {"SAMPLES", 5}, {"BOUNCES", 5} }
                        }
    );
}
