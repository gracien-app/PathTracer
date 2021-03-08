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
    Initialise();
    std::cout << "[C] Application:\n Resolution: 1000x1000\n Antialiasing: 0x" << std::endl;
}

App::App(int width, int height) {
    app_Resolution.reset(new sf::Vector2u(width,height));
    Initialise();
    std::cout << "[C] Application:\n Resolution: "<<width<<"x"<<height<<"\n Antialiasing: 0x" << std::endl;
}

App::~App() {
    std::cout << "\n[D] Application: Terminated"<< std::endl;
}

void App::Initialise() {
    app_Window.reset(new Window(app_Resolution.get()));
    app_Sprite.reset(new sf::Sprite);
}

void App::Run() {
    app_Texture.reset(new sf::Texture);
    
    if (app_Texture->create(app_Resolution->x, app_Resolution->y)) {
        std::cout << "[M] Application: Running" <<std::endl;
        int area = app_Resolution->x*app_Resolution->y;
        sf::Uint8* pixels = new sf::Uint8[area*4];
        
        for (int i=0; i < area; i++) {
            if(i%100) {
                pixels[i*4] = (10);
                pixels[i*4+1] = (10);
                pixels[i*4+2] = (10);
                pixels[i*4+3] = 255;
            }
            else {
                pixels[i*4] = 255;
                pixels[i*4+1] = (255);
                pixels[i*4+2] = (255);
                pixels[i*4+3] = 255;
            }
            
        }
        
        app_Texture->update(pixels);
        app_Sprite->setTexture(*app_Texture);
        
        while (app_Window->is_Open()) {
            app_Window->Display(app_Sprite.get());
        }
        delete[] pixels;
        pixels = nullptr;
    }
    else std::cout << "[M] Texture: Creation Failed" << std::endl;
    Stop();
}

void App::Stop() {
    std::cout << "[M] Application: Stopping" << std::endl;
}
