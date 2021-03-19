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
    
    Camera();
    Camera(const double &focal, const vect3D &position);

    void setFocal(const double &focalLength);
    void setFocal(vect3D &position);
    
    double camFocal() const;
    vect3D camPos() const;

private:
    double _focalLenght;
    vect3D _origin;
};

#endif /* Camera_hpp */
