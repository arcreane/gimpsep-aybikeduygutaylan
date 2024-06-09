cmake_minimum_required(VERSION 3.21)
project(multimediaproject)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

set(CMAKE_CXX_STANDARD 14)

# Include OpenCV headers
include_directories(${OpenCV_INCLUDE_DIRS})

# Define your project's source files
set(SOURCES main.cpp ImageEditor.cpp ImageEditor.h)

# Add executable and link libraries
add_executable(multimediaproject main.cpp ImageEditor.h ImageEditor.cpp VideoManipulations.cpp VideoManipulations.h)
target_link_libraries(multimediaproject sfml-graphics ${OpenCV_LIBS})


