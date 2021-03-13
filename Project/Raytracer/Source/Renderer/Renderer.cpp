//
//  Renderer.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Renderer.hpp"

Renderer::Renderer() {
    outTexture.reset(new sf::Texture);
    outSprite.reset(new sf::Sprite);
    std::cout << "[C] Renderer: Created" << std::endl;
};
Renderer::~Renderer() {
    std::cout << "[D] Renderer: Terminated" << std::endl;
}

void Renderer::init(const sf::Vector2u &resolution) {
    _width = resolution.x;
    _height = resolution.y;
    
    _projectionHeight = 2.0; //MARK: Height coorinates go from -1,1 so the total length is 2.
    _aspectRatio = _width / _height; //MARK: Aspect to see how height defines width
    _projectionWidth = _projectionHeight*_aspectRatio; //MARK: Defining the width of coordinate system based on height.
    
    outPixels.reserve(_width*_height*4); //MARK: because we store each pixel as R G B A.
     
    if (outTexture->create(_width, _height)) {
        outSprite->setTexture(*outTexture);
    }
    else throw "Can't initialize - sf::Texture::Create failure";
    
    render();
}

void Renderer::render() {
    Scene coolSky;
    auto camera = coolSky.getCamera();
    auto focal_length = camera.getFocal();
    
    _origin = camera.getPosition(); //MARK: Origin of renderer = camera position from which we see the scene
    
    vect3D X        (_projectionWidth,0,0); //MARK: Vector defining the direction of rendering in X axis.
    vect3D Y        (0,_projectionHeight,0); //MARK: Vector defining the direction of rendering in Y axis.
    vect3D Depth    (0,0,focal_length); //MARK: Vector defining the depth (Z coordinate) for the render.
    
    vect3D upperLeft(_origin + Depth + Y/2 - X/2);
    //MARK: FIXED Rendering starts from upper left corner, so its origin+depth-half_of_with+ half_of_height
    //MARK: For Origin at (0,0,0) and aspect ratio of 2 its (-2,1,1)
    
    for (int j=0; j<(_height); j++) {
        for (int i=0; i<(_width); i++) {

            int gridPos = i+(j*_width);
            //MARK: CRUCIAL CUSTOM RESOLUTION FIX - gridPos = i+(j x width) not (j x height)
            //MARK: Pixels are transfered from continuous array of data, not by coordinates!

            auto x = double(i) / (_width-1);
            auto y = double(j) / (_height-1);
            //MARK: x and y are to multiply the vertical and horizontal projection vectors to point to the correct pixel

            Ray testRay( _origin, upperLeft + x*X - y*Y);
            //MARK: FIXED Initial idea: Go from upper left, then add partials of X and Y vectors to go in such way:
            //MARK: Upper Left -> Go right to pixel at width x -> Go down to pixel at height y. Starting always at _origin of renderer so from camera.
            
            auto colour = coolSky.spaceColour(testRay);
            //MARK: spaceColour returns normalized RGB, no corrections needed.

            outPixels[4*gridPos+0] = int(colour.x()*255.999);
            outPixels[4*gridPos+1] = int(colour.y()*255.999);
            outPixels[4*gridPos+2] = int(colour.z()*255.999);
            outPixels[4*gridPos+3] = int(255);
            
            //4* because one pixel consists of RGBA color components
            //+x to access specific component
            //.999 to compensate lack of <= width, height
        }
    }
    
    updateTexture();
}

void Renderer::updateTexture() {
    outTexture->update(&outPixels[0]);
}

sf::Sprite* Renderer::getSprite() {
    return outSprite.get();
}

/* Test Rainbow function for debugging
 
 for (int j=0; j<_height; j++) {
     for (int i=0; i<_width; i++) {

         auto r = float(i) / _width;
         auto g = float(j) / _height;
         auto b = 0.8;
         // MARK: Data from renderer will come normalised, keep the 255.999
         int gridPos = i+(j*_width);
         outPixels[4*gridPos+0] = int(r*255.999);
         outPixels[4*gridPos+1] = int(g*255.999);
         outPixels[4*gridPos+2] = int(b*255.999);
         outPixels[4*gridPos+3] = int(255);
         //4* because one pixel consists of RGBA color components
         //+x to access specific component
         //.999 to compensate lack of <= width, height
         
    
     }
 }
 
 */
