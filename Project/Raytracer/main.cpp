//
//  main.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "main.h"

int main()
{
    App Raytracer;
    
    try {
        Raytracer.Initialise(1534, 1534, 7); //maximum height for my resolution 1534
    }
    catch(const char* err) {
        std::cerr << "[!] " << err << std::endl;
        return -1;
    }
    catch (std::bad_alloc err) {
        std::cerr << "[!] " << err.what() << std::endl;
        return -1;
    }
    
    Raytracer();

    return 0;
}

// MARK: Execution times for preset scenes before threading implementation
// Scene 1 (5 samples/pixel, 5 ray bounces) 108.4 MB of memory used
//      Run 1: 21.5666 sec (1 thread)
//      Run 2: 9.94164 sec (7 threads with data races)
//      Run 3: 7.69    sec (7 threads w/o data race)

// Scene 2 (5 samples/pixel, 5 ray bounces) 107.2 MB of memory used
//      Run 1: 6.05947 sec

// 50 50 0.001 746.3 sec // M1

// 50 50 0.001 296 sec // M1 Multithreading with 5 Threads (4 worker + 1 for window, input handling)

// 111.4 before thread->chunk conversion
