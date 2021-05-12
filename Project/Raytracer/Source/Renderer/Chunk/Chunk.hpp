//
//  Chunk.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/05/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Chunk_hpp
#define Chunk_hpp

#include "Scene.hpp"

#include <thread>
#include <mutex>

class Chunk {

public:
    
    Chunk(const int &yStart, const int &yEnd);
    
    void taskFinished(const sf::Time &executionTime, std::mutex &mut, const bool &stopped);
    
    bool joinChunk();
    bool isWorking();
    
    const int& rangeEnd();
    const int& rangeStart();
    
    const int& getID();
    
    std::thread workerThread;
    
private:
    
    bool _working;
    std::pair<int, int> _range;
    
    const int _chunkID;
    static int counterID;

};



#endif /* Chunk_hpp */
