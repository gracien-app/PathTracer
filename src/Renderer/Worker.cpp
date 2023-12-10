//
//  Created by Gracjan Jeżewski on 11/05/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#include <PathTracer/Renderer/Worker.hpp>

int Worker::_chunkCounter = 0;

Worker::Worker() : _chunkID(_chunkCounter++) {}

const int Worker::getID() {
    return _chunkID;
}

const bool Worker::isWorking() {
    return busy;
}

const bool Worker::joinWorker() {
    if (_thread.joinable()) {
        _thread.join();
        return true;
    }
    
    else return false;
}

const void Worker::run(std::thread task) { 
    _thread = std::move(task);
}
