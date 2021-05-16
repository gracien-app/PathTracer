//
//  Window.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Window_hpp
#define Window_hpp

#include "Renderer.hpp"

class Window {
public:
    
    // MARK: Constructors & Destructor
    
    
    /// Window constructor
    /// @brief Displays appropriate message in the console
    Window();
    
    /// Window destructor
    /// @brief Displays appropriate message in the console
    ~Window();
    
    // MARK: Methods
    
    /// Method used to display image resulting from renderer execution. Title of window is updated when calculations are performed. Function is executed while application window is open. At the end of execution, method joins all threads to safely return.
    void Display();
    
    /// Method used to initalise vector of maps, containing settings for different predefined scenes.
    void initPresets();
    
    /// Methods wrapping all necessary checks for handling window events such as closing window, or keyboard user input. Detached from Display method for improved readability
    void handleEvent();
    
    /// Method which performs all necessary actions, to restart calculations of current scene. Executed in case when number of samples is changed by user using user input functionality.
    void restartScene();
    
    /// Method which calls Renderer::runChunks() for currently set scene. Additionally, currentSamples and currentBounces are updated to match current render settings, which are later displayed in title of application window.
    void renderCurrentScene();
    
    
    /// @brief Method which changes current scene. Performs all necessary actions to safely stop previous, and start rendering of new scene.
    /// @param next Parameter defining whether method should switch to next or previous scene. If TRUE, change to next scene occurs.
    void changeScene(const bool &next = false);
    
    /// @brief Method used to initialise all necessary components for Renderer and Window classes. Uses exceptions to catch errors crucial for program execution.  If number of threads provided by the user is incorrect, std::thread::hardware_concurrency is used to determine optimal number of threads.
    /// @param width Parameter defining width of the window.
    /// @param height Parameter defining height of the window.
    /// @param inputThreads Number of threads provided by the user.
    void Initialise(const uint &width, const uint &height, const int &inputThreads);
   
private:
    
    int _userThreads, _scenesCount, _currentScene, _currentSamples, _currentBounces;
    
    sf::Clock _timer;
    sf::Event _windowEvent;
    sf::RenderWindow _renderWindow;
    
    std::unique_ptr<Renderer> _renderEngine;
    std::shared_ptr<std::vector<std::map<std::string, int>>> _presetsVector;
   
};

#endif /* Window_hpp */
