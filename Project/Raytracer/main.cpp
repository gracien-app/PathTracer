//
//  main.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"
#include "main.h"

#include "Colour.hpp"

int main()
{
    App Raytracer(1534,1534); //maximum height for my resolution 1534
    Raytracer.Run();

    return 0;
}

// TODO: Create Scene-changing functionality to the window, to switch between them using keyboard

// TODO: (IDEA) Make volumes where intersection function, is simply random generator where probability is dependent on density, the denser the volume, the more particles are hit and so it will maybe look like clouds.

// TODO: Implement normal differentation between inside and outside in pixel colouring methods

// TODO: IDEA track mouse location on the screen, then use this location as a middle point of projection plane, and calculate left upper corner and render direction vectors based on that, pointer will be always at the middle, and how far it is is defined by the focal length of camera, use scroll to change the focal length
