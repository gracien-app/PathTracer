//
//  Window.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Window.hpp"

// MARK: Constructors & Destructor

Window::Window() {
    
    std::cout << "[C] Window: Created" << std::endl;
    
}

Window::~Window() {
    
    _renderEngine.reset();
    std::cout << "[D] Window: Destructed" << std::endl;
    
}

// MARK: Methods

void Window::Initialise(const uint &width, const uint &height, const int &inputThreads) {
    
    try {
        
        // RENDERER INIT //
        _renderMode = Mode::STANDARD;
        
        if (inputThreads > 0) _userThreads = inputThreads;
        else _userThreads = std::thread::hardware_concurrency();
        
        initPresets();
        _renderEngine.reset(new Renderer(width, height) );
        _renderEngine->Initialise( _presetsVector, _userThreads );
        
        // WINDOW INIT //
        sf::VideoMode _videoMode(width, height, 32);
        _renderWindow.create(_videoMode, "RAYTRACER", sf::Style::Close);
        _renderWindow.setFramerateLimit(60);
        
        _currentScene = 0;
        _scenesCount = int(_presetsVector->size()-1);
        
    }
    
    catch(const char* &err) {
        throw;
    }
    
    catch (const std::bad_alloc &err) {
        throw;
    }
    
}

void Window::renderCurrentScene(const bool preview) {
    
    _timer.restart();
    if (preview) _moveTimer.restart();

    _currentBounces = _presetsVector->at(_currentScene).at("BOUNCES");
    _currentSamples = _presetsVector->at(_currentScene).at("SAMPLES");
    
    _renderEngine->resetChunksIndex();
    
    _renderEngine->runChunks( _currentScene, _currentSamples, _currentBounces, _renderMode, preview );
    
}

void Window::Display() {
    
    auto renderSprite = _renderEngine->refSprite();
    renderCurrentScene();
    
    _moved = false;
    _moveOffset = 0.04;
    
    while (_renderWindow.isOpen()) {
        
        while (_renderWindow.pollEvent(_windowEvent)) handleEvent();
        
        if (!_renderEngine->allFinished()) {
            
            auto renderTime = std::to_string(float(_timer.getElapsedTime().asSeconds()));
            auto titleInfo = "RAYTRACER | Bounces: " + std::to_string(_currentBounces) +
                             " | Samples: " + std::to_string(_currentSamples) +
                             " | Time: " + renderTime + " sec";
            
            _renderWindow.setTitle(titleInfo);
            
        }
        
        if (_moved && _moveTimer.getElapsedTime().asSeconds() >= 1.0) {
            _moved = false;
            restartScene();
        }
        
        _renderWindow.clear(sf::Color(15, 15, 15));
        _renderEngine->updateTexture();
        _renderWindow.draw(*renderSprite);
        _renderWindow.display();
        
    }
    
    if (_renderEngine->joinAll()) std::cout << " [R] All threads joined safely." << std::endl;
    else std::cout << "[!] WARNING: Not all threads joined." << std::endl;
    
}

void Window::changeScene(const bool &next) {
    
    _renderEngine->stopAll();
    _renderEngine->joinAll();
    
    _moved = false;
    
    if (next) _currentScene++;
    else _currentScene--;
    
    renderCurrentScene();
    
}

void Window::restartScene(const bool preview) {
    
    _renderEngine->stopAll();
    _renderEngine->joinAll();
    
    renderCurrentScene(preview);
    
}

void Window::initPresets() {
    _presetsVector.reset( new std::vector<std::map<std::string, int>> {
                            { {"ID", 5}, {"SAMPLES", 5}, {"BOUNCES", 25} },
                            { {"ID", 6}, {"SAMPLES", 5}, {"BOUNCES", 25} },
                            { {"ID", 4}, {"SAMPLES", 5}, {"BOUNCES", 25} },
//                            { {"ID", 99}, {"SAMPLES", 5}, {"BOUNCES", 10} },
//                            { {"ID", 1}, {"SAMPLES", 5}, {"BOUNCES", 50} },
                            { {"ID", 2}, {"SAMPLES", 5}, {"BOUNCES", 25} },
                            { {"ID", 3}, {"SAMPLES", 5}, {"BOUNCES", 25} },
                        });
}

void Window::handleEvent() {
    
    if (_windowEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        _renderEngine->stopAll();
        _renderWindow.close();
    }

    else if (_windowEvent.type == sf::Event::KeyPressed) {
        switch (_windowEvent.key.code) {
                
            case sf::Keyboard::W:
                if (_moved) {
                    if (_renderEngine->allFinished()) {
                        _renderEngine->moveCamera(vect3D(0.0, 0.0, -_moveOffset), _currentScene);
                        restartScene(true);
                    }
                }
                else {
                    _moved = true;
                    _renderEngine->stopAll();
                    _renderEngine->moveCamera(vect3D(0.0, 0.0, -_moveOffset), _currentScene);
                    restartScene(true);
                }
                break;
                
            case sf::Keyboard::S:
                if (_moved) {
                    if (_renderEngine->allFinished()) {
                        _renderEngine->moveCamera(vect3D(0.0, 0.0, _moveOffset), _currentScene);
                        restartScene(true);
                    }
                }
                else {
                    _moved = true;
                    _renderEngine->stopAll();
                    _renderEngine->moveCamera(vect3D(0.0, 0.0, _moveOffset), _currentScene);
                    restartScene(true);
                }
                break;
                
            case sf::Keyboard::A:
                if (_moved) {
                    if (_renderEngine->allFinished()) {
                        _renderEngine->moveCamera(vect3D(-_moveOffset, 0.0, 0.0), _currentScene);
                        restartScene(true);
                    }
                }
                else {
                    _moved = true;
                    _renderEngine->stopAll();
                    _renderEngine->moveCamera(vect3D(-_moveOffset, 0.0, 0.0), _currentScene);
                    restartScene(true);
                }
                break;
                
            case sf::Keyboard::D:
                if (_moved) {
                    if (_renderEngine->allFinished()) {
                        _renderEngine->moveCamera(vect3D(_moveOffset, 0.0, 0.0), _currentScene);
                        restartScene(true);
                    }
                }
                else {
                    _moved = true;
                    _renderEngine->stopAll();
                    _renderEngine->moveCamera(vect3D(_moveOffset, 0.0, 0.0), _currentScene);
                    restartScene(true);
                }
                break;
                
            case sf::Keyboard::Q:
                if (_moved) {
                    if (_renderEngine->allFinished()) {
                        _renderEngine->moveCamera(vect3D(0.0, _moveOffset, 0.0), _currentScene);
                        restartScene(true);
                    }
                }
                else {
                    _moved = true;
                    _renderEngine->stopAll();
                    _renderEngine->moveCamera(vect3D(0.0, _moveOffset, 0.0), _currentScene);
                    restartScene(true);
                }
                break;
                
            case sf::Keyboard::E:
                if (_moved) {
                    if (_renderEngine->allFinished()) {
                        _renderEngine->moveCamera(vect3D(0.0, -_moveOffset, 0.0), _currentScene);
                        restartScene(true);
                    }
                }
                else {
                    _moved = true;
                    _renderEngine->stopAll();
                    _renderEngine->moveCamera(vect3D(0.0, -_moveOffset, 0.0), _currentScene);
                    restartScene(true);
                }
                break;
                
            default:
                break;
        }
        
    }
    
    else if (_windowEvent.type == sf::Event::KeyReleased) {
        
        switch (_windowEvent.key.code) {
                
            case sf::Keyboard::Space:
                _renderEngine->stopAll();
                break;
                
            case sf::Keyboard::Num1:
                if (_renderMode != Mode::STANDARD) {
                    _renderMode = Mode::STANDARD;
                    restartScene();
                }
                break;
                
            case sf::Keyboard::Num2:
                if (_renderMode != Mode::DEPTH) {
                    _renderMode = Mode::DEPTH;
                    restartScene();
                }
                break;
                
            case sf::Keyboard::Num3:
                if (_renderMode != Mode::THERMOGRAPHY) {
                    _renderMode = Mode::THERMOGRAPHY;
                    restartScene();
                }
                break;
                
            case sf::Keyboard::Num4:
                if (_renderMode != Mode::NORMALS) {
                    _renderMode = Mode::NORMALS;
                    restartScene();
                }
                break;
                
            case sf::Keyboard::Left:
                if (_currentScene > 0) changeScene();
                break;
                
            case sf::Keyboard::Right:
                if (_currentScene < _scenesCount) changeScene(true);
                break;
                
            case sf::Keyboard::Up:
                _presetsVector->at(_currentScene).at("SAMPLES") += 5;
                restartScene();
                break;
                
            case sf::Keyboard::Down:
                if ((_currentSamples-5) > 0) {
                    _presetsVector->at(_currentScene).at("SAMPLES") -= 5;
                    restartScene();
                }
                break;
                
            default:
                break;
                
        }
    }
}
