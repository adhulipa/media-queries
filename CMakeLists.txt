# Header
cmake_minimum_required(VERSION 3.2)
project(MediaQueries)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# Packages
find_package(OpenCV REQUIRED)

# Includes
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(MediaQueries main.cpp Frame.cpp Frame.h Resource.cpp Resource.h SceneDetector.cpp)
target_link_libraries( MediaQueries ${OpenCV_LIBS} )