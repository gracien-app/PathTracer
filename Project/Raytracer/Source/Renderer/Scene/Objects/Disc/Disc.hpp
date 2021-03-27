//
//  Disc.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include "Solid.hpp"

class Disc : public Solid {
public:
    Disc(const vect3D &centerPoint, const vect3D &normalDirection, const double sideLength, const colour &colour);
    
    bool Intersect (const Ray &ray, recent &recent_Inter, double timeMin, double timeMax) const;
    
private:
    double _side;
    vect3D _normal;
};


#endif /* Plane_hpp */
