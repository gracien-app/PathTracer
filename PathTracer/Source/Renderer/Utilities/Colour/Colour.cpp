//
//  Colour.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 16/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Colour.hpp"
Colour::~Colour() {}
Colour::Colour() : vect3D() {}
Colour::Colour(const vect3D &rhs) : vect3D(rhs.x(),rhs.y(),rhs.z()) {}
Colour::Colour(const double &R, const double &G, const double &B) : vect3D(R,G,B) {}

Colour& Colour::normalizeRGB() {
    
    auto ratio = 1.0 / 255;
    
    this->_data[0] *= ratio;
    this->_data[1] *= ratio;
    this->_data[2] *= ratio;
    
    return *this;
    
}

void Colour::standardiseOutput(std::vector<sf::Uint8> &outPixels, const int &gridPos, const int &samples) {
    
    auto ratio = 1.0 / samples;
    
    auto R = sqrt(this->x() * ratio);
    auto G = sqrt(this->y() * ratio);
    auto B = sqrt(this->z() * ratio);
    
    outPixels[4*gridPos+0] = int(256 * clamp<double>(R, 0.0, 0.999));
    outPixels[4*gridPos+1] = int(256 * clamp<double>(G, 0.0, 0.999));
    outPixels[4*gridPos+2] = int(256 * clamp<double>(B, 0.0, 0.999));
    outPixels[4*gridPos+3] = 255;
    
}

void Colour::standardiseOutputPreview(std::vector<sf::Uint8> &outPixels, const int &gridPos) {
    
    outPixels[4*gridPos+0] = int(256 * sqrt(this->x()));
    outPixels[4*gridPos+1] = int(256 * sqrt(this->y()));
    outPixels[4*gridPos+2] = int(256 * sqrt(this->z()));
    outPixels[4*gridPos+3] = 255;
    
}

