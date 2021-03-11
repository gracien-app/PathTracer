//
//  Vectors.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Vectors_hpp
#define Vectors_hpp

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
    
//    vect3D operator + (const vect3D& lhs, const vect3D& rhs);
    
    // MARK: Private data access
    double x() const;
    double y() const;
    double z() const;
    
    // MARK: Utility methods
    double Length() const;
    double Dot(const vect3D &rhs) const;
    
    // MARK: Debug methods
    void printInfo();
    
private:
    double _data[3];
};


#endif /* Vectors_hpp */
