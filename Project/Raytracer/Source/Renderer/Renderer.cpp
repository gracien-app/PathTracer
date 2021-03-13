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
    _aspect_ratio = _width / _height;
    
    outPixels.reserve(_width*_height*4); //because we store RGBA separately, that's why 4x
     
    if (outTexture->create(_width, _height)) {
        outSprite->setTexture(*outTexture);
    }
    else throw "Can't initialize - sf::Texture::Create failure";
    
    render();
}

void Renderer::render() {
    Scene coolSky;
    
    auto camera = coolSky.getCamera();
    
    _projection_Height = 1.0;
    _projection_Width = _projection_Height*_aspect_ratio;
    std::cout << "Height: "<<_projection_Height<<" Width: "<<_projection_Width<<std::endl;
    
    auto focal_length = 1.0;

    vect3D origin   (0,0,0);
    vect3D X        (_projection_Width,0,0); //Projection width
    vect3D Y        (0,_projection_Height,0); //Projection height
    vect3D Depth    (0,0,focal_length); //focal_length is Z, set like that for clarity
    
    vect3D upperLeft(origin+Y/2-X/2+Depth);
    //MARK:: Transformation of origin to get to upper left corner of projection plane so to (-1,1,1) which is normalised coordinate system.
    
//    for (int j=0; j<(_height); j++) {
//        for (int i=0; i<(_width); i++) {
//
//            int gridPos = i+(j*_height);
//
//            auto x = double(i) / (_width-1);
//            auto y = double(j) / (_height-1);
//            //MARK: x and y are to multiply the vertical and horizontal projection vectors to point to the correct pixel
//
//            Ray testRay( _origin, upperLeft + (x*X) + (y*Y) );
//            //MARK: Initial idea: Go from upper left, add hor and vert vectors with respect to x and y which indicate
//            //MARK: for which pixel it works, so i need to add X vector multiplied by x and Y by y.
//            auto colour = coolSky.spaceColour(testRay);
//            //MARK: spaceColour returns normalized RGB, no corrections needed.
//
//            outPixels[4*gridPos+0] = int(colour.x()*255.999);
//            outPixels[4*gridPos+1] = int(colour.y()*255.999);
//            outPixels[4*gridPos+2] = int(colour.z()*255.999);
//            outPixels[4*gridPos+3] = int(255);
//            //4* because one pixel consists of RGBA color components
//            //+x to access specific component
//            //.999 to compensate lack of <= width, height
//        }
//    }
    
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
            
            //MARK: CRUCIAL CUSTOM RESOLUTION FIX - gridPos = i+(j x width) not height, pixels
            //MARK: are transfered from continuous stream of data, not by coordinates!
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

/* Test Rainbow function

 */
