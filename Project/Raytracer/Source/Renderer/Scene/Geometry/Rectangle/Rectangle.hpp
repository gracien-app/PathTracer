//
//  Rectangle.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 29/04/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "Disc.hpp"

class Rectangle : public Solid {
public:
    
    /// Rectangle constructor for creation of one-sided rectangular object.
    /// @param centerPoint Vector point defining position of the central point of the geometry
    /// @param normalDirection Normal vector of the geometry, defines direction towards which geometry is oriented.
    /// @param sideLength Length of the side of the rectangle
    /// @param colour Colour object defining colour of the geometry
    Rectangle(const vect3D &centerPoint,
              const vect3D &normalDirection,
              const double sideLength,
              std::shared_ptr<Material> &materialPtr);
    
    /// @brief Overloaded method checking if passed ray can intersect with rectangle geometry.
    /// @param ray Reference to object of type Ray
    /// @param recent_Inter Reference to Recent structure which keeps track of recent intersections performed.
    /// @param timeMin Specifies minimum time when the intersection can occur.
    /// @param timeMax Specifies maximum time when the intersection can occur.
    /// @return - True if ray INTERSECTS the geometry.
    /// @return - False if no intersections occur.
    bool Intersect (const Ray &ray,
                    collision &recent_Inter,
                    const double &timeMin,
                    const double &timeMax) const override;
    
private:
    double _side;
    double _xmin, _xmax;
    double _ymin, _ymax;
    double _zmin, _zmax;
    vect3D _normal;
};


#endif /* Rectangle_hpp */
