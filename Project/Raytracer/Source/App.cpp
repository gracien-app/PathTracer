//
//  App.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"

App::App() {
    app_Resolution.reset(new sf::Vector2u(1000,1000));
    try {
        Initialise();
    }
    catch (const char* err) {
        std::cerr << "[C] ERROR: "<< err << std::endl;
    }
    std::cout << "[C] Application:\n Resolution: 1000x1000\n Antialiasing: 0x" << std::endl;
}

App::App(int width, int height) {
    app_Resolution.reset(new sf::Vector2u(width,height));
    
    try {
        Initialise();
    }
    catch (const char* err) {
        std::cerr << "[C] ERROR: "<< err << std::endl;
    }
    std::cout << "[C] Application:\n Resolution: "<<width<<"x"<<height<<"\n Antialiasing: 0x" << std::endl;
}

App::~App() {
    std::cout << "\n[D] Application: Terminated"<< std::endl;
}

void App::Initialise() {
    app_Window.reset(new Window(app_Resolution.get()));
    app_Sprite.reset(new sf::Sprite);
    if (!app_Window) throw "Can't create application window.";
    if (!app_Sprite) throw "Can't create window sprite.";
}

void App::Run() {
    app_Texture.reset(new sf::Texture);
    
    if (app_Texture->create(app_Resolution->x, app_Resolution->y)) {
        
        std::cout << "[M] Application: Running" <<std::endl;
        int area = app_Resolution->x*app_Resolution->y;
        int width = app_Resolution->x;
        int height = app_Resolution->y;
        std::vector<sf::Uint8> pixels(area*4);
        
        for (int j=0; j<height; j++) {
            for (int i=0; i<width; i++) {
                
                auto r = float(i) / width;
                auto g = float(j) / height;
                auto b = 0.5;
                
                int gridPos = i+(j*height);
                pixels[4*gridPos+0] = int(r*255);
                pixels[4*gridPos+1] = int(g*255);
                pixels[4*gridPos+2] = int(b*255);
                pixels[4*gridPos+3] = int(255);
                //4* because one pixel consists of RGBA color components
                //+x to access specific component
            }
        }
        app_Texture->update(&pixels[0]);
        app_Sprite->setTexture(*app_Texture);
        
        while (app_Window->is_Open()) {
            app_Window->Display(app_Sprite.get());
        }
    }
    else std::cout << "[M] Texture: Creation Failed" << std::endl;
    Stop();
}

void App::Stop() {
    std::cout << "[M] Application: Stopping" << std::endl;
}
