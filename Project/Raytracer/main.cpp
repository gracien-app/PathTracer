//
//  main.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "main.h"
#include "App.hpp"
#include <thread>

const unsigned int logicalCoresCount() {
    return std::thread::hardware_concurrency();
}

int main()
{
    App Raytracer(1534,1534); //maximum height for my resolution 1534
    std::cout << "CPU - Logical Cores available: " << logicalCoresCount() << std::endl;
    Raytracer.Run();

    return 0;
}

// TODO: Create Scene-changing functionality to the window, to switch between them using keyboard

// TODO: (IDEA) Make volumes where intersection function, is simply random generator where probability is dependent on density, the denser the volume, the more particles are hit and so it will maybe look like clouds.

// TODO: Implement normal differentation between inside and outside in pixel colouring methods

// TODO: IDEA track mouse location on the screen, then use this location as a middle point of projection plane, and calculate left upper corner and render direction vectors based on that, pointer will be always at the middle, and how far it is is defined by the focal length of camera, use scroll to change the focal length

// MARK: Execution times for preset scenes before threading implementation
// Scene 1 (5 samples/pixel, 5 ray bounces)
//      Run 1: 21.5943 sec
//      Run 2: 21.5666 sec
//      Run 3: 21.7336 sec

// Scene 2 (5 samples/pixel, 5 ray bounces)
//      Run 1: 6.07266 sec
//      Run 2: 6.05947 sec
//      Run 3: 6.08092 sec
