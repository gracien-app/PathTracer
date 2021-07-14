//
//  Chunk.cpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 11/05/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include "Worker.hpp"

int Worker::_chunkCounter = 0;

Worker::Worker() : _chunkID(_chunkCounter++) {}

const int& Worker::getID() {
    return _chunkID;
}

const bool Worker::isWorking() {
    return busy;
}

const bool Worker::joinWorker() {
    
    if (Thread.joinable()) {
        Thread.join();
        return true;
    }
    
    else return false;
    
}
