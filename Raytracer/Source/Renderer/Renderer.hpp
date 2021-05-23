//
//  Renderer.hpp
//  Raytracer
//
//  Created by Gracjan Jeżewski on 09/03/2021.
//  Copyright © 2021 Gracjan Jeżewski. All rights reserved.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include "Chunk.hpp"

/// Helper class used to connect all logic of the Path-Tracer algorithm and provide unique storage for all Chunks.
/// @discussion Divides tasks between Chunks (threads) and initialises necessary data. Controls behaviour of Chunks.
class Renderer {
public:
    
    // MARK: Constructors & Destructor
    
    /// Renderer constructor
    /// @brief Displays appropriate message in the console
    /// @param width Width for which image render should be created
    /// @param height Height for which image render should be created
    Renderer(const uint &width, const uint &height);
    
    /// App destructor
    /// @brief Displays appropriate message in the console
    ~Renderer();
    
    // MARK: Methods
    
    /// Method used to call std::thread::join on all Chunks (wrapper class for std::thread) contained in _imageChunks.
    /// @return TRUE if all threads joined, FALSE otherwise.
    bool joinAll();
    
    /// Method used to determine if all Chunks (wrapper class for std::thread) finished execution of given task.
    bool allFinished();
    
    /// Method used to alter _stopExecution boolean to stop current rendering task on all Chunks.
    void stopAll();
    
    /// Method used to update sf::Texture with contents of array of pixels _outPixels.
    void updateTexture();
    
    /// Method used to run renderChunk on all available Chunks (wrapper class for std::thread)
    /// @param nPreset Index of preset from predefined presets for which renderChunk is ran.
    void runChunks(const int &nPreset);
    
    /// Method used to distribute tasks between Chunks, giving each of them unique range on which they work. Last thread is given range extended to the end of the image, for cases where image height is not divisible by number of threads.
    /// @param nThreads Number of threads available
    void distributeChunks(const int &nThreads);
    
    /// Method used to render chunk of the whole image. Iterates through pixels in given range, performing calculations samplesN-times.
    /// @discussion Gridpos defines cell in _outPixels vector, calcuated to match 1-dimensional vector of pixels (Implementation forced by SFML).
    /// X and Y are vectors which are used to alter the starting position (left upper corner of the projection plane) according to location of the currently calculated pixel.
    /// randomNumber in range <0;1> is added to both X and Y, to smoothen the transition between pixels (primitive antialiasing, pixel consists of itself and his nearest neighbours, needs great number of samples per pixel to provide accurate results).
    /// Results of different sample runs are added to the outputPixel, and averaged by colour::standardiseOutput method according to number of samples.
    /// At the end of execution, marks completion of the calculations by changing appropriate flag of the worker Chunk.
    /// @param chunkID ID of the chunk executing the metod, necessary to determine appropriate range of calculations.
    /// @param presetID ID of current preset from predefined scenes settings.
    /// @param samplesN Number of samples per pixel (how many times calculations are performed)
    /// @param bouncesN Number of ray bounces (reflections) per pixel.
    void renderChunk(const int &chunkID, const int &presetID, const int &samplesN, const int &bouncesN);
    
    /// Method used to initialise all necessary components of renderer object.
    /// @discussion Reserves space for _outPixels and vector of Chunks. Creates predefined scenes based on presets vector passed, only scenes defined in defaultPresets are allocated. Associates sf::Sprite with sf::Texture on which render results are presented and later passed to the window.
    /// @param defaultPresets Presets vector containing settings for predefined scenes.
    /// @param nThreads Number of worker threads available.
    /// @throws std::bad_alloc or char* (string) message.
    void Initialise(std::shared_ptr<std::vector<std::map<std::string, int>>> &userPresets, const int &nThreads);
    
    /// Method used to extract sf::Sprite smart pointer on which results of rendering are encoded.
    /// @discussion sf::Sprite consists of sf::Texture, which is loaded with _outPixels to form an image. Can be displayed by sf::RenderWindow
    /// @returns std::shared_ptr object by reference to increment smart pointer usage counter appropriately.
    std::shared_ptr<sf::Sprite> &refSprite();
    
private:
    
    double _width, _height;
    
    std::atomic<bool> _stopExecution;
    
    std::shared_ptr<sf::Sprite> _outSprite;
    std::unique_ptr<sf::Texture> _outTexture;
    std::shared_ptr<std::vector<std::map<std::string, int>>> _presetSettings;
    
    std::vector<Chunk> _imageChunks;
    std::vector<sf::Uint8> _outPixels;
    std::vector<std::unique_ptr<Scene>> _presetScenes;
    
};

#endif /* Renderer_hpp */
