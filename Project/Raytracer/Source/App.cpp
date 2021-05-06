//
//  App.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"

// MARK: Constructors

App::App(const uint &width, const uint &height) {
    
    app_Window.reset(new Window(width,height));
    
    std::cout << "[C] Application:\n    Resolution: "<<width<<"x"<<height<< "\n\n";
}

App::~App() {
    std::cout << "\n[D] Application: Terminated"<< std::endl;
}

// MARK: Operators

void App::operator()() {
    app_Window->Display();
}
