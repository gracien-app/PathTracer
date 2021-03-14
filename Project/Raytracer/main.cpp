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

    return 0;
}

// TODO: Make the window open before renderer finishes initial render, so that the window is already visible when rendering.

// TODO: Split Solid and Sphere into separate files, or maybe make Geometry file for all geometrical figures

// TODO: Cube class with intersection.

// TODO: Calculating normals

// TODO: Basic shadows
