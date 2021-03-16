//
//  Colour.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 16/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Colour.hpp"

colour::colour() : vect3D(), Alpha(255) {};
colour::colour(const vect3D &rhs) : vect3D(rhs.x(),rhs.y(),rhs.z()), Alpha(255) {};
colour::colour(unsigned int R, unsigned int G, unsigned int B) : vect3D(R,G,B), Alpha(255) {};
colour::colour(unsigned int R, unsigned int G, unsigned int B, unsigned int A) : vect3D(R,G,B), Alpha(A) {};

colour& colour::normalizeRGB() {
    this->_data[0] /= 255;
    this->_data[1] /= 255;
    this->_data[2] /= 255;
    this->Alpha /= 255;
    return *this;
}

void colour::standardizeOutput(std::vector<sf::Uint8> &outPixels, const int &gridPos) const {
    outPixels[4*gridPos+0] = int(this->x()*255.999);
    outPixels[4*gridPos+1] = int(this->y()*255.999);
    outPixels[4*gridPos+2] = int(this->z()*255.999);
    outPixels[4*gridPos+3] = int(this->Alpha*255.999);
    //.999 to compensate < width, height
}

// MARK: Debug
void colour::printInfo() {
    std::cout << "RGBA: " << this->x() << " " << this->y() << " " << this->z();
    std::cout << " Alpha: " << this->Alpha << std::endl;
}

