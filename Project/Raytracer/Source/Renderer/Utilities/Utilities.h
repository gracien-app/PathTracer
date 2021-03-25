//
//  Utilities.h
//  Raytracer
//
//  Created by Gracjan Jeżewski on 21/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Utilities_h
#define Utilities_h

#include <random>

inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

const double infinity = std::numeric_limits<double>::infinity();





#endif /* Utilities_h */
