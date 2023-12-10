//
//  Utilities.h
//  Raytracer
//
//  Created by Gracjan Jeżewski on 21/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Utilities_h
#define Utilities_h

#include <cmath>
#include <random>
#include <iostream>

/// Template function used to generate random number using Mersenne-Twister RNG. Numbers are generated within <0,1> range.
/// @warning To prevent data race in multi-threaded usage, thread_local flag is used to provide each thread with its own distribution and generator.
template <typename T>
inline T randomNumber() {
    thread_local static std::uniform_real_distribution<T> range(0.0, 1.0);
    thread_local static std::mt19937 generator;
    return range(generator);
}

/// Template function used to generate random number using Mersenne-Twister RNG. Numbers are generated within <min,max> range.
/// @warning To prevent data race in multi-threaded usage, thread_local flag is used to provide each thread with its own distribution and generator.
/// @param min Minimal number which can be generated.
/// @param max Maximal number which can be generated.
template <typename T>
inline T randomNumber(const T &min, const T &max) {
    thread_local static std::uniform_real_distribution<T> range(min, max);
    thread_local static std::mt19937 generator;
    return range(generator);
}

/// Function which "clamps" a value between an upper and lower bound.
/// @discussion Used extensively during rendering to make sure that values are within proper, often normalised <0,1> range.
/// @param x Value to be clamped.
/// @param min Lower bound of clamping
/// @param max Upper bound of clamping
template <typename T>
inline T clamp(T x, T min, T max) {
    if (x > max) return max;
    if (x < min) return min;
    return x;
}

/// Template variable (C++ 14 standard) used to determine upper bound of type T.
/// @discussion Used to determine theoretical infinity (rays need upper distance / time bound)
template <typename T>
const T infinity = std::numeric_limits<T>::infinity();


#endif /* Utilities_h */
