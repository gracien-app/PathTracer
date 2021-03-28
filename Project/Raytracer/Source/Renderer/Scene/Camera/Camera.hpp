//
//  Camera.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Vectors.hpp"
#include "Ray.hpp"
#include <vector>
#include <memory>

class Camera {
public:
    
    Camera( const vect3D &position, const double &focal, const int &resWidth, const int &resHeight);
    Ray prepRay(double X, double Y);

private:
    
    double _focalLenght;
    double _aspectRatio; // Resolution Width/Height
    double _projectionHeight;
    double _projectionWidth;

    vect3D _X;
    vect3D _Y;
    vect3D _LUC;
    vect3D _Depth;
    vect3D _origin;
    
};

#endif /* Camera_hpp */
