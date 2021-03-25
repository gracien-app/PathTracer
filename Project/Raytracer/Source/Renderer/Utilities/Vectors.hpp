//
//  Vectors.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Vectors_hpp
#define Vectors_hpp

#include <iostream>
#include <cmath>
#include "Utilities.h"

class vect3D {
public:
    // MARK: Constructors
    vect3D();
    vect3D(double x, double y, double z);

    // MARK: Operators
    double& operator[] (const int &index);
    
    vect3D& operator += (const vect3D &rhs); // += to not make a copy
    vect3D& operator -= (const vect3D &rhs); // as above
    
    vect3D& operator *= (const double multiplier);
    vect3D& operator /= (const double divider);
    
    // MARK: Private data access
    double x() const;
    double y() const;
    double z() const;
    
    // MARK: Utility methods
    double length() const;
    double lengthSquared() const;
    double dot(const vect3D &rhs) const;
    
    // MARK: Debug methods
    virtual void printInfo();
    
protected:
    double _data[3];
};

    //MARK: Utility functions
inline vect3D operator+(const vect3D &lhs, const vect3D &rhs) {
    return vect3D(lhs.x()+rhs.x(),
                  lhs.y()+rhs.y(),
                  lhs.z()+rhs.z());
}

inline vect3D operator-(const vect3D &lhs, const vect3D &rhs) {
    return vect3D(lhs.x()-rhs.x(),
                  lhs.y()-rhs.y(),
                  lhs.z()-rhs.z());
}

inline vect3D operator*(const double multiplier, const vect3D &lhs) {
    return vect3D(lhs.x()*multiplier,
                  lhs.y()*multiplier,
                  lhs.z()*multiplier);
}

inline vect3D operator*(const vect3D &lhs, const double multiplier ) {
    return multiplier*lhs; //Using the above;
}

inline vect3D operator/(const vect3D &lhs, const double divider) {
    return vect3D(lhs.x()*(1/divider),
                  lhs.y()*(1/divider),
                  lhs.z()*(1/divider));
}

inline vect3D Normalize(const vect3D &vector) {
    return vector / vector.length();
}

inline std::ostream& operator << (std::ostream &output, const vect3D &vector) {
    return output << "[ " << vector.x() << " " << vector.y() << " " << vector.z() << " ]\n";
}

inline static vect3D randomize() {
        return vect3D( randomDouble(), randomDouble(), randomDouble() );
}

inline static vect3D randomize(double min, double max) {
        return vect3D( randomDouble(min, max), randomDouble(min, max), randomDouble(min, max) );
}

inline vect3D randInSphere() {
    while (true) {
        auto gen = randomize(-1,1);
        if (gen.lengthSquared() >= 1) continue;
        return gen;
    }
}


#endif /* Vectors_hpp */
