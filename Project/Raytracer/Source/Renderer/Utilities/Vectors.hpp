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

class vect3D {
public:
    // MARK: Constructors
    vect3D();
    vect3D(double x, double y, double z);

    // MARK: Operators
    vect3D& operator += (const vect3D &rhs); // += to not make a copy
    vect3D& operator -= (const vect3D &rhs); // as above
    
    vect3D& operator *= (const vect3D &rhs); //for future colour class possibly
    vect3D& operator /= (const vect3D &rhs); //for future colour class possibly
    vect3D& operator *= (const double multiplier);
    vect3D& operator /= (const double divider);
    
    // MARK: Private data access
    double x() const;
    double y() const;
    double z() const;
    
    // MARK: Utility methods
    double Length() const;
    double Dot(const vect3D &rhs) const;
    
    //FIXME: Make some colour class for this, might add rgb->cmyk
    vect3D& normRGB(); //to transfer RGB vector xyz values to normalised <0,1> for renderer. 
    
    // MARK: Debug methods
    void printInfo();
    
private:
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
    return vector / vector.Length();
}

inline std::ostream& operator << (std::ostream &output, const vect3D &vector) {
    return output << "[ " << vector.x() << " " << vector.y() << " " << vector.z() << " ]\n";
}

#endif /* Vectors_hpp */
