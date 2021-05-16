//
//  Sphere.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 14/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Sphere.hpp"

Sphere::~Sphere() {
    std::cout << "  [D] Sphere: Destructed" << std::endl;
}

Sphere::Sphere(const vect3D &centerPoint,
               const double radius,
               std::shared_ptr<Material> &materialPtr) : _radius(radius),
                                                        Solid(centerPoint, materialPtr) {}

bool Sphere::Intersect (const Ray &ray, intersection &recent_Inter, const double &timeMin, const double &timeMax) const {
    
    auto OriginC = ray.getOrigin()-_center;
    auto a = ray.getDir().lengthSquared();
    auto optim_b = ray.getDir().dot(OriginC);
    auto c = OriginC.lengthSquared()-(_radius*_radius);
    
    auto delta = optim_b*optim_b - a*c;
    
    if (delta < 0) return false;
    else {
        auto deltaSqrt = sqrt(delta);
        
        auto root = (-optim_b - deltaSqrt) / a;
        if (root > timeMax || root < timeMin) {
            root = (-optim_b + deltaSqrt) / a;
            if (root > timeMax || root < timeMin) {
                return false; //If both failed.
            }
        }
        
        recent_Inter.time       = root;
        recent_Inter.position   = ray.getPos(root);
        recent_Inter.outNormal  = ( recent_Inter.position - _center ) / _radius;
        recent_Inter.material   = _material;
        return true;
    }
}
    // MARK: Optimisations performed:
    //      - Smaller root is prioritised. Then compared first against the time constraints (timeMin,timeMax)
    //      - Square root of Delta calculated only if necessary: when there are roots
    //      - First checking smaller root, if fails the check, ONLY then the bigger root is calculated.
    //      - Instead of Normalize() method of vect3D, radius of the sphere is used to normalize the normal vector.

