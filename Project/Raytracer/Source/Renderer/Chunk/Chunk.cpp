//
//  Chunk.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/05/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Chunk.hpp"

int Chunk::counterID = 0;

Chunk::Chunk(const int &yStart, const int &yEnd) : _chunkID(counterID++), _range(yStart,yEnd) {}

void Chunk::taskFinished(const sf::Time &executionTime, std::mutex &mut, const bool &stopped) {
    
    std::lock_guard<std::mutex> printLock(mut); // Safer than mutex::lock(), unlocks when out of scope
    
    _working = false;
    
    if (!stopped) {
        printf ("  [+] CHUNK: %i \n", _chunkID+1);
        printf ("      EXECUTION TIME: %f sec\n", executionTime.asSeconds());
    }
    
}

const int& Chunk::getID() {
    return _chunkID;
}

bool Chunk::isWorking() {
    return _working;
}

const int& Chunk::rangeEnd() {
    return _range.second;
}

const int& Chunk::rangeStart() {
    return _range.first;
}

bool Chunk::joinChunk() {
    
    if (workerThread.joinable()) {
        workerThread.join();
        return true;
    }
    
    else return false;
    
}
