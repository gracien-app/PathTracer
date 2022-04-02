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

struct Range {
    std::pair<int, int> start, end;
};

/// Wrapper class for std::thread with helper methods.
/// @discussion Each object contains unique ID which is used to differentiate between threads in easy way.
/// @note Created with future expansion in mind.
class Worker {

public:
    
    // MARK: Constructor
    
    /// Chunk constructor
    /// @brief Sets appropriate unique ID of newly created chunk (using static chunkCounter).
    Worker();
    
    // MARK: Methods
    
    /// Method used to execute std::thread::join() method on chunkThread (if joinable).
    /// @returns TRUE if successfully joined thread. FALSE otherwise.
    const bool joinWorker();
    
    /// Method used to determine, whether Chunk is currently busy.
    /// @returns TRUE if Chunk is busy. FALSE otherwise.
    const bool isWorking();
    
    /// Method used to extract unique chunk ID.
    /// @returns Constant integer defining ID of chunk.
    const int getID();
    
    const void run(std::thread task);
    
    // MARK: Data
    
    bool busy;
    
    
    Range workerRange;
    
private:
    std::thread _thread;
    const int _chunkID;
    static int _chunkCounter;

};

#endif /* Chunk_hpp */
