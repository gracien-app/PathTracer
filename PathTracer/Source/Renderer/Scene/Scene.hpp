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
    /// Camera object is initalised using initialiser list. At the current stage of the program, focal length and position is not changeable.
    /// @param width Value defining width of render, passed to Camera constructor.
    /// @param height Value defining height of render, passed to Camera constructor.
    /// @param variant Value defining variant of preset which will be initalised using switch statement.
    Scene(const int &width, const int &height, int &variant);
    
    // MARK: Methods
    
    void plainScene();
    
    void nvidiaScene();
    
    void lightScene();
    
    void roomsScene();
    
    void furnaceTestScene();
    
    void ballLightsScene();
    
    void blueSpheresScene();
    
    /// Method used to initialise Scene containing "Cornell Box" preset.
    /// @brief Allows creation of two distinct versions - reflective and matte. Materials are created accordingly to the boolean passed
    /// note By default, matte version of the scene is created.
    /// @param reflective If TRUE, reflective version is created. Matte otherwise.
    void cornellScene(const bool &reflective = false);
    
    /// Method used to determine colour of the ray based on his origin, direction, and objects in the scene.
    /// @warning This method can be recursive (if intersection is found and ray bounces >= 1)
    /// @discussion Ray is travelling through the scene, conditions are checked whether ray reaches the sky (No intersections, ray bounces > 0).
    /// If ray exceeds the number of bounces available or if recently hit geometry is a perfectly black object (ray is absorbed), function returns complete black.
    /// @note Linear interpolation (horizontal gradient) formula is used for the sky (global light source).
    /// heightColour = (1-height) x colourBottom + height x colourTop.
    /// @warning Material colour must be NORMALISED <0,1>! Colour is a product of attenuation from consecutive bounces.
    /// @param r Ray shot into the scene
    /// @param rayBounces Value defining how many times a ray can be bounced (reflected).
    /// @returns Colour accumulated from the ray path, with normalised partial components RGB.
    Colour traverseRegular(const Ray& r, const int &rayBounces) const;
    
    Colour traverseDepth(const Ray &r) const;
    
    Colour traverseNormal(const Ray &r) const;
    
    Colour traverseTurbo(const Ray &r, const float (&turbo_map)[256][3]) const;
        
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
    bool intersectAll (const Ray &ray, Intersection &recent_Inter, const double &tMin, const double &tMax) const;
    
    std::vector<Colour> _skyGradient;
    std::vector<std::unique_ptr<Solid>> _sceneObjects;
};

#endif /* Scene_hpp */
