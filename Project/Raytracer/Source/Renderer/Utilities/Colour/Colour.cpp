//
//  Colour.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 16/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Colour.hpp"

colour::colour() : vect3D() {};
colour::colour(const vect3D &rhs) : vect3D(rhs.x(),rhs.y(),rhs.z()) {};
colour::colour(const double &R, const double &G, const double &B) : vect3D(R,G,B) {};

colour& colour::normalizeRGB() {
    this->_data[0] /= 255;
    this->_data[1] /= 255;
    this->_data[2] /= 255;
    return *this;
}

void colour::standardizeOutput(std::vector<sf::Uint8> &outPixels, const int &gridPos, const int &samples) {
    
    auto samplingScale = 1.0 / samples;
    
    auto R =  sqrt((this->x() * samplingScale));
    auto G =  sqrt((this->y() * samplingScale));
    auto B =  sqrt((this->z() * samplingScale));
    
    outPixels[4*gridPos+0] = int(256 * clamp<double>(R, 0.0, 0.999));
    outPixels[4*gridPos+1] = int(256 * clamp<double>(G, 0.0, 0.999));
    outPixels[4*gridPos+2] = int(256 * clamp<double>(B, 0.0, 0.999));
    outPixels[4*gridPos+3] = int(255);
    //.999 to compensate < width, height
}

// MARK: Debug
void colour::printInfo() {
    std::cout << "RGBA: " << this->x() << " " << this->y() << " " << this->z();
}

