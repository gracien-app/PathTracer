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
//    _sky[0] += vect3D(45,50,172);
//    _sky[1] += vect3D(65,135,200);
    _sky[0] += vect3D(30,30,30);
    _sky[1] += vect3D(30,30,30);
    
    _sky[0].normalizeRGB();
    _sky[1].normalizeRGB();
    
    _camera.setFocal(1);

    spheres.push_back(Sphere(vect3D(0,0,1), 0.5, colour(241,123,21)));
    //MARK: Default scene, nice deep sky gradient ([0] is top, [1] bottom), camera at (0,0,0), with focal of 1.0
}

Scene::Scene(const vect3D &pointOfView, const colour &skyColour, const double focalLength) {
    _sky[0] += skyColour;
    _sky[1] += _sky[0];
    //FIXME: Maybe another constructor allowing for gradient input, right now its plain colour.
    
    _camera += pointOfView;
    _camera.setFocal(focalLength);
}

Camera& Scene::getCamera() {
    return _camera;
}

vect3D Scene::colourRay(const Ray& r) {
    
    auto t = spheres[0].Intersect(r); //Get the time of intersection
    if (t > 0) { //If time is positive then hit happened in front of camera, not behind, rays go to projection plane
        vect3D Normal = Normalize( r.pos(t) - spheres[0].getCenter() ); //Normal vector (perpendicular to the surface) for sphere is simply inverted vector from intersection point p(t) to sphere center -(C-P) = P-C.
        return vect3D ( Normal.x()+1, Normal.y()+1, Normal.z()+1 ) * 0.5 ; //same trick as below, to have <0,1> range, z is already <0,1> (front of camera and its normalised) so no need for +1 correction.
    }
    
    auto unit_R = r.getDest(); // Y can be between <-1,1> because of constant projectionHeight=2
    t = (unit_R.y()+1) * 0.5; // To make it go from <0, 1>
        
    return vect3D ( _sky[1]*(1-t) + _sky[0]*t );
    
    // MARK: Linear interpolation formula for sky gradient: (1-h) x colour_bottom + h x colour_top
}
