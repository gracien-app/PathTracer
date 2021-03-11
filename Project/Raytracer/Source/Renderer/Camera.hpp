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
    
    vect3D& getPos() const;
private:
    vect3D position;
};

#endif /* Camera_hpp */
