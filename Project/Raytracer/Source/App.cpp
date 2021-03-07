//
//  App.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"

App::App() {
    resolution.reset(new sf::Vector2u(1000,1000));
    app_Window.reset(new Window(resolution.get()));
    std::cout << "Application:\n Resolution: 1000x1000\n Antialiasing: 0x" << std::endl;
}

App::App(int width, int height) {
    resolution.reset(new sf::Vector2u(width, height));
    app_Window.reset(new Window(resolution.get()));
    std::cout << "Application:\n Resolution: "<<width<<"x"<<height<<"\n Antialiasing: 0x" << std::endl;
}

App::~App() {
    std::cout << "\nApplication: Terminated"<< std::endl;
}

void App::Run() {
    std::cout << "Application running" <<std::endl;
    while (app_Window->is_Open()) {
        app_Window->Display();
    }
}

void App::Stop() {
    std::cout << "Application stopping" << std::endl;
}
