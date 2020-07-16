cmake_minimum_required(VERSION 2.8)
project(startProject)
set(Leptonica_DIR /Users/alejandrocamba/Documents/leptonica/build)


find_package(OpenCV REQUIRED)
find_package(Leptonica REQUIRED)
find_package(Tesseract REQUIRED)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${Leptonica_INCLUDE_DIRS})
include_directories(${Tesseract_INCLUDE_DIRS})

add_executable(startProject main.cpp)
target_link_libraries(startProject ${OpenCV_LIBS})
target_link_libraries(startProject ${Tesseract_LIBRARIES})