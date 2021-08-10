//
//  Camera.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Camera.hpp"

Ray Camera::prepRay(const double &x, const double &y) {
    return Ray(_origin, (_LUC + _X*x - _Y*y));
}

void Camera::Move(const vect3D &moveVect) {
    
    /// Move camera by displacement vector passed to the function.
    _origin += moveVect;
    
    /// Reevaluate Left Upper Corner (abbr. LUC) of the projection view.
    _LUC = vect3D(_origin - _Depth + _Y/2 - _X/2 - _origin);
}

Camera::Camera( const vect3D &pos, const double &fovDeg, const int &width, const int &height) {
    
    _origin = pos;
    _FOV = fovDeg * M_PI/180;
    
    auto focalLength = 1.0;
    auto H = tan(_FOV/2.0);
    auto aspectRatio = width / height; //MARK: How height defines width.
    
    _viewH = 2.0 * H; //MARK: Height coordinates go from -1,1 so the total length is 2.
    _viewW = _viewH * aspectRatio; //MARK: Defining the width of projection based on height.
    
    _Depth = vect3D(0, 0, focalLength);
    _X = vect3D(_viewW, 0, 0);
    _Y = vect3D(0, _viewH, 0);
    _LUC = vect3D(_origin - _Depth + _Y/2 - _X/2 - _origin);
    
    //MARK: Depth - Direction vector defining the depth (Default = +Z)
    //MARK: X - Direction vector defining the direction of rendering in X axis (Default = +X)
    //MARK: Y - Direction vector defining the direction of rendering in Y axis (Default = +Y).
    //MARK: LUC - Left upper corner of projection plane.
    //MARK: Camera origin is middle point, move up by half (Y/2), move left by half (-X/2) and move by -focal (RH Coord)
    
}
