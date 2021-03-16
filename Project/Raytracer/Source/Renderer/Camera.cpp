//
//  Camera.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Camera.hpp"

Camera::Camera() : _focalLenght(1), _origin(0, 0, 0) {};

Camera::Camera(const double &focal, const vect3D &position) : _focalLenght(focal), _origin(position) {};

Camera& Camera::operator+=(const vect3D &rhs) {
    this->_origin += rhs;
    return *this;
}

void Camera::setFocal(const double focalLength) {
    _focalLenght = focalLength;
}

double Camera::getFocal() const {
    return _focalLenght;
}

vect3D Camera::getPosition() const {
    return _origin;
}
