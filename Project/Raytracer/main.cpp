//
//  main.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"

int main()
{
    App* Raytracer = new App();
    Raytracer->Run();
    delete Raytracer;
    Raytracer = nullptr;
    return 0;
}
