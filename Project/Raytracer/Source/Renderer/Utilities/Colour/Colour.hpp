//
//  Colour.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 16/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Colour_hpp
#define Colour_hpp

#include "Vectors.hpp"
#include <SFML/Graphics.hpp>

class colour : public vect3D{
public:
    
    colour();
    colour(const vect3D &rhs);
    colour(unsigned int R, unsigned int G, unsigned int B);
    colour(unsigned int R, unsigned int G, unsigned int B, unsigned int A);
    
    /// Method for transforming standard RGB values of vector to normalized values ranging from <0,1> used by the renderer.
    /// @warning Make sure that vector is not already normalized, no checks are performed.
    colour& normalizeRGB();
    
    void standardizeOutput(std::vector<sf::Uint8> &outPixels, const int &gridPos, const int &samples);
    void printInfo() override;
    
private:
    double Alpha;
};

inline colour operator*(const colour &lhs, const colour &rhs) {
    return colour(lhs.x()*rhs.x(),
                  lhs.y()*rhs.x(),
                  lhs.z()*rhs.x());
}


#endif /* Colour_hpp */
