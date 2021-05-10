//
//  Camera.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera( const vect3D &position, const double &focal, const int &resWidth, const int &resHeight) {
    
    _origin = position;
    _focalLenght = focal;
    _aspectRatio = resWidth / resHeight; //MARK: Aspect to see how height defines width
    
    _projectionHeight = 2.0; //MARK: Height coordinates go from -1,1 so the total length is 2.
    _projectionWidth = _projectionHeight*_aspectRatio; //MARK: Defining the width of coordinate system based on height.
    
    _Depth = vect3D(0, 0, _focalLenght);
    _X = vect3D(_projectionWidth, 0, 0);
    _Y = vect3D(0, _projectionHeight, 0);
    _LUC = vect3D(_origin - _Depth + _Y/2 - _X/2);
    
    //MARK: Direction vector defining the direction of rendering in X axis (Default = RIGHT)
    //MARK: Direction vector defining the direction of rendering in Y axis (Default = UP).
    //MARK: Direction vector defining the depth (Z coordinate) of the viewport.
    //MARK: FIXED Position vector of LEFT UPPER corner of viewport, starting point of rendering.
}

Ray Camera::prepRay(const double &x, const double &y) {
    return Ray(_origin, (_LUC + _X*x - _Y*y));
}
