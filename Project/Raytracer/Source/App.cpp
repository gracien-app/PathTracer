//
//  App.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"

// MARK: Constructors

App::App() {
    
   
    
    std::cout << "[C] Application: Created" << std::endl;
}

App::~App() {
    std::cout << "[D] Application: Terminated" << std::endl;
}

// MARK: Operators

void App::operator()() {
    _appWindow->Display();
}

void App::Initialise(const uint &width, const uint &height) {
    
    try {
        _appWindow.reset( new Window() );
        _appWindow->Initialise(width, height);
    }
    catch(const char* err) {
        std::cerr << "[!] APP Initialise: " << err << std::endl;
    }
    catch (std::bad_alloc err) {
        std::cerr << "[!] APP Initialise: " << err.what() << std::endl;
    }

}
