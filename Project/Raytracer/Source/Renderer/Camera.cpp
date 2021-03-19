//
//  Camera.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera() : _focalLenght(1), _origin(0, 0, 0) { std::cout << "[C] Camera" << std::endl;};
Camera::Camera(const double &focal, const vect3D &position) : _focalLenght(focal), _origin(position) {};

void Camera::setFocal(const double &focalLength) {
    _focalLenght = focalLength;
}

void Camera::setFocal(vect3D &position) {
    _origin[0] = position[0];
    _origin[1] = position[1];
    _origin[2] = -position[2];
}

double Camera::camFocal() const {
    return _focalLenght;
}

vect3D Camera::camPos() const {
    return _origin;
}
