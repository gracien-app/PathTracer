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

Camera::Camera( const vect3D &position, const double &focal, const int &resWidth, const int &resHeight) {
    
    _origin = position;
    _focalLenght = focal;
    _aspectRatio = resWidth / resHeight; //MARK: How height defines width.
    
    _projectionHeight = 2.0; //MARK: Height coordinates go from -1,1 so the total length is 2.
    _projectionWidth = _projectionHeight*_aspectRatio; //MARK: Defining the width of projection based on height.
    
    _Depth = vect3D(0, 0, _focalLenght);
    _X = vect3D(_projectionWidth, 0, 0);
    _Y = vect3D(0, _projectionHeight, 0);
    _LUC = vect3D(_origin - _Depth + _Y/2 - _X/2);
    
    //MARK: Depth - Direction vector defining the depth (Default = +Z)
    //MARK: X - Direction vector defining the direction of rendering in X axis (Default = +X)
    //MARK: Y - Direction vector defining the direction of rendering in Y axis (Default = +Y).
    //MARK: LUC - Left upper corner of projection plane.
    //MARK: Camera origin is middle point, move up by half (Y/2), move left by half (-X/2) and move by -focal (RH Coord)
    
}
