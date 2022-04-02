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

/// Cube class representing geometrical Cubic object which consists of six rectangular objects.
/// @discussion [POLYMORPHIC] [COLLISIONS]
class Cube : public Solid {

public:
    
    /// Cube destructor.
    /// @discussion Overloads the default Solid destructor to correctly deallocate data.
    ~Cube() override;
    
    /// Cube constructor creating Cubic object with given parameters.
    /// @discussion Normals for all Rectangle sides are defined OUTWARDS.
    /// @warning Cases where Cube is enclosing geometry ("Camera" is inside) might produce incorrect behaviour of ray reflections (incorrect lighting).
    /// That is because of implementation (Normal vectors are ALWAYS pointing outside of the geometry, at the current stage no differentiation is performed).
    /// @param centerPoint Value defining 3-dimensional point representing center of the geometry.
    /// @param sideLength Value defining total length of Cube side.
    /// @param materialPtr Pointer to material object.
    /// @note Cube is always axis-aligned. No rotations are possible at the current implementation stage.
    Cube(const vect3D &centerPoint,
         const double &sideLength,
         std::shared_ptr<Material> &materialPtr,
         const bool invertNormals = false);
    
    /// Overloaded method checking if passed ray can intersect with Cube geometry (six Rectangles in _cubeSides).
    /// @discussion Intersects ray with all rectangular sides and looks for the closest intersection available (copy of Scene::intersectScene method)
    /// @note For the implementation of intersection mechanism, one should refer to Rectangle::Intersect method.
    /// Maximum time of intersection is updated using temporary variable to find the minimal time of intersection.
    /// @param ray Reference to object of type Ray
    /// @param recent_Inter Reference to structure which keeps track of recent intersections data.
    /// @param timeMin Specifies minimum time when the intersection can occur.
    /// @param timeMax Specifies maximum time when the intersection can occur.
    /// @returns - TRUE if ray intersects the geometry. FALSE if no intersections occur.
    bool Intersect (const Ray &ray, Intersection &recent_Inter, const double &timeMin, const double &timeMax) const override;
    
private:
    std::vector<std::unique_ptr<Rectangle>> _cubeSides;
};

#endif /* Cube_hpp */
