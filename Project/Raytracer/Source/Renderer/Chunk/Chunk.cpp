//
//  Chunk.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/05/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Chunk.hpp"

int Chunk::_chunkCounter = 0;

Chunk::Chunk(const int &yStart, const int &yEnd) : _chunkID(_chunkCounter++), _range(yStart,yEnd) {}

const int& Chunk::getID() {
    return _chunkID;
}

const bool Chunk::isWorking() {
    return busy;
}

const int& Chunk::rangeEnd() {
    return _range.second;
}

const int& Chunk::rangeStart() {
    return _range.first;
}

const bool Chunk::joinChunk() {
    
    if (chunkThread.joinable()) {
        chunkThread.join();
        return true;
    }
    
    else return false;
    
}
