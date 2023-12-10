//
//  Sphere.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 14/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include <PathTracer/Renderer/Scene/Geometry/Sphere.hpp>

Sphere::~Sphere() {}

Sphere::Sphere(const vect3D &centerPoint, const double radius,
               std::shared_ptr<Material> &materialPtr) : _radius(radius), Solid(centerPoint, materialPtr) {}

bool Sphere::Intersect (const Ray &ray, Intersection &recent_Inter, const double &timeMin, const double &timeMax) const {
    
    // MARK: Below, partials of quadratic equation ax^2+bx+c are calculated for improved readability.
    auto OriginC = ray.origin()-_center;             // (Origin-Center vector)
    auto a = ray.direction().lengthSquared();              // Direction^2
    auto optim_b = ray.direction().Dot(OriginC);           // Direction * (Origin-Center)
    auto c = OriginC.lengthSquared()-(_radius*_radius); // (Origin - Center)^2 - Radius^2
    
    auto delta = optim_b*optim_b - a*c; // Delta = b^2 - 4*a*c
    
    if (delta < 0) return false; // No solutions of the quadratic equation
    
    else {
        auto deltaSqrt = sqrt(delta);
        
        auto root = (-optim_b - deltaSqrt) / a;
        if (root > timeMax || root < timeMin) {
            root = (-optim_b + deltaSqrt) / a;
            if (root > timeMax || root < timeMin) {
                return false; // If both roots are outside of lower or upper bound.
            }
        }
        
        // Save information about intersection to the passed Intersection structure
        recent_Inter.time       = root;
        recent_Inter.position   = ray.position(root);
        recent_Inter.outNormal  = ( recent_Inter.position - _center ) / _radius;
        recent_Inter.material   = _material;
        return true;
    }
    
}
    // MARK: Optimisations performed:
    //      - Smaller root is prioritised. Compared first against the time constraints (timeMin,timeMax)
    //      - Square root of Delta calculated only if necessary: when there are roots
    //      - First checking smaller root, if fails the check, ONLY then the bigger root is calculated.
    //      - Instead of Normalise() method of vect3D, radius of the sphere is used to normalize the normal vector.

