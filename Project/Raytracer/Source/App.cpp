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
    Initialise(1000, 1000);
    std::cout << "[C] Application:\n Resolution: 1000x1000" << std::endl;
}

App::App(const int &width, const int &height) {
    Initialise(width, height);
    std::cout << "[C] Application:\n    Resolution: "<<width<<"x"<<height<< std::endl;
}

App::~App() {
    std::cout << "\n[D] Application: Terminated"<< std::endl;
}

// MARK: State methods
void App::Initialise(const int &width, const int &height) {
    
    app_Window.reset(new Window(width,height));
    app_Renderer.reset(new Renderer());
    
    try {
        app_Renderer->init(app_Window->getResolution());
    }
    catch(const char* err) {
        std::cerr << "\n[!] FATAL: " << err << "\n\n";
    }
    catch (std::bad_alloc) {
        std::cerr << "\n[!] FATAL: Can't allocate space for output pixel vector.\n\n";
    }
}

void App::Run() {
    std::cout << "[M] Application: Running" <<std::endl;
   
    while (app_Window->isOpen()) {
        app_Window->Display(*app_Renderer->getSprite());
    }
    
    Stop();
}

void App::Stop() {
    std::cout << "[M] Application: Stopping" << std::endl;
}
