//
//  Plane.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 27/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Plane_hpp
#define Plane_hpp

#include "Solid.hpp"


class Plane : public Solid {
public:
    
    Plane(const vect3D &centerPoint, const vect3D &normalDirection, const colour &colour);
    
    bool Intersect (const Ray &ray, recent &recent_Inter, double timeMin, double timeMax) const override;
    
private:
    vect3D _normal;
};

#endif /* Plane_hpp */
