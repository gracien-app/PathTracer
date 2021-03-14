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
    
    _camera.setFocal(1);
    
    sphere1 = new Sphere(vect3D(0,0,1), 0.5, vect3D(228, 158, 62));
    
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
    if (sphere1->Intersects(r)) {
        return sphere1->getColour();
    }
    
    else {
        auto unit_R = r.getDest(); // Y can be between <-1,1> because of constant projectionHeight=2
        double height = (unit_R.y()+1) * 0.5; // To make it go from <0, 1>
        
        return _sky[1]*(1-height) + _sky[0]*height;
    }
    // MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top
}
