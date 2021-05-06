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
    
    // MARK: Constructors & Destructor
    App(const uint &width, const uint &height);
    ~App();
    
    // MARK: Operators
    void operator()();
    
    // MARK: Methods
    void Initialise();
    
private:
    
    bool is_Open;
    std::unique_ptr<Window> app_Window;
    
};

#endif /* App_hpp */
