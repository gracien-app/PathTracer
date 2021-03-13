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
    double getFocal() const;
    vect3D getPosition() const;

private:
    double _focalLenght;
    vect3D _origin;
};

#endif /* Camera_hpp */
