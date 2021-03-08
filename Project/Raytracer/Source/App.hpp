//
//  App.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef App_hpp
#define App_hpp

#include "Window.hpp"

class App {
public:
    App();
    App(int width, int height);
    ~App();
    
    void Initialise();
    void Run();
    void Stop();
    
private:
    bool is_Open;
    
    std::unique_ptr<Window> app_Window;
    std::unique_ptr<sf::Sprite> app_Sprite;
    std::unique_ptr<sf::Texture> app_Texture;
    std::unique_ptr<sf::Vector2u> app_Resolution;
    
    
};

#endif /* App_hpp */
