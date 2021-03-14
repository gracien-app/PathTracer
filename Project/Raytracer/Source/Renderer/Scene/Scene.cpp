//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene() {
    //https://uigradients.com/#Skyline
    _sky[0] += vect3D(45,50,172);
    _sky[1] += vect3D(65,135,200);
    _sky[0].normRGB();
    _sky[1].normRGB();
    
    _camera.setFocal(0.3);
    _camera+= vect3D(0,0,0);
    
    int max = 5000;
    
    spheres.reserve(max);
    
//    spheres.push_back(Sphere(vect3D(0,0,2), 0.1, vect3D(83,159,120)));
//    spheres.push_back(Sphere(vect3D(0,0.3,2), 0.15, vect3D(83,159,120)));
//    spheres.push_back(Sphere(vect3D(0,0.70,2), 0.2, vect3D(83,159,120)));
//    spheres.push_back(Sphere(vect3D(0,1.2,2), 0.25, vect3D(83,159,120)));
//    spheres.push_back(Sphere(vect3D(0,1.8,2), 0.3, vect3D(83,159,120)));
    
    //MARK: Genesio Tesi attractor test
    auto a = 0.44 ;
    auto b = 1.1;
    auto c = 1.0;
    
    auto x = 0.1;
    auto y = 0.1;
    auto z = 0.1;
    
    float dt = 0.01;
    
    spheres.push_back(Sphere((vect3D(x,y,z+1)), 0.005, vect3D(83,159,120)));
    
    for (int t = 0; t<max; t++) {
        x = x+y*dt;
        y = y+z*dt;
        z = z+(-c*x-b*y-a*z+x*x)*dt;
        
        spheres.push_back(Sphere((vect3D(x,y,z+1)), 0.005, vect3D(83,159,120)));
    }
    
    //MARK: Default scene, nice deep sky gradient ([0] is top, [1] bottom), camera at (0,0,0), with focal of 1.0
}

Scene::Scene(const vect3D &pointOfView, const vect3D &spaceColour, const double focalLength) {
    _sky[0] += spaceColour;
    _sky[1] += _sky[0];
    //FIXME: Maybe another constructor allowing for gradient input, right now its plain colour.
    
    _camera += pointOfView;
    _camera.setFocal(focalLength);
}

Camera& Scene::getCamera() {
    return _camera;
}

vect3D Scene::colourRay(const Ray& r)  {
    
    for (int i = 0; i<spheres.size(); i++) {
        if (spheres[i].Intersects(r)) {
            return spheres[i].getColour();
        }
    }
    
    auto unit_R = r.getDest(); // Y can be between <-1,1> because of constant projectionHeight=2
    double height = (unit_R.y()+1) * 0.5; // To make it go from <0, 1>
        
    return _sky[1]*(1-height) + _sky[0]*height;
    
    // MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top
}
