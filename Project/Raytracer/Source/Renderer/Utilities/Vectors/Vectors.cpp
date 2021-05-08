//
//  Vectors.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Vectors.hpp"

// MARK: Constructors
vect3D::vect3D () : _data{0, 0, 0} {};
vect3D::vect3D(double x, double y, double z) : _data{x, y, z} {};

// MARK: Operators

double& vect3D::operator[] (const int &index) {
    return _data[index];
}

vect3D vect3D::operator- () const {
    return vect3D( -_data[0], -_data[1], -_data[2] );
}

vect3D& vect3D::operator+= (const vect3D &rhs) {
    _data[0] += rhs._data[0];
    _data[1] += rhs._data[1];
    _data[2] += rhs._data[2];
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
double vect3D::length() const {
    return sqrt(_data[0]*_data[0] + _data[1]*_data[1] + _data[2]*_data[2]);
}

double vect3D::lengthSquared() const {
    return (_data[0]*_data[0] + _data[1]*_data[1] + _data[2]*_data[2]);
}

double vect3D::dot(const vect3D &rhs) const {
    return _data[0]*rhs._data[0] + _data[1]*rhs._data[1] + _data[2]*rhs._data[2];
}

// MARK: Debug
void vect3D::printInfo() {
    std::cout << "Vector: " << this->x() << " " << this->y() << " " << this->z();
    std::cout << " Length: " << this->length() << std::endl;
}
