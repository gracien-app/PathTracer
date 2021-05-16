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
    
    /// App constructor
    /// @brief Displays appropriate message in the console
    App();
    
    /// App destructor
    /// @brief Displays appropriate message in the console
    ~App();
    
    // MARK: Operators
    
    /// Empty bracket operator, provides clean and simple way to execute Window::Display() function
    void operator()();
    
    // MARK: Methods
    
    /// Allocates and initialises all necesary App class components. Uses exceptions to catch errors crucial for program execution.
    /// @param width Parameter defining width of the application resolution
    /// @param height Parameter defining height of the application resolution
    void Initialise(const uint &width, const uint &height, const int &inputThreads = -1);
    
private:
    
    std::unique_ptr<Window> _appWindow;
    
};

#endif /* App_hpp */
