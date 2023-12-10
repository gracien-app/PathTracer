# Library with all the Renderer-related logic
add_library(Renderer STATIC)

# C++14 is required for make_unique and related memory management features.
target_compile_features(Renderer PUBLIC cxx_std_17)

# Link to SFML from the Renderer.
# Renderer uses SFML's data types.
target_link_libraries(Renderer PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)

target_include_directories(Renderer PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/external/SFML/include>
    $<INSTALL_INTERFACE:include>
)

# Renderer sources and headers file path arrays.
set(RENDERER_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Renderer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Worker.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Scene.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Camera.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Material.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Geometry/Cube.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Geometry/Disc.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Geometry/Plane.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Geometry/Rectangle.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Geometry/Solid.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Scene/Geometry/Sphere.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Utilities/Colour.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Utilities/Ray.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Renderer/Utilities/Vectors.cpp"
)

target_sources(Renderer PUBLIC
    ${RENDERER_SRC}
)

