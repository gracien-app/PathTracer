//
//  main.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 07/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "App.hpp"
#include "Ray.hpp"

int main()
{
//    App Raytracer(1534,1534); //maximum height for my resolution
//    Raytracer.Run();
    
    vect3D origin(1,2,3);
    vect3D destination(4,5,6);
    
    Ray ray1(origin,destination);
    ray1.printInfo();
    
    return 0;
}
