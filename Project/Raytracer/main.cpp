//
//  main.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"
#include "main.h"

int main()
{
    App Raytracer(1534,1534); //maximum height for my resolution 1534
    Raytracer.Run();
    
    // FIXME: Fix dumb pointer usage in Renderer::getSprite()

    return 0;
}

// TODO: Make the window open before renderer finishes initial render, so that the window is already visible when rendering. <- Current goal, Scene needs rework, use pointer to wait with scene making till window is open.

// TODO: Cube class with intersection.

// TODO: Basic shadows using calculated normals

// TODO: (IDEA) Make volumes where intersection function, is simply random generator where probability is dependent on density, the denser the volume, the more particles are hit and so it will maybe look like clouds.

// TODO: Maybe use struct somewhere where class it not really needed?

// TODO: Implements normal differentation between inside and outside in pixel colouring methods


