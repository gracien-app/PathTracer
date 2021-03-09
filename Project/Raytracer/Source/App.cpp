//
//  App.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"

App::App() {
    Initialise(1000, 1000);
    std::cout << "[C] Application:\n Resolution: 1000x1000\n Antialiasing: 0x" << std::endl;
}

App::App(int width, int height) {
    Initialise(width, height);
    std::cout << "[C] Application:\n Resolution: "<<width<<"x"<<height<<"\n Antialiasing: 0x" << std::endl;
}

App::~App() {
    std::cout << "\n[D] Application: Terminated"<< std::endl;
}

void App::Initialise(int width, int height) {
    app_Window.reset(new Window(width,height));
    app_Renderer.reset(new Renderer());
    
    try {
        app_Renderer->Initialise(app_Window->getResolution());
    }
    catch(const char* err){
        std::cerr << "\n[!] FATAL: " << err << "\n\n";
    }
}

void App::Run() {
    std::cout << "[M] Application: Running" <<std::endl;
   
    while (app_Window->isOpen()) {
        app_Window->Display(app_Renderer->getSprite());
    }
    
    Stop();
}

void App::Stop() {
    std::cout << "[M] Application: Stopping" << std::endl;
}
