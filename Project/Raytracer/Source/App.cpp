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
    app_Renderer.reset(new Renderer(width, height));
    
    Initialise();
    std::cout << "[C] Application:\n    Resolution: "<<width<<"x"<<height<< "\n\n";
}

App::~App() {
    std::cout << "\n[D] Application: Terminated"<< std::endl;
}

// MARK: State methods

void App::Initialise() {
    try {
        app_Renderer->init();
    }
    catch(const char* err) {
        std::cerr << "\n[!] FATAL: " << err << "\n\n";
    }
    catch (std::bad_alloc) {
        std::cerr << "\n[!] FATAL: Can't allocate space for output pixel vector.\n\n";
    }
}

void App::Run() {
    while (app_Window->isOpen()) {
        app_Window->Display(app_Renderer);
    }
}
