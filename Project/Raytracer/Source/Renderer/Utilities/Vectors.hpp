//
//  Vectors.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Vectors_hpp
#define Vectors_hpp

#include "main.h"

class vect3D {
public:
    //Constructors
    vect3D();
    vect3D(double x, double y, double z);

    //Operators
    vect3D& operator += (const vect3D &rhs); // += to not make a copy
    vect3D& operator -= (const vect3D &rhs); // as above
    
    vect3D& operator *= (const vect3D &rhs);
    vect3D& operator /= (const vect3D &rhs);
    vect3D& operator *= (const double multiplier);
    vect3D& operator /= (const double divider);
    
    double x() const;
    double y() const;
    double z() const;
    
    double Length() const;
    
private:
    double _data[3];
};

#endif /* Vectors_hpp */
