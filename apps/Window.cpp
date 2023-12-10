//
//  Window.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Window.hpp"

// MARK: - Constructors & Destructor

Window::Window() {
    std::cout << "[C] Window: Created" << std::endl;
}

Window::~Window() {
    _renderEngine.reset();
    std::cout << "[D] Window: Destructed" << std::endl;
}

// MARK: - Methods

void Window::Initialise(const uint &width, const uint &height, const int &inputThreads) {
    
    if (inputThreads > 0) _userThreads = inputThreads;
    else _userThreads = std::thread::hardware_concurrency();
    
    _currentMode = Mode::STANDARD;
    
    try {
        initPresets();
        _renderEngine.reset(new Renderer(width, height));
        _renderEngine->Initialise(_presetsVector, _userThreads);
        
        sf::VideoMode _videoMode(sf::Vector2u{width, height}, 32);
        _renderWindow.create(_videoMode, "PATHTRACER", sf::Style::Close);
        _renderWindow.setFramerateLimit(60);
    }
    catch(const char* &err) {
        throw;
    }
    catch (const std::bad_alloc &err) {
        throw;
    }
}

void Window::initPresets() {
    _presetsVector.reset(new std::vector<std::map<std::string, int>> {
        { {"ID", 5}, {"SAMPLES", 5}, {"BOUNCES", 50} },
        { {"ID", 2}, {"SAMPLES", 5}, {"BOUNCES", 50} },
        { {"ID", 7}, {"SAMPLES", 5}, {"BOUNCES", 10} },
        
        { {"ID", 4}, {"SAMPLES", 1}, {"BOUNCES", 25} },
        { {"ID", 3}, {"SAMPLES", 1}, {"BOUNCES", 25} },
        { {"ID", 9}, {"SAMPLES", 5}, {"BOUNCES", 25} },
        { {"ID", 98}, {"SAMPLES", 1}, {"BOUNCES", 25} },
    });
    
    _currentScene = 0;
    _scenesCount = int(_presetsVector->size() - 1);
}


// MARK: -

void Window::Display() {
    
    auto renderSprite = _renderEngine->refSprite();
    renderCurrentScene();
    
    _moved = false;
    _moveOffset = 0.04;
    
    while (_renderWindow.isOpen()) {
        
        while (_renderWindow.pollEvent(_windowEvent)) handleEvent();
        
        if (!_renderEngine->allFinished()) {
            
            std::stringstream _timeStream;
            _timeStream << std::fixed << std::setprecision(2) << float(_timer.getElapsedTime().asSeconds());
            auto renderTime = _timeStream.str();
            
            auto titleInfo = "PATHTRACER | Bounces: " + std::to_string(_currentBounces) +
                             " | Samples: " + std::to_string(_currentSamples) +
                             " | Time: " + renderTime + " sec";
            
            _renderWindow.setTitle(titleInfo);
        }
        
        if (_moved && _moveTimer.getElapsedTime().asSeconds() >= 1.0) {
            _moved = false;
            restartCurrentScene();
        }
        
        _renderWindow.clear(sf::Color(15, 15, 15));
        _renderEngine->updateTexture();
        _renderWindow.draw(*renderSprite);
        _renderWindow.display();
        
    }
    
    if (_renderEngine->joinAll()) std::cout << " [R] All threads joined safely." << std::endl;
    else std::cout << "[!] WARNING: Not all threads joined." << std::endl;

}


void Window::renderCurrentScene(const bool preview) {
    
    _timer.restart();
    if (preview) _moveTimer.restart();

    _currentBounces = _presetsVector->at(_currentScene).at("BOUNCES");
    _currentSamples = _presetsVector->at(_currentScene).at("SAMPLES");
    
    _renderEngine->runChunks( _currentScene, _currentSamples, _currentBounces, _currentMode, preview );
}


void Window::restartCurrentScene(const bool preview) {
    _renderEngine->stopAll();
    _renderEngine->joinAll();
    
    renderCurrentScene(preview);
}


void Window::changeSceneIndex(const int offset) {
    int offsetIndex = _currentScene + offset;
    
    if(offsetIndex >= 0 && offsetIndex <= _scenesCount) {
        _currentScene = offsetIndex;
        _moved = false;
        
        restartCurrentScene();
    }
}


void Window::changeSampleCount(const int offset) {
    int offsetSamples = _currentSamples + offset;
    
    if(offsetSamples > 0) {
        _presetsVector->at(_currentScene).at("SAMPLES") = offsetSamples;
        restartCurrentScene();
    }
}


void Window::changeRenderMode(const Mode &newMode) {
    if(newMode != _currentMode) {
        _currentMode = newMode;
        restartCurrentScene();
    }
}


void Window::moveCurrentCamera(const vect3D &offset) {
    if (_moved) {
        if (_renderEngine->allFinished()) {
            _renderEngine->moveCamera(offset, _currentScene);
            restartCurrentScene(true);
        }
    }
    else {
        _moved = true;
        _renderEngine->stopAll();
        _renderEngine->moveCamera(offset, _currentScene);
        restartCurrentScene(true);
    }
}


void Window::handleEvent() {
    
    if (_windowEvent.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        _renderEngine->stopAll();
        _renderWindow.close();
    }

    else if (_windowEvent.type == sf::Event::KeyPressed) {
        switch (_windowEvent.key.code) {
                
            case sf::Keyboard::W:
                moveCurrentCamera(vect3D(0.0, 0.0, -_moveOffset));
                break;
                
            case sf::Keyboard::S:
                moveCurrentCamera(vect3D(0.0, 0.0, _moveOffset));
                break;
                
            case sf::Keyboard::A:
                moveCurrentCamera(vect3D(-_moveOffset, 0.0, 0.0));
                break;
                
            case sf::Keyboard::D:
                moveCurrentCamera(vect3D(_moveOffset, 0.0, 0.0));
                break;
                
            case sf::Keyboard::Q:
                moveCurrentCamera(vect3D(0.0, _moveOffset, 0.0));
                break;
                
            case sf::Keyboard::E:
                moveCurrentCamera(vect3D(0.0, -_moveOffset, 0.0));
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
                changeRenderMode(Mode::STANDARD);
                break;
                
            case sf::Keyboard::Num2:
                changeRenderMode(Mode::DEPTH);
                break;
                
            case sf::Keyboard::Num3:
                changeRenderMode(Mode::THERMOGRAPHY);
                break;
                
            case sf::Keyboard::Num4:
                changeRenderMode(Mode::NORMALS);
                break;
                
            case sf::Keyboard::Left:
                changeSceneIndex(-1);
                break;
                
            case sf::Keyboard::Right:
                changeSceneIndex(1);
                break;
                
            case sf::Keyboard::Up:
                changeSampleCount(5);
                break;
                
            case sf::Keyboard::Down:
                changeSampleCount(-5);
                break;
                
            default:
                break;
                
        }
    }
}
