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

template <typename T>
inline double randomNumber() {
    static std::uniform_real_distribution<T> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

template <typename T>
inline double randomNumber(double min, double max) {
    static std::uniform_real_distribution<T> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

template <typename T>
inline double clamp(T x, T min, T max) {
    if (x > max) return max;
    if (x < min) return min;
    return x;
}

template <typename T>
const T infinity = std::numeric_limits<T>::infinity();

#endif /* Utilities_h */
