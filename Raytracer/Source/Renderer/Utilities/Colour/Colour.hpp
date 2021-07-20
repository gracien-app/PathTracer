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

/// Helper class representing RGBA colour.
/// @discussion Created mainly to differentiate between vect3D objects which hold colour instead of position / vector.
/// Derives from vect3D to get access to already defined operators and _data array storage for partial components RGB.
/// Owns normalise method suitable for normalisation <0,1> of RGB colour, and standardise method used to transform colour back to standard form <0,255>
/// @note Alpha component is not used, although it was prepared for future expansion.
class Colour : public vect3D{
public:
    
    /// Default Colour constructor.
    /// @note Initialised using default vect3D constructor to (0.0, 0.0, 0.0) - perfect black.
    Colour();
    
    /// Destructor override of Base vect3D.
    ~Colour() override;
    
    /// Colour constructor creating colour from partial elements of vect3D object where XYZ = RGB
    /// @param rhs vect3D object from which partials are extracted to construct a RGB colour,
    Colour(const vect3D &rhs);
    
    /// Colour constructor creating colour from given partial elements RGB
    /// @param R Value defining Red partial element of colour.
    /// @param G Value defining Green partial element of colour.
    /// @param B Value defining Blue partial element of colour.
    Colour(const double &R, const double &G, const double &B);
    
    /// Method used to normalise partial elements of Colour. Partials are normalised using division by 255 (maximum value of partial).
    /// @note Multiplication by inverse (1/255) is performed because of how vect3D operator for division is implemented (uses multiplication by 1/div for each).
    /// @warning Method doesn't perform any checks whether Colour is not already normalised.
    Colour& normalizeRGB();
    
    /// Method used to prepare and write corrected pixel colour partials into pixels container.
    /// @param outPixels Pixel array to which data is written.
    /// @param gridPos Position of pixel (consists of 4 partials) in the image grid (width x height).
    /// @param samples Samples per pixel
    /// @discussion Sampling ratio is evaluated to average pixel colour partials.
    /// Sampling sums pixel colours throughout execution of the program, this method averages the result (Monte-Carlo simulation principles).
    /// Later, partials are multiplied by sampling ratio and squared.
    /// Squaring is a primitive solution to gamma correction (proper way, would be to power up each partial by ^1/2.2).
    /// Without gamma correction, colours look off compared to what was provided to the program (RGB colours from web look different).
    /// More on this topic here:
    /// https://blog.johnnovak.net/2016/09/21/what-every-coder-should-know-about-gamma/
    /// @note (Optimisation) Multiplication by inverse is performed, because of how vect3D operator/ is implemented (uses multiplication by 1/divisor).
    /// To compensate cast to int(), multiplication of 256 * 0.999 for maximum brightness is performed. Only this way, I was able to reach full spectrum (255).
    /// For 255 * 1.0, it's rounded to (254) instead.
    void standardiseOutput(std::vector<sf::Uint8> &outPixels, const int &gridPos, const int &samples);
    
private:
    
    /// Exists for future expansion. Not used throughout the program at the current stage.
    double Alpha;

};

/// Operator overload used to multiply Colours.
/// @discussion Only used in recursive part of Scene::colourRay method.
/// @note Function set to inline as a optimisation - Small, often called function.
inline Colour operator*(const Colour &lhs, const Colour &rhs) {
    return Colour(lhs.x()*rhs.x(),
                  lhs.y()*rhs.y(),
                  lhs.z()*rhs.z());
}


#endif /* Colour_hpp */
