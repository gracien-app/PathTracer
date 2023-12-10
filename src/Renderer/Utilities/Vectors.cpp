//
//  Vectors.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include <PathTracer/Renderer/Utilities/Vectors.hpp>

// MARK: Constructors & Destructor

vect3D::~vect3D() {};
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

// MARK: Methods

double vect3D::x() const {
    return _data[0];
}
double vect3D::y() const {
    return _data[1];
}
double vect3D::z() const {
    return _data[2];
}

double vect3D::Length() const {
    return sqrt(_data[0]*_data[0] + _data[1]*_data[1] + _data[2]*_data[2]);
}

double vect3D::lengthSquared() const {
    return (_data[0]*_data[0] + _data[1]*_data[1] + _data[2]*_data[2]);
}

double vect3D::Dot(const vect3D &rhs) const {
    return _data[0]*rhs._data[0] + _data[1]*rhs._data[1] + _data[2]*rhs._data[2];
}

