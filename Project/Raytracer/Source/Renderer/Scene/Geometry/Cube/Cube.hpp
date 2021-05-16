//
//  Cube.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 29/04/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Cube_hpp
#define Cube_hpp

#include "Rectangle.hpp"

/// @discussion [POLYMORPHIC] [COLLISIONS]
class Cube : public Solid {

public:
    
    ~Cube() override;
    
    Cube(const vect3D &centerPoint,
         const double sideLength,
         std::shared_ptr<Material> &materialPtr);
    
    /// Overloaded method checking if passed ray can intersect with infinite plane geometry.
    /// @param ray Reference to object of type Ray
    /// @param recent_Inter Reference to Recent structure which keeps track of recent intersections performed.
    /// @param timeMin Specifies minimum time when the intersection can occur.
    /// @param timeMax Specifies maximum time when the intersection can occur.
    /// @return - True if ray INTERSECTS the geometry.
    /// @return - False if no intersections occur.
    bool Intersect (const Ray &ray, intersection &recent_Inter, const double &timeMin, const double &timeMax) const override;
    
private:
    std::vector<std::unique_ptr<Rectangle>> cubeSides;
};

#endif /* Cube_hpp */
