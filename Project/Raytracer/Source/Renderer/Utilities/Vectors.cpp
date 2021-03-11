//
//  Vectors.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Vectors.hpp"
#include <iostream>
#include <cmath>

// MARK: Constructors
vect3D::vect3D() : _data{0,0,0} {};
vect3D::vect3D(double x, double y, double z) : _data{x,y,z} {};

// MARK: Operators
vect3D& vect3D::operator += (const vect3D &rhs) {
    _data[0] += rhs._data[0];
    _data[1] += rhs._data[1];
    _data[2] += rhs._data[2];
    return *this;
}

vect3D& vect3D::operator -= (const vect3D &rhs) {
    _data[0] -= rhs._data[0];
    _data[1] -= rhs._data[1];
    _data[2] -= rhs._data[2];
    return *this;
}

vect3D& vect3D::operator *= (const vect3D &rhs) {
    _data[0] *= rhs._data[0];
    _data[1] *= rhs._data[1];
    _data[2] *= rhs._data[2];
    return *this;
}

vect3D& vect3D::operator /= (const vect3D &rhs) {
    _data[0] /= rhs._data[0];
    _data[1] /= rhs._data[1];
    _data[2] /= rhs._data[2];
    return *this;
}

vect3D& vect3D::operator *= (const double multiplier) {
    _data[0] *= multiplier;
    _data[1] *= multiplier;
    _data[2] *= multiplier;
    return *this;
}

vect3D& vect3D::operator /= (const double divider) {
    _data[0] /= divider;
    _data[1] /= divider;
    _data[2] /= divider;
    return *this;
}

// MARK: Private data access
double vect3D::x() const {
    return _data[0];
}
double vect3D::y() const {
    return _data[1];
}
double vect3D::z() const {
    return _data[2];
}

// MARK: Utility methods
double vect3D::Length() const {
    return sqrt(_data[0]*_data[0] + _data[1]*_data[1] + _data[2]*_data[2]);
}

double vect3D::Dot(const vect3D &rhs) const {
    return _data[0]*rhs._data[0] + _data[1]*rhs._data[1] + _data[2]*rhs._data[2];
}

// MARK: Debug
void vect3D::printInfo() {
    std::cout << "Vector: " << this->x() << " " << this->y() << " " << this->z();
    std::cout << " Length: " << this->Length() << std::endl;
}




