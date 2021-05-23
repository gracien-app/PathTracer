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

/// Wrapper class for std::thread with helper methods.
/// @discussion Each object contains unique ID which is used to differentiate between threads in easy way.
/// @note Created with future expansion in mind.
class Chunk {

public:
    
    // MARK: Constructor
    
    /// Chunk constructor
    /// @brief Sets appropriate unique ID of newly created chunk (using static chunkCounter). Initialises range according to parameters provided.
    /// @param yStart Beginning of the range on which Chunk should work (height)
    /// @param yEnd End of the range on which Chunk should work (height)
    Chunk(const int &yStart, const int &yEnd);
    
    // MARK: Methods
    
    /// Method used to execute std::thread::join() method on chunkThread (if joinable).
    /// @returns TRUE if successfully joined thread. FALSE otherwise.
    const bool joinChunk();
    
    /// Method used to determine, whether Chunk is currently busy.
    /// @returns TRUE if Chunk is busy. FALSE otherwise.
    const bool isWorking();
    
    /// Method used to extract end of the range on which Chunk is performing calculations.
    /// @returns Constant integer value defining end of range.
    const int& rangeEnd();
    
    /// Method used to extract start of the range on which Chunk is performing calculations.
    /// @returns Constant integer value defining start of range.
    const int& rangeStart();
    
    /// Method used to extract unique chunk ID.
    /// @returns Constant integer defining ID of chunk.
    const int& getID();
    
    // MARK: Data
    
    bool busy;
    std::thread chunkThread;
    
private:
    
    std::pair<int, int> _range;
    
    const int _chunkID;
    static int _chunkCounter;

};



#endif /* Chunk_hpp */
