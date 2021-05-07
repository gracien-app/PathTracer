//
//  main.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "main.h"

const unsigned int logicalCoresCount() {
    return std::thread::hardware_concurrency();
}

int main()
{
    App Raytracer;
    
    try {
        Raytracer.Initialise(1534, 1534); //maximum height for my resolution 1534
    }
    catch(const char* err) {
        std::cerr << "[!] " << err << std::endl;
        return -1;
    }
    catch (std::bad_alloc err) {
        std::cerr << "[!] " << err.what() << std::endl;
        return -1;
    }
    
    std::cout << "CPU - Logical Cores available: " << logicalCoresCount() << std::endl;
    Raytracer();

    return 0;
}

// TODO: Create Scene-changing functionality to the window, to switch between them using keyboard

// TODO: (IDEA) Make volumes where intersection function, is simply random generator where probability is dependent on density, the denser the volume, the more particles are hit and so it will maybe look like clouds.

// TODO: Implement normal differentation between inside and outside in pixel colouring methods

// TODO: IDEA track mouse location on the screen, then use this location as a middle point of projection plane, and calculate left upper corner and render direction vectors based on that, pointer will be always at the middle, and how far it is is defined by the focal length of camera, use scroll to change the focal length

// MARK: Execution times for preset scenes before threading implementation
// Scene 1 (5 samples/pixel, 5 ray bounces) 108.4 MB of memory used
//      Run 1: 21.5943 sec
//      Run 2: 21.5666 sec
//      Run 3: 21.7336 sec
//      Run 4: 51.7416 (Rosetta)

// Scene 2 (5 samples/pixel, 5 ray bounces) 107.2 MB of memory used
//      Run 1: 6.07266 sec
//      Run 2: 6.05947 sec
//      Run 3: 6.08092 sec

// 50 50 0.001 1787 sec // i5
// 50 50 0.001 746.3 sec // M1

// 50 50 0.001 296 sec // M1 Multithreading with 5 Threads (4 worker + 1 for window, input handling)
