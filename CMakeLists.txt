    cmake_minimum_required(VERSION 3.26)
    project(cpp_project)

    set(CMAKE_CXX_STANDARD 17)

    # Add the SDL2 include directory to the include search path
    include_directories(${CMAKE_SOURCE_DIR}/include/SDL2)

    # Set the path to the SDL2 library directory
    link_directories(C:/Users/bamax/OneDrive/Bureau/cpp_project/lib)  # Adjust the path as needed

    add_executable(cpp_project test.cpp framework.hpp framework.cpp
            Asteroid.cpp
            Asteroid.hpp
            Missile.cpp
            Missile.hpp
            FlyingObject.cpp
            FlyingObject.hpp)

    # Link your executable with the necessary libraries
    target_link_libraries(cpp_project mingw32 SDL2main SDL2)
