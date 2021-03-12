//
//  Camera.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Camera.hpp"

Camera& Camera::operator+=(const vect3D &rhs) {
    this->_origin += rhs;
    return *this;
}

void Camera::setFocal(const double focalLength) {
    _focalLenght = focalLength;
}

vect3D Camera::getPosition() const {
    return _origin;
}
