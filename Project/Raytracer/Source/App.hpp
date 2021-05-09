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
    App();
    ~App();
    
    // MARK: Operators
    void operator()();
    
    // MARK: Methods
    void Initialise(const uint &width, const uint &height, const int &threads = -1);
    
private:
    
    std::unique_ptr<Window> _appWindow;
    
};

#endif /* App_hpp */
