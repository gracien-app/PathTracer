//
//  Scene.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Scene_hpp
#define Scene_hpp

#include "Cube.hpp"
#include "Camera.hpp"

/// Class representing Scene object which contains objects (Solids).
/// @discussion Created with expansion in mind, allows to easily create unique "scene" objects containing large amounts of geometry which can be rendered.
/// @note Contains the most important methods of the engine - colourRay and intersectScene.
/// Derives from Camera - each Scene must have a point of view from which it is rendered.
class Scene : public Camera {
public:
    
    // MARK: Constructors & Destructor
    
    /// Default destructor of Scene
    /// @brief Prints appropriate message to the console
    ~Scene();
    
    /// Constructor of Scene object.
    /// @brief Constructor uses switch statement to initalise scene preset according to variant passed.
    /// Camera object is initalised using initialiser list. at the current stage of the program, focal length and position is not changeable.
    /// @param width Value defining width of render, passed to Camera constructor.
    /// @param height Value defining height of render, passed to Camera constructor.
    /// @param variant Value defining variant of preset which will be initalised using switch statement.
    Scene(const int &width, const int &height, int &variant);
    
    // MARK: Methods
    
    /// Method used to initialise plain Scene containing Plane and Sphere objects.
    void plainScene();
    
    /// Method used to initialise Scene containing three Sphere objects and five walls created using Rectangle.
    void setupSpheres();
    
    /// Method used to initialise Scene containing "Cornell Box" preset.
    /// @brief Allows creation of two distinct versions - reflective and matte. Materials are created accordingly to the boolean passed
    /// note By default, matte version of the scene is created.
    /// @param reflective If TRUE, reflective version is created. Matte otherwise.
    void setupCornell(const bool &reflective = false);
    
    /// Method used to determine colour of the ray based on his origin, direction, and objects in the scene.
    /// @warning This method can be recursive (if intersection is found and ray bounces >= 1)
    /// @discussion Ray is "shoot" through the scene, conditions are checked whether ray reaches the sky (No intersections, ray bounces > 0).
    /// If a ray exceeds the number of bounces available or if recently hit geometry is a perfectly black object (ray is absorbed), function returns perfect black colour.
    /// At the current stage, light source is global (Global Illumination), what it means, is that light is available from all directions (if there are no obstacles).
    /// If ray intersects with any geometry in the scene, data is saved in temporary "intersection" structure.
    /// Afterwards Material::Reflect method is called, at this stage method can be recursive,
    /// If material "supports" reflection of the ray, new ray is constructed using Reflect.
    /// Appropriate values are passed to intersectScene method, they represent lower and upper (infinity) bound of time at which intersection can occur.
    /// @note Linear interpolation (horizontal gradient) formula is used for the sky (global light source).
    /// heightColour = (1-height) x colourBottom + height x colourTop.
    /// @warning Material colour must be NORMALISED <0,1>! Colour between bounces is accumulated using multiplication.
    /// @param r Ray with starting position and direction defined
    /// @param rayBounces Value defining how many times a ray can be bounced (reflected).
    /// @returns Colour accumulated from the ray traveling, with normalised partial components RGB.
    Colour colourRay(const Ray& r, const int &rayBounces) const;
        
private:
    
    /// Method used to determine whether passed ray (with origin and direction defined) intersects with any geometry in the scene.
    /// @discussion Temporary variables are created to store information about potential candidates, method looks for CLOSEST intersection.
    /// Order of objects in the objects container can be random. Method looks for minimal time of intersection to find objects which are closest.
    /// If new proper intersection is found, passed intersection data is updated based on data from temporary containers.
    /// @note Upper bound passed should preferably define numerical "infinity" of the program.
    /// @param ray Ray object with origin and direction defined.
    /// @param recent_Inter Recent intersection data
    /// @param tMin Lower bound of time at which intersection can occur (necessary to prevent intersections which tend to 0).
    /// @param tMax Upper bound of time at which intersection can occur.
    /// @returns TRUE if any intersection occurs. FALSE otherwise.
    bool intersectScene (const Ray &ray, Intersection &recent_Inter, const double &tMin, const double &tMax) const;
    
    std::vector<Colour> _skyGradient;
    std::vector<std::unique_ptr<Solid>> _sceneObjects;
};

#endif /* Scene_hpp */
