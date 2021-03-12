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

class Camera {
public:
    
    Camera& operator+=(const vect3D &rhs);
    
    void setFocal(const double focalLength);
    vect3D getPosition() const;
    
    double _focalLenght;
    double _projectionHeight;
    double _projectionWidth;
    
private:
    vect3D _origin;
};

#endif /* Camera_hpp */
