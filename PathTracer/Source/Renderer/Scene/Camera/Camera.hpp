//
//  Camera.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 10/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Camera_hpp
#define Camera_hpp

#include "Ray.hpp"

/// Helper class used to separate point of view / projection logic from the renderer engine.
/// @discussion Created with expansion in mind. Base class for Scene, defines point of view from which geometry is rendered.
class Camera {
public:
    
    //MARK: Constructor
    
    /// Camera object constructor.
    /// @discussion Camera is a point from which the scene is seen. It's a wrapper class made with expansion in mind (moving the point of view).
    /// To mimic how real camera works (lens) an imaginary projection plane is created.
    /// The distance between camera and projection plane is defined as focal length
    /// Projection plane defines direction of each ray (origin of each initial ray is the same - camera origin point).
    /// Rendering should start from left upper corner (abbrev. LUC). This is because SFML transfers pixels array to texture starting from this point.
    /// To find LUC for any focal length, and any resolution, appropriate vectors are added and subtracted (More specific comments in .cpp file).
    /// @note X Y and Z coordinates respect Right Handed Coordinate system, otherwise vector operations would need corrections.
    /// +X goes to right, +Y is up, +Z is BEHIND the camera.
    /// @param position 3-dimensional vector defining point of view, origin of the camera.
    /// @param focal Value defining focal length of the camera
    /// @param resWidth Value defining width of the application
    /// @param resHeight Value defining height of the application
    Camera(const vect3D &pos, const double &fovDeg, const int &width, const int &height);
    
    //MARK: Methods
    
    /// Method used to prepare Ray object with respect to Camera parameters (focal length, resolution)
    /// @discussion Origin remains unchanged, Direction is determined in such way:
    /// To the starting point of the render (left upper corner - LUC) partials of X and Y vectors are added or subtracted.
    /// X and Y vectors define total width and height. They allow to move by a given fraction in any direction.
    /// @example To move to the middle pixel (from LUC), we can add half of whole X vector (move right by half) and subtract half of Y (move down by half).
    /// @param x Value defining a fraction by which X vector should be moved.
    /// @param y Value defining a fraction by which Y vector should be moved
    Ray prepRay(const double &x, const double &y);
    
    void Move(const vect3D &moveVect);
    void setFOV(const double &newValue);
    void calibrate();

private:
    
    double _FOV;
    double _viewH;
    double _viewW;
    double _aspect;

    vect3D _X;
    vect3D _Y;
    vect3D _LUC;
    vect3D _Depth;
    vect3D _origin;
    
};

#endif /* Camera_hpp */
