//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene() {
    _space += vect3D(1.0,1.0,1.0); //Set colour of the space, default blue-ish sky colour.
//    _space.normRGB(); //Normalize RGB values to <0,1>
    //Camera _pov is set to (0,0,0) due to constructor of vect3D
    _pov.setFocal(1.0);
}

Scene::Scene(const vect3D &pointOfView, const vect3D &spaceColour, const double focalLength) {
    _space += spaceColour;
    _space.normRGB();
    _pov += pointOfView;
    _pov.setFocal(focalLength);
}

Camera& Scene::getCamera() {
    return _pov;
}

vect3D Scene::spaceColour(const Ray& r)  {
    auto unit_R = Normalize(r.getDest()); // vector is of length 1 now and xyz are <0,1>
    double height = (unit_R.y()+1) * 0.5; //To get the height, 0 for upper part, 1 for bottom
    //For -1 the output is 0, for 1 its 1 so fits, maybe change it later
    
//    return _space*(1-height) + vect3D(0.5, 0.7, 1)*height;
    return vect3D(0.5, 0.7, 1);
    
    // MARK: Linear interpolation formula for sky gradient: blend = (1-h) x colour_up + h x colour_down
    // MARK: Colours set acordingly to the sky colour, goes from dark blue to very light blue
    // MARK: https://uigradients.com/#CoolSky
}
