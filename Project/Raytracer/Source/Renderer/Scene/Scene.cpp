//
//  Scene.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Scene.hpp"

Scene::Scene() {
    _sky[0] += vect3D(43,50,178);
    _sky[1] += vect3D(20,136,204);
    
    _sky[0].normRGB();
    _sky[1].normRGB();
    
    _camera.setFocal(1.0);
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

vect3D Scene::spaceColour(const Ray& r)  {
    auto unit_R = Normalize(r.getDest()); // vector is of length 1 now and xyz are <0,1>
    double height = (unit_R.y()+1) * 0.5; //To get the height, 0 for upper part, 1 for bottom
    //For -1 the output is 0, for 1 its 1 so fits, maybe change it later
    
    return _sky[1]*(1-height) + _sky[0]*height;
    
    // MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top
}
