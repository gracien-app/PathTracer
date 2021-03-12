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
    App Raytracer(1200,1000); //maximum height for my resolution 1534
    Raytracer.Run();
    
    //testing pos
    
//    vect3D origin(1,2,3);
//    vect3D destination(4,5,6);
//
//    Ray ray1(origin,destination);
//
//    vect3D test1 = ray1.pos(0); // should be origin (1 2 3) + (0*4 0*5 0*6) so 1 2 3
//
//    test1 = ray1.pos(1); //should be past destination, and (1 2 3) + (1*4 1*5 1*6) so 5 7 9
//    auto test = Normalize(test1);
//
//    vect3D colourtest(41,128,185);
//    colourtest.printInfo();
//    colourtest.normRGB();
//    colourtest.printInfo();
    
    return 0;
}
