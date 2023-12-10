//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"

#include <memory>
#include <iostream>


// MARK: - Constructors & Destructors

App::App() {
    std::cout << "[C] Application: Created" << std::endl;
}

App::~App() {
    _appWindow.reset();
    std::cout << "[D] Application: Destructed" << std::endl;
}


// MARK: - Operators

void App::operator()() {
    _appWindow->Display();
}


// MARK: - Methods

void App::Initialise(const uint &width, const uint &height, const int &threadCount) {
    
    try {
        _appWindow = std::make_unique<Window>();
        _appWindow->Initialise(width, height, threadCount);
    }
    catch(const char* &err) {
        throw;
    }
    catch (const std::bad_alloc &err) {
        throw;
    }

}