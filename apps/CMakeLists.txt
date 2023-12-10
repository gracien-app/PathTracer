# Main executable for the PathTracer: application management logic.
add_executable(PathTracer_App "main.cpp")

# C++14 for Smart Pointers and other memory management features.
target_compile_features(PathTracer_App PUBLIC cxx_std_17)


target_sources(PathTracer_App PRIVATE
    "App.cpp"
    "App.hpp"

    "Window.cpp"
    "Window.hpp"
)

target_link_libraries(PathTracer_App PRIVATE
    Renderer
)

