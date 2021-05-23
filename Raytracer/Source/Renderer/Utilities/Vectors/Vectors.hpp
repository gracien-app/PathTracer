//
//  Vectors.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Vectors_hpp
#define Vectors_hpp

#include "Utilities.h"

/// Class representing 3-dimensional vector.
/// @discussion vect3D is used both as a point, and as a vector.
/// Contains all necessary operators and methods used to determine mathematical properties of vectors.
class vect3D {
public:
    
    // MARK: Constructors & Destructor
    
    /// Default constructor, initalises all partials to 0's.
    vect3D();
    
    /// Virtual destructor of vect3D.
    virtual ~vect3D();
    
    /// Constructor initialises partials according to passed arguments.
    /// @param x Value defining X partial of the vector
    /// @param y Value defining Y partial of the vector
    /// @param z Value defining Z partial of the vector
    vect3D(double x, double y, double z);

    // MARK: Operators
    
    /// Bracket operator overload used to access private partial components of the vector.
    /// @param index Index of the partial to be accessed (X Y Z).
    double& operator[](const int &index);
    
    /// Operator overload returning value (copy) of inverted vector.
    /// @const *this data is not altered.
    vect3D operator-() const;
    
    /// Addition operator overload. Adds rhs vector components to *this.
    /// @param rhs vect3D to be added to *this
    vect3D& operator+=(const vect3D &rhs);
    
    // MARK: Methods
    
    /// Method which returns value of X vector component
    ///@const *this data is not altered.
    double x() const;
    
    /// Method which returns value of Y vector component
    ///@const *this data is not altered.
    double y() const;
    
    /// Method which returns value of Z vector component
    ///@const *this data is not altered.
    double z() const;
    
    /// Method which returns value of length of the vector.
    ///@const *this data is not altered.
    double Length() const;
    
    /// Method which returns value of square of length of vector (without sqrt).
    ///@const *this data is not altered.
    double lengthSquared() const;
    
    /// Method which returns value of dot product calculated for *this and vector rhs.
    ///@const *this data is not altered.
    /// @param rhs Second vector for the dot product.
    double Dot(const vect3D &rhs) const;
    
protected:
    double _data[3];
};

/// Addition operator overload
/// @param lhs Left side vector for the addition
/// @param rhs Right side vector for the addition
/// @note Inline - Small, often used operator.
inline vect3D operator+(const vect3D &lhs, const vect3D &rhs) {
    return vect3D(lhs.x()+rhs.x(),
                  lhs.y()+rhs.y(),
                  lhs.z()+rhs.z());
}

/// Subtraction operator overload
/// @param lhs Left side vector for the subtraction
/// @param rhs Right side vector for the subtracion
/// @note Inline - Small, often used operator.
inline vect3D operator-(const vect3D &lhs, const vect3D &rhs) {
    return vect3D(lhs.x()-rhs.x(),
                  lhs.y()-rhs.y(),
                  lhs.z()-rhs.z());
}

/// Multiplication by constant operator overload
/// @param multiplier Value of multiplier.
/// @param rhs Right side vector for the multiplication
/// @note Inline - Small, often used operator.
inline vect3D operator*(const double &multiplier, const vect3D &rhs) {
    return vect3D(rhs.x()*multiplier,
                  rhs.y()*multiplier,
                  rhs.z()*multiplier);
}

/// Multiplication by constant operator overload
/// @param lhs Left side vector for the multiplication
/// @param multiplier Value of multiplier.
/// @note Inline - Small, often used operator.
inline vect3D operator*(const vect3D &lhs, const double &multiplier ) {
    return multiplier*lhs; // Using the above operator.
}

/// Division by constant operator overload
/// @param lhs Dividend
/// @param divider Value of divisor
/// @note Inline - Small, often used operator.
inline vect3D operator/(const vect3D &lhs, const double &divider) {
    return (1/divider)*lhs; // Using multiplication by inverse.
}

/// Method used to obtain normalised value of vector.
/// @param vector Vector to be normalised.
/// @note Inline - Small, often used method.
inline vect3D Normalise(const vect3D &vector) {
    return vector / vector.Length();
}

/// Method used to obtain randomised value of vector
/// @param min Lower bound of partials XYZ
/// @param max Upper bound of partials XYZ
/// @note Inline - Small, often used method.
inline static vect3D Randomise(const double &min, const double &max) {
        return vect3D(randomNumber<double>(min, max),
                      randomNumber<double>(min, max),
                      randomNumber<double>(min, max));
}

/// Method used to generate random vector of length <1.
/// @warning Naming convention might be confusing, method generates random vector of length SMALLER than 1.
/// @discussion Generates randomised vector until condition (lengthSquared < 1) is passed.
/// @note Inline - Small, often used method. It's not necessary to square the length.
inline vect3D randUnitVect() {
    
    while (true) {
        auto randomVector = Randomise(-1,1);
        if (randomVector.lengthSquared() >= 1) continue;
        return randomVector;
    }
    
}

/// Method used to generate random vector of length < 1 with respect to the normal vector passed.
/// @note Newly generated direction is on the same side.
/// @param normal Normal vector acting as a reference for newly generated random direction.
/// @note Inline - Small, often used method.
inline vect3D randUnitDir(const vect3D &normal) {
    vect3D unitVec = randUnitVect();
    
    if (unitVec.Dot(normal) > 0.0) return unitVec; //If dot is positive then they are on the same side
    else return -unitVec;                          //Otherwise negate the vector to correct it
}

#endif /* Vectors_hpp */
