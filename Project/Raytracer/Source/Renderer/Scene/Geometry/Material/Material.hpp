//
//  Material.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 28/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Material_hpp
#define Material_hpp

/// Base class for all custom materials.
class Material {
public:
    Material();
private:
    
};

class Diffused : public Material {
public:
    Diffused();
private:
    
};

class Metallic : public Material {
public:
    Metallic();
private:
    
};



#endif /* Material_hpp */
